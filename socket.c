#include "socket.h"

/*Определим массив сокетов водителей*/
static int countCars = 0; //Счетчик подключенных водителей
static _STRUCT_POINT_SOCKET *point_socket_car[_STRUCT_POINT_SOCKET_COUNT];
/*Определим массив сокетов пассажиров*/
static int countPass = 0; //Счетчик подключенных пассажиров
static _STRUCT_POINT_SOCKET *point_socket_pass[_STRUCT_POINT_SOCKET_COUNT];
/*Мьютекс*/
static pthread_mutex_t mutex_server = PTHREAD_MUTEX_INITIALIZER; //Так как мьютекс статичкский- иницмализируем его макросом

/*Соединение клиента с сервером*/
int connectToServerSocket(char *serverAddress, int port)
{
    int sockfd = 0;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return -1;
    }
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(serverAddress);
    //Попробуем по имени хоста подключиться
    if((int)serv_addr.sin_addr.s_addr == -1)
    {
        struct hostent *host_struct = NULL;
        host_struct = gethostbyname(serverAddress);
        if(host_struct == 0L)
        {
            printf("\n Error : Could not get host by name \n");
            return -1;
        }
        serv_addr.sin_addr = *((struct in_addr *)host_struct->h_addr);
    }



    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)    
    {
        printf("\n Error : Connect Failed \n");
        return -2;
    }

    return sockfd;
}

//---------------------------------------------------------------------------
int sendPacketInfoToServer(int socket,int typeClient, int x, int y)
{
    QUERY_PACKET_HEAD head;
    head.x = x;
    head.y = y;
    head.PacketType = typeClient;
    head.BodyLength = 0;
    
    QUERY_PACKET packet = {head, 0};
    packet.head.crc = 0;
    unsigned char crc = Crc8((unsigned char *)(&packet), sizeof(QUERY_PACKET_HEAD)+head.BodyLength);
    packet.head.crc = crc;
    int res = SendPacket(socket,(char*)(&packet),sizeof(QUERY_PACKET_HEAD)+head.BodyLength);

    return res;
}
//---------------------------------------------------------------------------
bool checkSRCPacket(QUERY_PACKET *packet)
{
    unsigned char crc_recv = (*packet).head.crc;
    (*packet).head.crc = 0;
    unsigned char crc_count = Crc8((unsigned char *)packet,sizeof(QUERY_PACKET_HEAD) + (*packet).head.BodyLength);
    (*packet).head.crc = crc_recv;
    //printf("\rcrc_count = %i, crc_recv = %i\r",crc_count,crc_recv);
    return (crc_count == crc_recv);
}
//---------------------------------------------------------------------------
/*Проверка клиента на пару*/
bool checkPair(_STRUCT_POINT_SOCKET *point)
{
    if (point->socket_pair>0)
    {
        char buffer[200];
        double dist = getDistance(point->x,point->y,point->x_pair,point->y_pair);
        sprintf(buffer,"Найдена пара %d x=%d, y=%d расстояние %0.3f",point->socket_pair,point->x_pair,point->y_pair,dist);
        SendPacketAck(point->socket,buffer);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
int readPacketFromServer(int socket, _STRUCT_POINT_SOCKET *point_s)
{
    char buffer[_LEN_BUFFER];

    int valread = ReceiveBuffer(socket,buffer,sizeof(QUERY_PACKET_HEAD),_TIME_OUT_SERVER_SECONDS);
    if (valread<0)
    {
          printf("\n Error read from socket %d \n",socket);
          //SendPacketReject(socket,"Error read from socket");
          //isBreak = true;
          //continue;
          return _IS_BREAK_FROM_CYCLE_STATUS;
    }
    if (valread>0)
    {

        //printf("\n valread=%i \n",valread);
        //Если считали не весь пакет, считаем еще
        if (valread<sizeof(QUERY_PACKET_HEAD))
        {
            usleep(10*1000);
            int len = ReceiveBuffer(socket,&buffer[valread],sizeof(QUERY_PACKET_HEAD),_TIME_OUT_SERVER_SECONDS);//read( socket , &buffer[valread], sizeof(QUERY_PACKET_HEAD) - valread); 
            if (len>0) valread += len;
        }
        //printf("buffer=%s\r\n",buffer);
        if (valread<sizeof(QUERY_PACKET_HEAD))
        {
            SendPacketReject(socket,"Error read packet");
            return -1;
        }
        else
        {
            QUERY_PACKET_HEAD head;
            memcpy(&head,buffer,sizeof(QUERY_PACKET_HEAD));
            QUERY_PACKET packet; 
            packet.head = head;
            //считаем тело
            if (head.BodyLength>MAX_QUERY_BODY_LENGTH)
            {
                printf("\n Error read Body \n");
                SendPacketReject(socket,"Error read Body");
                return -1;
            }
            if (head.BodyLength>0)
            {
                int len = read( socket , packet.body, head.BodyLength);
                if (len>0 && len<MAX_QUERY_BODY_LENGTH)
                    packet.body[len] = 0;
            }
            //packet.body = body;
            if (!checkSRCPacket(&packet))
            {
                printf("\n Error CRC \n");
                SendPacketReject(socket,"Error CRC");
            }
            else if ((head.PacketType!= _TYPE_QUERY_CARS && head.PacketType!= _TYPE_QUERY_PASS) || point_s->typeClient>0 && head.PacketType!=point_s->typeClient)
            {
                printf("\n Error PacketType %i point_s->typeClient = %i\n",head.PacketType,point_s->typeClient);
                SendPacketReject(socket,"Error PacketType");
            }
            else if (getDistance(0,0,(int)packet.head.x,(int)packet.head.y)>_MAX_RADIUS_DISTANCE)
            {
                printf("\n Error Distance\n");
                SendPacketReject(socket,"Error Distance");
            }
            else
            {
                if (point_s->typeClient==0)//значит еще в список не добавлен
                    point_s->typeClient = head.PacketType;
                if (addSocketToList(socket,point_s,head.x,head.y))
                {
                    SendPacketAck(socket,"");
                    findPairToClient(point_s);
                    return valread;
                }
                else
                {
                    printf("\n Error AddPacket \n");
                    SendPacketReject(socket,"Error AddPacket");
                    //return -1;
                }

            }
        }
        //send(socket , "hello" , 5 , 0 ); 
    }

    return 0;
}
//---------------------------------------------------------------------------
//потоковая функция клиента
void* threadSocket(void* thread_data)
{
    if (!thread_data)
        return NULL;
    //Присаоим сокет из основного потока сервера локальной переменной
    int socket = *((int*)thread_data);
    //Выделяем память под структуру данных клиента
    _STRUCT_POINT_SOCKET *point_s = (_STRUCT_POINT_SOCKET *)malloc(sizeof(_STRUCT_POINT_SOCKET));
    point_s->socket =  socket;
    point_s->typeClient = 0;
    point_s->socket_pair = 0;
    bool isBreak = false;
    struct timeval tv1,tv2;
    struct timezone tz;
    /*Старт таймера*/
    time_start(&tv1,&tz);
    while (!isBreak && time_stop(&tv1,&tz)<=_TIME_OUT_SERVER_SECONDS*1000)
    {
        int res_read = readPacketFromServer(socket, point_s);
        if (res_read ==_IS_BREAK_FROM_CYCLE_STATUS)
        {
            isBreak = true;
            //printf("\n Нашли пару \n");
            continue;
        }
        //Если считали какие-то данные то обнулим таймер
        if (res_read>0)
           time_start(&tv1,&tz);
        if (checkPair(point_s))
        {
            isBreak = true;
            printf("\n Нашли пару \n");
            continue;
        }
        usleep(100);
    }
    //Удаляем сокет из списка
    delSocketFromList(socket,point_s->typeClient);
    printf("\n Завершили поток \n");
    //Закроем сокет
    //Именно так. Если порядок поменять, то другой сокет законнектится
    shutdown(socket,SHUT_RDWR);
    close(socket);
    pthread_exit(0);
}


/*Стартуем поток сокета*/
int startThread(int socket)
{
    
    //данные для потока
    //void* thread_data = (int*)malloc(sizeof(int));
    //((int*)thread_data)[0] = socket;
    //создаем идентификатор потока
    pthread_t thread;

    //создаем поток по идентификатору thread и функции потока threadSocket
    //и передаем потоку указатель на данные thread_data
    pthread_create(&thread, NULL, threadSocket, &socket);

    //ждем завершения потока
    //pthread_join(thread, NULL);

    return 0;
    
}

/*Очистим данные*/
void clearData()
{
    pthread_mutex_lock(&mutex_server);
    for (int i=0;i<_STRUCT_POINT_SOCKET_COUNT;i++)
    {
        point_socket_car[i] = NULL;
        point_socket_pass[i] = NULL;
    }
    countCars = 0;
    countPass = 0;
    pthread_mutex_unlock(&mutex_server);
}

/*Стартуем серверный сокет*/
int startServerSocket()
{
    //Инициализация мьютекса
    //pthread_mutex_init(&mutex_server, NULL);
    clearData();
    struct sockaddr_in addr;
    int addrlen = sizeof(addr); 

    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        printf("socket error\r\n");
        return _ERROR_SOCKET;
    }
    int on = 1;
    //printf("setsockopt(SO_REUSEADDR)\n");
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
           perror("setsockopt(SO_REUSEADDR) failed");
           return _ERROR_SOCKET;
    }

    int port = _SERVER_PORT;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, addrlen) < 0)
    {
        printf("bind error\r\n");
        return _ERROR_SOCKET;
    }

    printf("Start New Server Socket\r\n");
    while (1)
    {
        listen(listener, 1);
        int new_socket = 0;
        if ( 
            (new_socket = accept(listener, (struct sockaddr *)&addr, (socklen_t*)&addrlen))<0
            //(new_socket = accept(listener, NULL,NULL))<0
        )
        {
            perror("accept error\r\n"); 
            //exit(EXIT_FAILURE); 
        }
        startThread(new_socket);
    }
    printf("Server start success on port %i!!!\r\n",port);
    //Уничтожение мьютекса
    //pthread_mutex_destroy(&mutex_server);
    return listener;
}

/*Добавим значение в список*/
bool addSocketToList(int socket,_STRUCT_POINT_SOCKET *point_s,int x,int y)
{
    pthread_mutex_lock(&mutex_server);
    int index_null = -1;
    bool retValue = false;
    point_s->x = x;
    point_s->y = y;
    if (point_s->typeClient==_TYPE_QUERY_CARS)
    {
        for (int i=0;!retValue && i<_STRUCT_POINT_SOCKET_COUNT;i++)
        {
            if (!point_socket_car[i])
            {
                if(index_null<0)
                    index_null = i;
                continue;
            }
            if(point_socket_car[i]->socket == socket)//Если сокет уже есть, то вернем
            {
              retValue = true;
              point_socket_car[i]->x = point_s->x;
              point_socket_car[i]->y = point_s->y;
            }
        }
        if (index_null>=0)
        {
            retValue = true;
            point_socket_car[index_null] = point_s;
            countCars++;
        }
    }
    else
    if (point_s->typeClient==_TYPE_QUERY_PASS)
    {
        for (int i=0;!retValue && i<_STRUCT_POINT_SOCKET_COUNT;i++)
        {
            if (!point_socket_pass[i])
            {
                if(index_null<0)
                    index_null = i;
                continue;
            }
            if(point_socket_pass[i]->socket == socket)//Если сокет уже есть, то вернем
            {
              retValue = true;
              point_socket_pass[i]->x = point_s->x;
              point_socket_pass[i]->y = point_s->y;
            }
        }
        if (index_null>=0)
        {
            retValue = true;
            point_socket_pass[index_null] = point_s;
            countPass++;
        }
    }
    printf("Сокет %i, x=%i,y=%i\n",socket,point_s->x,point_s->y);
    pthread_mutex_unlock(&mutex_server);
    return retValue;
}

/*Удалим сокет из списка*/
bool delSocketFromList(int socket, int typeClient)
{
    pthread_mutex_lock(&mutex_server);
    for (int i=0;i<_STRUCT_POINT_SOCKET_COUNT;i++)
    {
        if(typeClient==_TYPE_QUERY_CARS && point_socket_car[i] && point_socket_car[i]->socket == socket)
        {
           free(point_socket_car[i]);
           point_socket_car[i] = NULL;
           countCars--;
           break;
        }
        if(typeClient ==_TYPE_QUERY_PASS && point_socket_pass[i] && point_socket_pass[i]->socket == socket)
        {
           free(point_socket_pass[i]);
           point_socket_pass[i] = NULL;
           countPass--;
           break;
        }
    }


    pthread_mutex_unlock(&mutex_server);

}
/*Ищем расстояние между точками*/
double getDistance(int x1,int y1,int x2,int y2)
{
    return (double)sqrt(pow((x2-x1),2) + pow((y2-y1),2));
}

/*Ищем пару клиенту*/
bool findPairToClient(_STRUCT_POINT_SOCKET *point_s)
{
    _STRUCT_POINT_SOCKET **point_socket = NULL;
    bool retValue = false;
    pthread_mutex_lock(&mutex_server); //Наиболее жесткий вариант синхронизации
    if (point_s->typeClient==_TYPE_QUERY_CARS)
        point_socket = point_socket_pass;
    else
    if (point_s->typeClient==_TYPE_QUERY_PASS)
        point_socket = point_socket_car;
    double minDist = 0;
    int minIndex = -1;

    for (int i=0;point_socket && i<_STRUCT_POINT_SOCKET_COUNT;i++)
    {
        if (!point_socket[i])
            continue;
        double dist0 = getDistance(point_socket[i]->x,point_socket[i]->y,point_s->x,point_s->y);
        if (minIndex<0 || minDist>dist0)
        {
            retValue = true;
            minIndex = i;
            minDist = dist0;
        }
    }
    printf("findPairToClient retValue = %i, minIndex = %i\n",retValue,minIndex);
    if (retValue && minIndex>=0) //Нашли пару бедолаге
    {
        point_socket[minIndex]->x_pair = point_s->x;
        point_socket[minIndex]->y_pair = point_s->y;
        point_socket[minIndex]->socket_pair = point_s->socket;

        point_s->x_pair = point_socket[minIndex]->x;
        point_s->y_pair = point_socket[minIndex]->y;
        point_s->socket_pair = point_socket[minIndex]->socket;

    }
    pthread_mutex_unlock(&mutex_server);
    return retValue;
}


void time_start(struct timeval *tv1, struct timezone *tz) { gettimeofday(tv1, tz); }
long time_stop(struct timeval *tv1, struct timezone *tz)
{ 
  struct timeval dtv;
  struct timeval tv2;
  gettimeofday(&tv2, tz);
  dtv.tv_sec= tv2.tv_sec -tv1->tv_sec;
  dtv.tv_usec=tv2.tv_usec-tv1->tv_usec;
  if(dtv.tv_usec<0) { dtv.tv_sec--; dtv.tv_usec+=1000000; }
  return dtv.tv_sec*1000+dtv.tv_usec/1000;
}

/*Считывание данных из сокета с таймаутом*/
int ReceiveBuffer(int Socket,void *buffer,int length, int timeoutmsec)
{
  struct timeval tv1;
  struct timezone tz;
  fd_set readfds;
  int offset = 0;
  time_start(&tv1,&tz);
  for(;time_stop(&tv1,&tz) < timeoutmsec;usleep(100))
  {
      //printf("time_out = %d\r\n",(int)time_stop());
      struct timeval tv = {0,10};
      FD_ZERO(&readfds);
      FD_SET((unsigned int)Socket, &readfds);
      int SelCount = select( Socket + 1, &readfds, NULL , NULL , &tv);
      if(SelCount == -1)
      {
          printf("\n Error Read Socket \n");
          return -1;
      }
      //if(FD_ISSET(Socket, &readfds))
      if (SelCount>0)
      {
          int RecvBytes = read( Socket , (char *)(buffer)+offset, (length-offset)); //recv(Socket,(char *)(buffer)+offset,(length-offset), 0);
          if(RecvBytes < 0)
          {
            printf("\n Error Read Socket \n");
              return -1;
          }
          if(RecvBytes>0)
          {
             offset += RecvBytes;
            //printf("return res = %i\r\n",offset);
            if(offset == length)
                return offset;
          } 
        usleep(1);
      };
  };// end for
  //printf("return 0\r\n");
  return 0;
}


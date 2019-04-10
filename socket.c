#ifndef PacketDeclH
#define PacketDeclH
#include "packet.c"

#include <stdio.h>
#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <pthread.h>
#include <netdb.h>
#include <sys/time.h>
#include <stdbool.h>

#define _STRUCT_POINT_SOCKET_COUNT   500

#define _SERVER_PORT    2000
#define _ERROR_SOCKET   -1
#define _LEN_BUFFER     1024

#define _MAX_COORDINATE_X 1024
#define _MAX_COORDINATE_Y 1024

#define     _TYPE_QUERY_CARS            1
#define     _TYPE_QUERY_PASS            2

#define     _TIME_OUT_SERVER_SECNDS     10

/*Соединение клиента с сервером*/
int connectToServerSocket(char *serverAddress, int port);
/*Клиент посылает информацию о себе*/
int sendPacketInfoToServer(int socket,int typeClient, int x, int y);
/*Проверка CRC присланного пакета*/
bool checkSRCPacket(QUERY_PACKET *packet);
/*Очистим данные*/
void clearData();
//потоковая функция клиента
void* threadSocket(void* thread_data);
/*Стартуем серверный сокет*/
int startServerSocket();
/*Удалим сокет из списка*/
bool delSocketFromList(int socket);


typedef struct
{
    /*Тип клиента*/
    int typeClient;
     /*Координата X*/
     int x;
     /*Координата Y*/
     int y;
     /*Сокет по которому подключились*/
     int socket;
     /*Сокет пары*/
     int socket_pair;
} _STRUCT_POINT_SOCKET;

/*Определим массив сокетов водителей*/
static int countCars = 0; //Счетчик подключенных водителей
static _STRUCT_POINT_SOCKET *point_socket_car[_STRUCT_POINT_SOCKET_COUNT];
/*Определим массив сокетов пассажиров*/
static int countPass = 0; //Счетчик подключенных пассажиров
static _STRUCT_POINT_SOCKET *point_socket_pass[_STRUCT_POINT_SOCKET_COUNT];
/*Мьютекс*/
static pthread_mutex_t mutex_server;

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
    return (crc_count == crc_recv);
}
//---------------------------------------------------------------------------

//потоковая функция клиента
void* threadSocket(void* thread_data){
    if (!thread_data)
        return NULL;
    int socket = ((int*)thread_data)[0];
    free(thread_data);
    printf("socket=%d\r\n",socket);
    char buffer[_LEN_BUFFER];
    //Таймауты задаем
    struct timeval tv = {_TIME_OUT_SERVER_SECNDS,0};
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    _STRUCT_POINT_SOCKET *point_s = (_STRUCT_POINT_SOCKET *)malloc(sizeof(_STRUCT_POINT_SOCKET));
    point_s->socket =  socket;
    point_s->typeClient = 0;
    bool isBreak = false;
    while (!isBreak)
    {
        int retval = select(socket + 1, &rfds, NULL, NULL, &tv);
        switch(retval)
        {
            case -1:                
                printf("\n Error read from socket %d \n",socket);
                SendPacketReject(socket,"Error read from socket");
                isBreak = true;
                //close(socket);
                continue;
            case 0:
                printf("\n Time out %d second from socket %d \n",_TIME_OUT_SERVER_SECNDS,socket);
                SendPacketReject(socket,"Error Time out");
                isBreak = true;
                //close(socket);
                continue;
        }
        usleep(1000);
        int valread = read( socket , buffer, sizeof(QUERY_PACKET_HEAD)); 
        if (valread>0)
        {
            //Если считали не весь пакет, считаем еще
            if (valread<sizeof(QUERY_PACKET_HEAD))
            {
                usleep(10*1000);
                int len = read( socket , &buffer[valread], sizeof(QUERY_PACKET_HEAD) - valread); 
                if (len>0) valread += len;
            }
            //printf("buffer=%s\r\n",buffer);
            if (valread<sizeof(QUERY_PACKET_HEAD))
                SendPacketReject(socket,"Error read packet");
            else
            {
                SendPacketAck(socket,"");
                QUERY_PACKET_HEAD head;
                memcpy(&head,buffer,sizeof(QUERY_PACKET_HEAD));
                QUERY_PACKET packet; 
                packet.head = head;
                //считаем тело
                if (head.BodyLength>MAX_QUERY_BODY_LENGTH)
                {
                    printf("\n Error read Body \n");
                    SendPacketReject(socket,"Error read Body");
                    continue;
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
            }
            //send(socket , "hello" , 5 , 0 ); 
        }
        delSocketFromList(socket);
        close(socket);
        sleep(1);
    }
    //завершаем поток
    pthread_exit(0);
}


/*Стартуем поток сокета*/
int startThread(int socket)
{
    
    //данные для потока (для примера)
    void* thread_data = (int*)malloc(sizeof(int));
    ((int*)thread_data)[0] = socket;                                                                            
    //создаем идентификатор потока
    pthread_t thread;                                                            
                                                                                
    //создаем поток по идентификатору thread и функции потока threadSocket
    //и передаем потоку указатель на данные thread_data
    pthread_create(&thread, NULL, threadSocket, thread_data);

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
    
    while (1)
    {
        listen(listener, 1);    
        printf("Start New Server Socket\r\n");
        int new_socket = 0;
        if ( 
            (new_socket = accept(listener, (struct sockaddr *)&addr, (socklen_t*)&addrlen))<0
            //(new_socket = accept(listener, NULL,NULL))<0
        ) 
        { 
            perror("accept error"); 
            //exit(EXIT_FAILURE); 
        }     
        startThread(new_socket);
    }
    printf("Server start success on port %i!!!\r\n",port);
    
    return listener;
}

/*Добавим значение в список*/
bool addSocketToList(int socket,QUERY_PACKET *packet)
{
    pthread_mutex_lock(&mutex_server);
    for (int i=0;i<_STRUCT_POINT_SOCKET_COUNT;i++)
    {
        //point_socket_car[i] = NULL;
        //point_socket_pass[i] = NULL;
    }
    countCars = 0;
    countPass = 0;
    pthread_mutex_unlock(&mutex_server);
    
}

/*Удалим сокет из списка*/
bool delSocketFromList(int socket)
{
    pthread_mutex_lock(&mutex_server);
    for (int i=0;i<_STRUCT_POINT_SOCKET_COUNT;i++)
    {
        if(point_socket_car[i] && point_socket_car[i]->socket == socket)
        {
           free(point_socket_car[i]);
           point_socket_car[i] = NULL;
           countCars--;
        }
        if(point_socket_pass[i] && point_socket_pass[i]->socket == socket)
        {
           free(point_socket_pass[i]);
           point_socket_pass[i] = NULL;
           countPass--;
        }
    }
    
    
    pthread_mutex_unlock(&mutex_server);
    
}

#endif

/*Клиентский сокет*/
//#include "packet.c"
#include "socket.c"
#define try bool __HadError=false;
#define catch(x) ExitJmp:if(__HadError)

char ipAddress[255];
int typeClient;
int x;
int y;
int timeOutMs = 1000;
int step_x = 1;
int step_y=1;

int socketClient = 0;

/*Печатаем сообщение при неудачном запуске*/
void printHelpInfo(char *progName)
{
    printf("При запуске необходимо указывыть 4 или 5 параметров: \r\n\
    %s <p или с (пассажир или водитель)> <Координата X> <Координата Y> <IP адрес сервера> [<Таймаут в миллисикундах (по умолчанию 1000)>]\r\n"
    ,progName    
    );
}

/*Проверяем введенные данные в параметрах*/
void checkParamData()
{
    if (typeClient!=_TYPE_QUERY_PASS && typeClient!=_TYPE_QUERY_CARS)
    {
        printf("Первый параметр должен быть p или с (пассажир или водитель)\r\n");
        exit(EXIT_FAILURE);
    }
    if (getDistance(0,0,x,y)>_MAX_RADIUS_DISTANCE)
    {
        printf("Точка вне зоны лосягаемости %d\r\n",_MAX_RADIUS_DISTANCE);
        exit(EXIT_FAILURE);
    }
    socketClient = connectToServerSocket(ipAddress, _SERVER_PORT);
    if (socketClient<=0)
    {
        printf("Невозможно соединится с сервером %s\r\n",ipAddress);
        exit(EXIT_FAILURE);
    }
    
    int res =0;
    //usleep(1000 * 10);
    //for (int i=0;i<20;i++)
    int i = 0;
    while(getDistance(0,0,x,y)<=_MAX_RADIUS_DISTANCE)
    {
        i++;
        res = sendPacketInfoToServer(socketClient,typeClient, x, y);
        int size_reply_packet = sizeof(REPLY_PACKET_HEAD);
        //printf("Результат посылки пакета  %i, i=%i,sizeof(REPLY_PACKET_HEAD)=%i\r\n",res,i,size_reply_packet);
        char buffer[1024];
        REPLY_PACKET r_packet;
        int result =0;
        try{result = ReceiveBuffer(socketClient,&r_packet.head,sizeof(REPLY_PACKET_HEAD),1000);}
        catch(...){}
        if (result<0 || result<sizeof(REPLY_PACKET_HEAD))
        {
            printf("Ошибка чтения пакета\r\n");
        }
        else
        {
            char buffer[1024];
            int lenRead=0;
            if (r_packet.head.BodyLength>0)
                lenRead = ReceiveBuffer(socketClient,r_packet.body,r_packet.head.BodyLength,1000);
            if (lenRead<0) lenRead = 0;
            r_packet.body[lenRead] = 0;
            int offset = 0;
            ParseStringValue(r_packet.body,&offset,buffer);
            
            if (r_packet.head.PacketType == ACK)
                printf("Packet OK %s i=%i x=%i y=%i\r\n",buffer,i,x,y);
            else
                printf("Packet Error %s i=%i x=%i y=%i\r\n",buffer,i,x,y);
        }
        x = x+step_x;
        y = y+step_y;
        usleep(timeOutMs * 1000);
    }
    
    
}


int main(int argc, char const *argv[]) 
{
    int x = 0;
    
    if (argc<5)
    {
        printHelpInfo((char*)argv[0]);
        return -1;
    }
    typeClient = 0;
    if (strcmp(argv[1],"p") == 0 || strcmp(argv[1],"P") == 0)
        typeClient =  _TYPE_QUERY_PASS;
    else
    if (strcmp(argv[1],"c") == 0 || strcmp(argv[1],"C") == 0)
        typeClient =  _TYPE_QUERY_CARS;
    x = atoi(argv[2]);
    y = atoi(argv[3]);
    strcpy(ipAddress,argv[4]);
    
    if (argc>5)
       timeOutMs =  atoi(argv[5]);
    srand ( time(NULL) );
    if ((rand() % 100)%2 ==0)
        step_x = -1;
    if ((rand() % 100)%2 ==0)
        step_y = -1;
        
    checkParamData();
    
    
    return 0;  
}

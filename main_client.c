/*Клиентский сокет*/
//#include "packet.c"
#include <getopt.h>
#include <unistd.h>

#include "socket.h"
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
    printf("При запуске необходимо указывыть 4 или 5 параметров:\n"
    "%s < --type (-t) <p или с> (пассажир или водитель)> \n"
    "-x <Координата X> \n"
    "-y <Координата Y> \n"
    "--server(-s) <IP адрес сервера> \n"
    "[--timeout(-o) <Таймаут в миллисикундах (по умолчанию 1000)>]\n"
    ,progName
    );
}

/*Проверяем введенные данные в параметрах*/
void checkParamData()
{
    if (typeClient!=_TYPE_QUERY_PASS && typeClient!=_TYPE_QUERY_CARS)
    {
        printf("Не задан тип клиента (пассажир или водитель)\r\n");
        exit(EXIT_FAILURE);
    }
    if (getDistance(0,0,x,y)>_MAX_RADIUS_DISTANCE)
    {
        printf("Точка вне зоны лосягаемости %d\r\n",_MAX_RADIUS_DISTANCE);
        exit(EXIT_FAILURE);
    }
    if (timeOutMs<=0)
    {
        printf("Неверное значение таймаута %d\r\n",timeOutMs);
        exit(EXIT_FAILURE);
    }
    if (strcmp(ipAddress,"")==0)
    {
        printf("Не задан адрес сервера\r\n");
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


int main(int argc, char *argv[]) 
{
    //int x = 0;
    //Начинаем разбор параметров
    int c;
    int optIdx;
    int flag_help = 0;
    strcpy(ipAddress,"");
    static struct option long_opt[] = {
                {"help", 0, 0, 'h'},
                {"type", 1, 0, 't'},
                {"x", 1, 0, 'x'},
                {"y", 1, 0, 'y'},
                {"server", 1, 0, 's'},
                {"out", 1, 0, 'o'},
                {0,0,0,0}
              };
    while(true)
    {

        if((c = getopt_long(argc, argv, "ht:x:y:o:s:", long_opt, &optIdx)) == -1)
           break;
       //printf("paramname=%c paramvalue=%s\n",c,optarg);
       switch( c )
        {
            case 'h':
               //usage(argv[0]);
                 printHelpInfo((char*)argv[0]);
                 return(-1);
             case 's':
                 strcpy(ipAddress,optarg);
                 printf("option 's' servername: %s\n", ipAddress);
                 break;
             case 'x':
                x = atoi(optarg);
                break;
             case 'y':
                y = atoi(optarg);
                break;
             case 't':
                if(strcmp(optarg,"p")==0)
                   typeClient =  _TYPE_QUERY_PASS;
                else
                if(strcmp(optarg,"c")==0)
                   typeClient =  _TYPE_QUERY_CARS;
                break;
             case 'o':
                timeOutMs = atoi(optarg);
                break;
             default:
                 //usage(argv[0]);
                 printf("Invalid argument %c\n",c);
                 return(-1);
        }
    }


    srand ( time(NULL) );
    if ((rand() % 100)%2 ==0)
        step_x = -1;
    if ((rand() % 100)%2 ==0)
        step_y = -1;

    checkParamData();

    return 0;
}

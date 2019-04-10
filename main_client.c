/*Клиентский сокет*/
//#include "packet.c"
#include "socket.c"

char ipAddress[255];
int typeClient;
int x;
int y;

int socketClient = 0;

/*Печатаем сообщение при неудачном запуске*/
void printHelpInfo(char *progName)
{
    printf("При запуске необходимо указывыть 4 параметра: \r\n\
    %s <p или с (пассажир или водитель)> <Координата X> <Координата Y> <IP адрес сервера>\r\n"
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
    if (x>_MAX_COORDINATE_X || -x < -_MAX_COORDINATE_X)
    {
        printf("Координата X должна быть в пределах от %d до %d\r\n",-_MAX_COORDINATE_X,_MAX_COORDINATE_X);
        exit(EXIT_FAILURE);
    }
    if (y>_MAX_COORDINATE_Y || -y<-_MAX_COORDINATE_Y)
    {
        printf("Координата Y должна быть в пределах от %d до %d\r\n",-_MAX_COORDINATE_Y,_MAX_COORDINATE_Y);
        exit(EXIT_FAILURE);
    }
    socketClient = connectToServerSocket(ipAddress, _SERVER_PORT);
    if (socketClient<=0)
    {
        printf("Невозможно соединится с сервером %s\r\n",ipAddress);
        exit(EXIT_FAILURE);
    }
    
    int res = sendPacketInfoToServer(socketClient,typeClient, x, y);
    printf("Результат посылки пакета  %i\r\n",res);
}

int main(int argc, char const *argv[]) 
{
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
    
    checkParamData();
    
    
    return 0;  
}

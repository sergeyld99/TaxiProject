#ifndef PacketDeclH
#define PacketDeclH
#include "packet.h"

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
#include <math.h>
#include <time.h>
#include <sys/times.h>

/*Максимальное количество одновременно подключенных клиентов (одинаково для пассажиров и клиентов)*/
#define _STRUCT_POINT_SOCKET_COUNT   500

/*Порт сервера*/
#define _SERVER_PORT    2000
#define _ERROR_SOCKET   -1
#define _LEN_BUFFER     1024

/*Максимальное удаление от точки 0, 0 (радиус удаления)*/
#define   _MAX_RADIUS_DISTANCE  1024

#define     _TYPE_QUERY_CARS            1
#define     _TYPE_QUERY_PASS            2

/*Таймаут бездействия клиента в секундах*/
#define     _TIME_OUT_SERVER_SECONDS     10

#define    _IS_BREAK_FROM_CYCLE_STATUS   -100000

//структура для клиента подключенного к сераеру
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
     /*Координата X пары*/
     int x_pair;
     /*Координата Y пары*/
     int y_pair;
} _STRUCT_POINT_SOCKET;

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
/*Считывание данных из сокета*/
int ReceiveBuffer(int socket,void *buffer,int length, int timeoutmsec);
/*Стартуем серверный сокет*/
int startServerSocket();
/*Добавим значение в список*/
bool addSocketToList(int socket,_STRUCT_POINT_SOCKET *point_s,int x,int y);
/*Удалим сокет из списка*/
bool delSocketFromList(int socket, int typeClient);
/*Ищем пару клиенту*/
bool findPairToClient(_STRUCT_POINT_SOCKET *point_s);
/*Старт таймера*/
void time_start(struct timeval *tv1, struct timezone *tz);
/*Стоп таймера (для отсчета таймеров)*/
long time_stop(struct timeval *tv1, struct timezone *tz);
/*Ищем расстояние между точками*/
double getDistance(int x1,int y1,int x2,int y2);
/*Читаем пакет из сокета, и если прочитали, то меняем информацию о точке*/
int readPacketFromServer(int socket, _STRUCT_POINT_SOCKET *point_s);

#endif

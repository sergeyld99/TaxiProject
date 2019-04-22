//#ifndef PacketDeclH
//#define PacketDeclH

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h> 
//---------------------------------------------------------------------------
#define     MAX_QUERY_BODY_LENGTH      512
#define     MAX_REPLY_BODY_LENGTH      512
//---------------------------------------------------------------------------
#define     REJECT                      0
#define     ACK                         1

#define     FIELD_TYPE_STRING           0x01
#define     FIELD_TYPE_FLOAT_           0x02
#define     FIELD_TYPE_INTEGER          0x03
#define     FIELD_TYPE_SYSTIME          0x04
#define     FIELD_TYPE_BYTE             0x05
//---------------------------------------------------------------------------
#define     SUCCESS                          1
#define     ERROR_CONNECTION                -1
#define     ERROR_BAD_PACKET                -2
#define     ERROR_TIMEOUT_EXP               -3

int SendPacket(int socket,char *buffer,int length);
void InsertStringValue(unsigned char *body,int *offset, char* Value);
int SendPacketReject(int Socket,char* Error);
int SendPacketAck(int Socket,char* Message);
int ParseStringValue(unsigned char *body,int *offset,char *Value);
void InsertStringValue(unsigned char *body,int *offset, char* Value);
unsigned char Crc8(unsigned char *pcBlock, unsigned int len);

#pragma pack(1)
//---------------------------------------------------------------------------
/*Заголовок запроса*/
struct _QUERY_PACKET_HEAD{
   unsigned char    PacketType;      //Паасажир или водитель
   int             x;               //Координата X
   int             y;               //Координата Y
   unsigned long   BodyLength;      //Длинна тела
   unsigned char   crc;             //CRC
   //DWORD number_check;
};
typedef struct _QUERY_PACKET_HEAD QUERY_PACKET_HEAD;
//---------------------------------------------------------------------------
struct _REPLY_PACKET_HEAD{
   unsigned char   PacketType;
   unsigned int  BodyLength;
};

typedef struct _REPLY_PACKET_HEAD REPLY_PACKET_HEAD;
//---------------------------------------------------------------------------
struct _REPLY_PACKET{
   REPLY_PACKET_HEAD head;
   unsigned char body[MAX_REPLY_BODY_LENGTH];
} ;
typedef struct _REPLY_PACKET REPLY_PACKET;
//---------------------------------------------------------------------------
struct _QUERY_PACKET{
   QUERY_PACKET_HEAD head;
   unsigned char body[MAX_QUERY_BODY_LENGTH];
};
typedef struct _QUERY_PACKET QUERY_PACKET;


#pragma pack()

//---------------------------------------------------------------------------


//#endif

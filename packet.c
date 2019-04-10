//#ifndef PacketDeclH
//#define PacketDeclH

#include <string.h>
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
// MY FUNCTIONS
int SendPacket(int socket,char *buffer,int length)
{
   int length_0 = length;
   int Result = send(socket,buffer,length_0,0);
   return Result;
}
//---------------------------------------------------------------------------
//Добавим строку к пакету
//---------------------------------------------------------------------------
void InsertStringValue(unsigned char *body,int *offset, char* Value)
{
   *(unsigned char *)(body+*offset) = FIELD_TYPE_STRING;
   *offset++;
   *(unsigned short *)(body+*offset) = (unsigned short)strlen(Value);
   *offset += sizeof(unsigned short);
   memcpy(body+*offset,Value,strlen(Value));
   *offset += (int)strlen(Value);
}
//---------------------------------------------------------------------------
int SendPacketReject(int Socket,char* Error)
{
   REPLY_PACKET packet;
   memset((void *)&packet,0,sizeof(REPLY_PACKET));
   packet.head.PacketType = REJECT;

   int offset = 0;
   InsertStringValue(packet.body,&offset,Error);

   packet.head.BodyLength = (unsigned short)offset;
   int PacketLength = (int)sizeof(packet.head)+(int)offset;

   if(SendPacket(Socket,(char *)&packet,PacketLength)!=PacketLength)
       return ERROR_CONNECTION;
   return SUCCESS;
}
//---------------------------------------------------------------------------
int SendPacketAck(int Socket,char* Message)
{
   REPLY_PACKET packet;
   memset((void *)&packet,0,sizeof(REPLY_PACKET));
   packet.head.PacketType = ACK;

   int offset = 0;
   InsertStringValue(packet.body,&offset,Message);

   packet.head.BodyLength = (unsigned short)offset;
   int PacketLength = (int)sizeof(packet.head)+(int)offset;

   if(SendPacket(Socket,(char *)&packet,PacketLength)!=PacketLength)
       return ERROR_CONNECTION;
   return SUCCESS;
}

/*
  Name  : CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт(127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/
unsigned char Crc8(unsigned char *pcBlock, unsigned int len)
{
    unsigned char crc = 0xFF;
    unsigned int i;

    while (len--)
    {
        crc ^= *pcBlock++;

        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }

    return crc;
}

//#endif

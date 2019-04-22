#include "packet.h"
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
   (*offset)++;
   *(unsigned short *)(body+*offset) = (unsigned short)strlen(Value);
   *offset += sizeof(unsigned short);
   memcpy(body+*offset,Value,strlen(Value));
   *offset += (int)strlen(Value);
   //printf("*offset = %i\r\n",*offset);
}
//---------------------------------------------------------------------------
int ParseStringValue(unsigned char *body,int *offset,char *Value)
{
   if(*(unsigned char *)(body+*offset) != FIELD_TYPE_STRING)
       return ERROR_BAD_PACKET;
   (*offset)++;
   unsigned short length = *(unsigned short *)(body+*offset);
   (*offset)+=sizeof(unsigned short);
   char tmpstr[MAX_REPLY_BODY_LENGTH];
   memcpy(tmpstr,(body+*offset),length);
   tmpstr[length] = 0;
   offset += length;
   strcpy(Value,tmpstr);
   return SUCCESS;
}
//---------------------------------------------------------------------------
int SendPacketReject(int Socket,char* Error)
{
   REPLY_PACKET packet;
   memset((void *)&packet,0,sizeof(REPLY_PACKET));
   packet.head.PacketType = REJECT;

   int offset = 0;
   InsertStringValue(packet.body,&offset,Error);
   //printf("offset = %i\r\n",offset);

   packet.head.BodyLength = (unsigned short)offset;
   int PacketLength = (int)sizeof(packet.head)+(int)offset;
   
    //printf("Packet Error %s BodyLength = %i\r\n",Error,packet.head.BodyLength);

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

/*Срверный сокет*/
#include "socket.h"


int main(int argc, char const *argv[]) 
{
     if (startServerSocket()<0)
         exit(EXIT_FAILURE); 
     return 0; 
}

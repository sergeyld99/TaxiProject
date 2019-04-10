/*Срверный сокет*/
#include "socket.c"


int main(int argc, char const *argv[]) 
{
     if (startServerSocket()<0)
         exit(EXIT_FAILURE); 
     return 0;  
}

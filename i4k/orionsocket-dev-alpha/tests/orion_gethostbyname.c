#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <orion/socket/socket.h>

int main(int argc, char** argv)
{
    char ip[16];
    bzero(&ip, 16);
        
    orion_getHostByName("64.233.163.104", ip);
    
    printf("%s\n", ip);
    
    return 0;
}



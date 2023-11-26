#include <sys/socket.h>
#include <fcntl.h>
#include<string.h>
#include <netinet/in.h>
#include<sys/sendfile.h>
int main()
{
int s = socket(AF_INET, SOCK_STREAM, 0); 

struct sockaddr_in addr =
{
    AF_INET, 
    0x901F, // 8080 in hex 
    0 
};



bind(s , &addr , sizeof(addr)); 


    listen(s, 10);

    int client_fd = accept(s, 0, 0);
    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    char * f = buffer + 5; // skip 5 bytes of "GET /" 
    *strchr(f, ' ') = 0 ; // first space
 int open_f =   open(f , O_RDONLY); // open the file 
sendfile(client_fd , open_f , 0 , 256); // send the file

}
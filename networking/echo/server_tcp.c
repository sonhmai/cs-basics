#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

/*
- create a socket
- bind socket to addr and port# specified in addr
- listen (mark the socket as passive socket = accepting incoming connection)
*/
# define PORT 5000
# define BUFFER_SIZE 1024


int main(int argc, char const *argv[])
{
    int serverfd = 0;

    /*
    Create a socket
    ==============

    int socket(int domain, int type, int protocol);

    Socket function creates unbound socket in a communication domain,
    returns a fd that can be used in later function calls that operate on sockets.
    
    protocol 
        0: use default protocol appropriate for requested socket type.
    type: determines semantics of communication over the socket. Most common:
        SOCK_STREAM: (TCP) sequenced, reliable, bidirectional, connection-mode byte streams
        SOCK_DGRAM: (UDP) datagrams, which are connectionless-mode, 
                    unreliable message with fixed max len

    Return
        -1 when error, unsigned int if successful
    */
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1) {
        printf("Error opening socket.\n");
        return -1;
    }

    /*
    Bind to a socket
    ============

    int bind(int socket, const struct sockaddr *address, socklen_t address_len);

    socket
        fd of the socket to be bound. May require process to have appriopriate
        priviledges to use bind() function.
    address
        points to a sockaddr structure containing the address (port and IP addr)
        to be bound to the socket.
        Length and format of address depends on address faminly of the socket.
    address_len
        length of sockaddr structure pointed to by address arg

    */
   struct sockaddr_in address;  // include netinet/in.h to have sockaddr_in
   int addrlen = sizeof(address);
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;

   if (bind(serverfd, (struct sockaddr *)&address, addrlen) < 0) {
       printf("Bind failed.\n");
       return -1;
   }
    printf("Bound successfully.\n");

    // mark socket as listen
    if(listen(serverfd, 2) < 0) {
        printf("Cannot listen on socket.\n");
        return -1;;
    }
    printf("Listening...");

    // accept data from client
    /*
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        
    socketfd
        socket created, bound to local addr, is listening for connections after listen()
    addr
        pointer to struct sockaddr (filled in with address of peer socket)
    
    Returns
        on success, a fd for the accepted socket
        on error, -1
    */
   int client_fd = 0;
   struct sockaddr_in client;
   char buf[BUFFER_SIZE];
    while (1) {
        socklen_t client_len = sizeof(client);
        client_fd = accept(serverfd, (struct sockaddr *) &client, &client_len);
        memset(buf, 0, sizeof(buf));
        int size = read(client_fd, buf, sizeof(buf));
        if ( size < 0 ) {
        perror("read error");
        exit(5);
        }
        printf("received %s from client\n", buf);
        if (write(client_fd, buf, size) < 0) {
        perror("write error");
        exit(6);
        }
        close(client_fd);
    }
    close(serverfd);
    return 0;

}

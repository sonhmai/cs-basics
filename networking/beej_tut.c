/*
ai - address info
sa_ = sockaddr
sin_ = sockaddr_in

Below code taken from this guide
https://beej.us/guide/bgnet/html//index.html
*/

int socketfd; // socket descriptor type int

// prep socket addrs structure for subsequent use, in hostname lookups,
// service name lookups
struct addrinfo {
    int ai_flags;   // AI_PASSIVE, AI_CANONNAME,..
    int ai_family;  // AF_INET, AF_INET6
    int ai_socktype;    // SOCK_STREAM, SOCK_DGRAM
    int ai_protocol;    // use 0 for any
    size_t ai_addrlen; // size of 
}
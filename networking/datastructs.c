/*
Data structures in network programming
*/

// consider for the Internet

struct sockaddr {
    unsigned short sa_family; // AF_INET
    char sa_data[14]; // IP and port we want to connect or bind to
};

// same size as sockaddr, created to not have to put IP and port
// into sa_data which is inconvenient to write and retrieve 
// (IP and port not separated but both stored in array sa_data).
// Usually, programmer uses this and cast it to above structure.
struct sockaddr_in {
    short sin_family;
    unsigned short sin_port; // PORT NUMBER short 2 byte
    struct in_addr sin_addr; // IP address 4 byte
    char sin_zero[8]; // 2 + 4 + 8 = 14byte in total same as sa_data
};

struct in_addr {
    unsigned long s_addr; // 4 byte long
};

// https://www.youtube.com/watch?v=d9pmc7oObkw watch this - cont
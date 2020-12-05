# Review Questions

1. Difference between connection-based socket and connectionless socket?
2. Sequence of system calls to create a simple server listening on TCP socket localhost port 5000 in C?
3. Why bind() not needed in client?
   - because connect() in client does an implicit bind("0.0.0.0", 0) if one has not been done previously (zero = any). All sockets must bind, where TCP or UDP or other, they just are not always explicitly done.
   - for outgoing connections, this is preferred. OS will bind to all interfaces and pick high-numbered, unused port.
   - only need to bind on client if server expects client coming from a specific port or port range.

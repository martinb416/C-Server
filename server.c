/*
 * Binds a socket to the host machine and begins listening.
 * Handles the polling/receiving of new connections
 *
 * Author: Martin Buitrago
 * 2018
*/

#include "common.h"
#include "server.h"

#define LISTEN_QUEUE	32

/*
 * Set up and tear down the server structs, bind to a port, and start listening
 * Returns the socket descriptor bound to the server
*/
int startup(char *port){
	struct addrinfo info, *addr;
	int sock, result;

	memset(&info, 0, sizeof(struct addrinfo));
    info.ai_family = AF_UNSPEC; // Might need to force AF_INET for IPV4
    info.ai_socktype = SOCK_STREAM;
    info.ai_flags = AI_PASSIVE;
    info.ai_protocol = IPPROTO_TCP;

	if((result = getaddrinfo(LOCALHOST, port, &info, &addr)) != 0) {
	    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(result));
	    exit(result);
	}

	sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if(sock == -1){
		perror("Socket");
		exit(errno);
	}else{
		// Allows port reuse
		int iSetOption = 1;
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, 
			sizeof(iSetOption));

		if((result = bind(sock, addr->ai_addr, addr->ai_addrlen)) != 0){
			perror("Bind");
			close(sock);
			exit(errno);
		}

		// Success!
		freeaddrinfo(addr);
	}

	
	if((result = listen(sock, LISTEN_QUEUE)) != 0){
		perror("Listen");
		close(sock);
		exit(errno);
	}

	return sock;
}

// TODO: pointer to prog arg port/ip needs security review
void *run_server(void *port){
	int bound_socket = startup((char*)port);


	return 0;
}
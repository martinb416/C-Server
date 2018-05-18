/*
 * Test driver for server connections
 *
 * Author: Martin Buitrago
 * 2018
*/

#include "common.h"
#include "server.h"

int main(){
	int sock, result;

	/* Get the address informtation and connect to the server */
	struct addrinfo info, *addr;
	memset(&info, 0, sizeof(struct addrinfo));
    info.ai_family = AF_UNSPEC; // TODO: Change if changed in server.c
    info.ai_socktype = SOCK_STREAM;
    info.ai_flags = AI_PASSIVE;
    info.ai_protocol = IPPROTO_TCP;

    result = getaddrinfo(LOCALHOST, DEF_PORT, &info, &addr);
    if(result != 0){
    	fprintf(stderr, "getaddrinfo Error\n");
    }
    sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (sock < 0){
        fprintf(stderr, "Socket Error\n");
        exit(-1);
    }
    int iSetOption = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption,
        sizeof(iSetOption));
    result = connect(sock, addr->ai_addr, addr->ai_addrlen);
    if(result < 0){
		close(sock);
		perror("client");
		exit(errno);
    }

	return printf("Client Didn't Crash\n");
}

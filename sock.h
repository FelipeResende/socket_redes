#ifndef SOCK_H
#define SOCK_H

//#include <sys/types.h>
#include <sys/socket.h> // socket(), bind()
#include <arpa/inet.h> // htons()
#include <netdb.h> // struct hostent

//#include <netinet/in.h>

//#include <string.h>
//#include <stdlib.h>
//#include <errno.h>

#ifndef	INADDR_NONE
#define	INADDR_NONE	0xffffffff
#endif	/* INADDR_NONE */

int sock_conn(const char *host, const char *service, const char *transport);
int sock_bind(int port, int n_connections);
int sock_accept(int sock_desc);

#endif

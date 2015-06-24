#ifndef SOCK_H
#define SOCK_H

int sock_conn(const char *host, const int port);
int sock_bind(int port, int n_connections);
int sock_accept(int sock_desc);

#endif

#include "sock.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int sock_conn(const char *host, const int port)
{
  struct sockaddr_in client;
  struct hostent *he;
  struct in_addr **addr_list;
  struct servent *pse;
  char ip[100];
  int i, socket_desc;

  // Cria o socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_desc == -1) return -1;

  // Pega o IP
  if ( (he = gethostbyname(host)) == NULL) return -1;
  else memcpy(&client.sin_addr, he->h_addr, he->h_length);

  client.sin_family = AF_INET;
  client.sin_port = htons(port);

  if (connect(socket_desc, (struct sockaddr *)&client, sizeof(client)) < 0)
  {
    puts("Connect error!");
  }
  return socket_desc;
}

int sock_bind(int port, int n_connections)
{
  int socket_desc;
  struct sockaddr_in server;

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_desc == -1) return -1;

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  if (bind(socket_desc, (const struct sockaddr *)&server, sizeof(server)) < 0) return -2;

  listen(socket_desc, n_connections);

  return socket_desc;
}

int sock_accept(int sock_desc)
{
  struct sockaddr_in client;
  int c = sizeof(struct sockaddr_in);
  int new_socket = accept(sock_desc, (struct sockaddr *)&client, (socklen_t *)&c);

  return new_socket;
}

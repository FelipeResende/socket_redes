#include "sock.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int sock_conn(const char *host, const char *service, const char *transport)
{
  struct sockaddr_in client;
  struct hostent *he;
  struct in_addr **addr_list;
  struct servent *pse;
  char ip[100];
  int i, socket_desc;

  client.sin_family = AF_INET;
  // Cria o socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_desc == -1) return -1;

  // Pega o IP
  if ( (he = gethostbyname(host)) == NULL) return -1;

  addr_list = (struct in_addr **)he->h_addr_list;

  for (i = 0; addr_list[i] != NULL; i++)
  {
    strcpy(ip, inet_ntoa(*addr_list[i]));
  }

  // Pega a porta
  if ((pse = getservbyname(service, transport)))
    client.sin_port = pse->s_port;
  else
    printf("Erro para achar a porta!\n");

  printf("Porta num: %d\n", client.sin_port);

  return 0;
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

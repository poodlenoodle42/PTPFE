#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
int punch(const struct sockaddr_in *target, int socket_desc);

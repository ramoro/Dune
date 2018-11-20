#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


class Socket{
private:
	int fd;
	int port;
	struct addrinfo *ptr;
	void fill_addrinfo(struct addrinfo *hints, int flag);
	int socket_connect();
	explicit Socket(int fd);

public:
	Socket();
	Socket(char ip[], char port[]);
	Socket(char port[], int listen_size);
	void socket_bind_and_listen(int cant_conex_espera);
	void close_socket();
	void send_msj(unsigned char *text,int size);
	void send_string(std::string text);
	int recv_msj(unsigned char *text,int max);
	int recv_int();
	void send_int(int number);
	int recv_string(int size, std::string &text);
	void close_send_channel();
	void close_recv_channel();
	Socket* accept_connection();
	~Socket();
	//Constructor por copia anulado
  	Socket(const Socket& other) = delete;
  	//Asignacion por copia anulada
  	Socket& operator=(const Socket &other) = delete;
  	//Constructor por movimiento
  	Socket(Socket&& other); 
  	//Asignacion por movimiento
  	Socket& operator=(Socket&& other);

};


#endif /* SOCKET_H_ */


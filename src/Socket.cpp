#include "Socket.h"
#include "socket_error.h"
#include <vector>
#include <string>


//PRIVATE

Socket::Socket(int file_desc){
	this->fd=file_desc;
}


int Socket::socket_connect(){
	return connect(this->fd, this->ptr->ai_addr, \
this->ptr->ai_addrlen);
}


void Socket::fill_addrinfo(struct addrinfo *hints, int flag){
	memset(hints, 0, sizeof(struct addrinfo));
   	hints->ai_family = AF_INET;
   	hints->ai_socktype = SOCK_STREAM;
   	hints->ai_flags = flag;
}


//PUBLIC


//crea socket servidor
Socket::Socket(char port[],int listen_size){
	struct addrinfo hints;
	int s;
	fill_addrinfo(&hints,AI_PASSIVE);
	if ((s = getaddrinfo(NULL, port, &hints, &(this->ptr))) != 0) {
		throw SocketError("Error de socket: fallo addrinfo servidor.\n");
	}
	this->fd = socket(this->ptr->ai_family, this->ptr->ai_socktype,\
this->ptr->ai_protocol);
	if (this->fd == -1) {
		freeaddrinfo(this->ptr);
		throw SocketError("Error de socket: fallo creacion servidor.\n");
	}
	int val = 1;
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1) {
		throw SocketError("Error de socket: no se pudo setear el sockopt.\n");
	}
	socket_bind_and_listen(listen_size);
}


void Socket::socket_bind_and_listen(int cant_conex_espera){
	if (bind(this->fd, this->ptr->ai_addr, this->ptr->ai_addrlen) == -1) {
      	close(this->fd);
      	freeaddrinfo(this->ptr);
	throw SocketError("Error de socket: no se pudo bindear el servidor.\n");
    } 
    freeaddrinfo(this->ptr);
    if (listen(this->fd, cant_conex_espera) == -1) {
    	close(this->fd);
		throw SocketError("Error de socket: fallo en escucha de servidor.\n");
    }
}


Socket* Socket::accept_connection(){
	int peerskt = 0;
	peerskt = accept(this->fd, NULL, NULL);
	if (peerskt>0){
		return (new Socket(peerskt));
	} else {
		throw SocketError("Error de socket: no se pudo aceptar el cliente.\n");
	}
}


//crea socket client
Socket::Socket(char ip[], char port[]){
	struct addrinfo hints;
	struct addrinfo *result;
	int s;
	fill_addrinfo(&hints,0);
   	if ((s = getaddrinfo(ip, port, &hints, &result)) != 0) { 
    	printf("Error in getaddrinfo: %s\n", gai_strerror(s));
		throw SocketError("Error de socket: fallo addrinfo cliente.\n");
	}
	bool conectado = false;
	for (this->ptr = result; this->ptr != NULL && conectado == false; \
this->ptr = this->ptr->ai_next) {
		this->fd = socket(this->ptr->ai_family, this->ptr->ai_socktype,\
this->ptr->ai_protocol);
		if (this->fd == -1) {
			continue;
		} else {
			conectado = true;
			if(socket_connect() == -1) {
				conectado = false;
			}
		}
	}
	freeaddrinfo(result);
	if (!conectado){
		throw SocketError("Error de socket: fallo conexion cliente.\n");
	}
}


void Socket::send_msj(unsigned char *text,int size){
	int bytes_sent=0;
	bool still_open=true;
	while((size>bytes_sent)&&(still_open)){
		int sent=send(this->fd,&(text[bytes_sent]),size-bytes_sent,MSG_NOSIGNAL);
		if(sent<0){
			still_open=false;
		} else if (sent==0){
			still_open=false;
		} else {
			bytes_sent=bytes_sent+sent;
		}
	}
}


int Socket::recv_msj(unsigned char *text,int max){
	int bytes_recv=0;
	bool still_open=true;
	while((max>bytes_recv)&&(still_open)){
		int recieved=recv(this->fd,&(text[bytes_recv]),max-bytes_recv,0);
		if(recieved<0){
			still_open=false;
		} else if (recieved==0){
			still_open=false;
		} else {
			bytes_recv=bytes_recv+recieved;
		}
	}
	return bytes_recv;
}


void Socket::send_string(std::string text,int size){
	unsigned char **t=reinterpret_cast<unsigned char**>(&text);
	this->send_msj(*t,size);
}


int Socket::recv_string(int size, std::string& recv){
	unsigned char *text_recieved=new unsigned char [size];
	int recieved=this->recv_msj(text_recieved,size);
	std::vector<unsigned char> text(text_recieved,text_recieved+size);
	std::string ret(text.begin(), text.end());
	recv=std::move(ret);
	delete[] text_recieved;
	return recieved;
}


int Socket::recv_int(){
	unsigned char int_size;
	int recv=this->recv_msj(&int_size,1);
	int size=(int)int_size;
	if((recv>0)&&(size>0)){
		unsigned char *text=new unsigned char[size];
		this->recv_msj(text,size);
		int *number=((int*)text);
		int finish=ntohl(*number);
		delete[] text;
		return finish;
	} else {
		return -2;
	}
}


void Socket::send_int(int number){
	unsigned char size=(unsigned char)sizeof(int);
	this->send_msj(&size,1);
	int to_send=htonl(number);
	this->send_msj((unsigned char *)&to_send,(int)size);
}


void Socket::close_socket(){
	shutdown(this->fd,0);
}


void Socket::close_send_channel(){
	shutdown(this->fd,SHUT_WR);
}


void Socket::close_recv_channel(){
	shutdown(this->fd,SHUT_RD);
}


Socket::~Socket(){
	shutdown(this->fd,0);
	close(this->fd);
}


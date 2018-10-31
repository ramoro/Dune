#include "fake_client.h"
#include <iostream>

Cliente::Cliente(const char *ip, const char *puerto) {
  //Socket *sckt = new Socket;
  //socket = sckt;

  //socket->create(servicename, hostname, false);	
	socket = new Socket(ip, puerto);
}

Cliente::operar() {
	char *codigo;
	while(true) {
		socket.recv_msj(codigo, 1);
		if(*codigo == 's') break;
		if(*codigo == 'e') {
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
		} else if (*codigo == 't') {
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
			std::cout << socket.recv_int() << std::endl;
		}
	}
}

Cliente::~Cliente() {
	delete socket;
}

#include "fake_client.h"
#include <iostream>
#include <string>

Cliente::Cliente(const char *ip, const char *puerto) {
  //Socket *sckt = new Socket;
  //socket = sckt;

  //socket->create(servicename, hostname, false);	
	socket = new Socket(ip, puerto);
}

Cliente::operar() {
	char *codigo;
	std::string mensaje("e|0|7|33|4");
	socket->send_int(mensaje.size());
	socket->send_string(mensaje, mensaje.size());
}

Cliente::~Cliente() {
	delete socket;
}

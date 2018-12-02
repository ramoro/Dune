#include "server.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <ratio>
//#include "socket_error.h"

using namespace std::chrono;

Server::Server(char *servicename, int max_cant_escucha_clientes,
OrganizadorJuegos &organizador): organizador_juegos(organizador) {
	socket = new Socket(servicename, max_cant_escucha_clientes);
}

void Server::run() {
	/*Partida partida;
	std::vector<std::shared_ptr<ColaBloqueante>> colas;
  	//partida.agregar_jugador("harkonnen", colas);
  	//partida.agregar_jugador("ordos", &cola);
  	OrganizadorJuegos org;
  	int i = 0;
  	while (i < 1) {
  		Socket *otro_socket = socket->accept_connection();
  		otro_socket->send_int(i);
  		org.agregar_cliente(std::move(*otro_socket));
  		//otro_socket->send_int(1);
  		//otro_socket->send_int(1);
  		//otro_socket->send_int(150000);
 		//otro_socket->send_int(150000);
 		//int aux = otro_socket->recv_int(); 
 		//aux++;
  		if ( i == 0) {
  			std::shared_ptr<Juego> juego(new Juego());
  			juegos.push_back(juego);
  			//juegos[0]->agregar_jugador(std::move(*otro_socket), "harkonnen");
  		} else {
			//juegos[0]->agregar_jugador(std::move(*otro_socket), "ordos");  			
  		}		
  		delete otro_socket;
  		i++;
  	}
	juegos[0]->run();*/
	while(true) {
		try {
			Socket *otro_socket = socket->accept_connection();
			organizador_juegos.agregar_cliente(std::move(*otro_socket));
			delete otro_socket;
		} catch (...) {
			break;
		}
	}
}

/*void Server::aceptar_cliente() {
	while(!server_finalizado) {
		try {
			Socket *otro_socket = socket->accept_connection();
			std::thread *t = new std::thread(&Server::ejecutar_accion, this, 
			otro_socket);
			threads.push_back(t);	
		} catch(const SocketError &e) {
			continue;
		}	
	}
}*/

void Server::apagar() {
	socket->close_socket();
}

Server::~Server() {
	delete socket;
}
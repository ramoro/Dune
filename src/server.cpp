#include "server.h"
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#include "partida.h"
//#include "socket_error.h"

#define MOVER 'm'
#define ATACAR 'a'
#define CREAR_EDIFICIO 'e'
#define CREAR_UNIDAD 'u'

Server::Server(char *servicename) {
	socket = new Socket(servicename, 10);
	server_finalizado = false;
}

void Server::enviar_info_vectores_enteros(std::vector<std::vector<int>> &data,
char *codigo) {
	for (std::vector<std::vector<int>>::iterator it = 
	data.begin(); it != data.end(); ++it) {
		socket->send_msj((unsigned char*)codigo, 1);
		for (std::vector<int>::iterator it2 = (*it).begin();
		it2 != (*it).end(); ++it2) {
			socket->send_int(*it2);
		}
	}
}

void Server::aceptar_cliente() {
	Socket *otro_socket = socket->accept_connection();
	enviar_mapa(otro_socket);
	/*Partida partida;
  	partida.agregar_jugador("je");
  	partida.agregar_jugador("asd");
  	bool agregado = partida.agregar_edificio(0, std::pair<int, int>(50,50), 6);
	otro_socket->send_int(1);
	std::pair<int, std::pair<int,int>> nueva_unidad = partida.agregar_unidad_movible(0, 0);
	otro_socket->send_int(nueva_unidad.first);//mando id
	otro_socket->send_int((nueva_unidad.second).first);//mando su coordx
	otro_socket->send_int((nueva_unidad.second).second);//mando coordy
	agregado = partida.agregar_edificio(1, std::pair<int, int>(150,150), 6);
	otro_socket->send_int(1);
	nueva_unidad = partida.agregar_unidad_movible(0, 2);
	otro_socket->send_int(nueva_unidad.first);//mando id
	otro_socket->send_int((nueva_unidad.second).first);//mando su coordx
	otro_socket->send_int((nueva_unidad.second).second);//mando coordy*/

	delete otro_socket;


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

void Server::ejecutar_accion(Socket *otro_socket) {
	/*while(true) {
		if(server_finalizado) break;
		unsigned char *accion;
  		otro_socket->recv_msj(accion, 1);
	
		if (*accion == MOVER) {
			std::cout << "claa" << std::endl;
		} else if (*accion == ATACAR) {
			
		} else if (*accion == CREAR_EDIFICIO) {
			
		} else if (*accion == CREAR_UNIDAD) {
			
		}
	}*/
	delete otro_socket;
}

void Server::enviar_mapa(Socket* otro_socket) {
	std::vector<std::vector<int>> edificios = {{0, 0, 1, 300,
	300, 50, 50}, {1, 1, 1, 300, 300, 1000, 1000}};
	std::vector<std::vector<int>> terrenos = {{0, 500, 500, 50, 50},
	{2, 200, 200, 700, 700}};
	std::cout << "envia1" << std::endl;
	//char codigo_edificio = 'e';
	//char codigo_terreno = 't';
	//enviar_info_vectores_enteros(edificios, &codigo_edificio);
	//enviar_info_vectores_enteros(terrenos, &codigo_terreno);
	unsigned char codigo = 's';
	otro_socket->send_msj(&codigo, 1);
	std::cout << "envia2" << std::endl;
}

void Server::apagar() {
	server_finalizado = true;
	unsigned int i = 0;
	while(i < threads.size()) {
		threads[i]->join();
		delete threads[i];
		i++;
	}
}

Server::~Server() {
	delete socket;
}
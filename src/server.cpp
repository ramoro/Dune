#include "server.h"
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
//#include "socket_error.h"

#define MINIMA_LONGITUD_NOMBRE_MAPA 4

Server::Server(char *servicename, int max_cant_escucha_clientes,
OrganizadorJuegos &organizador): organizador_juegos(organizador) {
	socket = new Socket(servicename, max_cant_escucha_clientes);
	/*Codigo para leer los nombres de los archivos de un directorio
	extraido de: http://www.forosdelweb.com/f96/
	como-obtener-nombre-directorio-contenido-1073420/
	*/
	DIR *ID_Directorio;
	dirent *Directorio;
	ID_Directorio = opendir("../mapas");
        
	while ((Directorio = readdir(ID_Directorio)) != NULL) {
		std::cout << Directorio->d_name << "\n";
		if (strlen(Directorio->d_name) < MINIMA_LONGITUD_NOMBRE_MAPA) continue;
		organizador_juegos.agregar_mapa(Directorio->d_name);
	}
	closedir(ID_Directorio);
}

void Server::run() {
	/*Partida partida;
	std::vector<std::shared_ptr<ColaBloqueante>> colas;
  	//partida.agregar_jugador("harkonnen", colas);
  	//partida.agregar_jugador("ordos", &cola);
  	OrganizadorJuegos org;
  	int i = 0;
  	while (i < 2) {
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
			juegos[0]->agregar_jugador(std::move(*otro_socket), "atreides");  			

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
	organizador_juegos.apagar();
}

Server::~Server() {
	delete socket;
}
#include "server.h"
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include "socket_error.h"

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
		if (strlen(Directorio->d_name) < MINIMA_LONGITUD_NOMBRE_MAPA) continue;
		organizador_juegos.agregar_mapa(Directorio->d_name);
	}
	closedir(ID_Directorio);
}

void Server::run() {
	
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

void Server::apagar() {
	socket->close_socket();
	organizador_juegos.apagar();
}

Server::~Server() {
	delete socket;
}
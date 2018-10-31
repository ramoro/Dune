#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "partida.h"
#include "Socket.h"

/*Clase que representa a un server el juego Dune.*/
class Server {
	private:
		std::vector<Partida> partidas;
		Socket socket;

	public:
		/*Constructor de la clase.*/
		Server(const char *servicename);

		/*Recibe un vector de vectores de int y un codigo indicando si se enviaran
		edificios o terrenos y se envia toda la data por socket al cliente.*/
		Server::enviar_info_vectores_enteros(std::vector<std::vector<int>> &data,
		char *codigo);

		/*Envia todos los datos del mapa para que el cliente lo pueda 
		dibujar.*/
		Server::enviar_mapa();
};

#endif 
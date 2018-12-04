#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"
#include "organizador_juegos.h"
#include "thread.h"
#include <thread>

/*Clase que representa a un server del juego Dune en la cual se aceptan
los diferentes cliente que van ingresando al server. Corre en un hilo
de ejecucion propio.*/
class Server: public Thread {
	private:
		Socket *socket;
		OrganizadorJuegos &organizador_juegos;

	public:
		/*Constructor de la clase.*/
		Server(char *servicename, int max_cant_escucha_clientes,
		OrganizadorJuegos &organizador);

		/*Metodo que acepta los clientes y los va agregando
		al organizador del juego.*/
		void run();

		/*Apaga el servidor haciendole un shutdown a su socket.*/
		void apagar();

		/*Destructor de la clase.*/
		~Server();
};

#endif 
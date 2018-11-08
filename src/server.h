#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <mutex>
#include <thread>
//#include "partida.h"
#include "Socket.h"

/*Clase que representa a un server el juego Dune.*/
class Server {
	private:
		//std::vector<Partida> partidas;
		Socket *socket;
		std::vector<std::thread*> threads;
		bool server_finalizado;
		std::mutex mutex;

	public:
		/*Constructor de la clase.*/
		Server(char *servicename);

		/*Recibe un vector de vectores de int y un codigo indicando si se enviaran
		edificios o terrenos y se envia toda la data por socket al cliente.*/
		void enviar_info_vectores_enteros(std::vector<std::vector<int>> &data,
		char *codigo);

		void aceptar_cliente();

		/*Envia todos los datos del mapa para que el cliente lo pueda 
		dibujar.*/
		void enviar_mapa(Socket* otro_socket);

		/*Recibe un puntero al socket de un cliente y ejecuta
		la accion pedida por el mismo.*/
		void ejecutar_accion(Socket *otro_socket);

		/*Apaga el servidor joineando todos los hilos y dejando de aceptar
		clientes.*/
		void apagar();

		/*Destructor de la clase.*/
		~Server();
};

#endif 
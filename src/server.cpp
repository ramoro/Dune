#include "server.h"

Server::Server(const char *servicename) {
	Socket socket(servicename, 10);
}

void Server::enviar_info_vectores_enteros(std::vector<std::vector<int>> &data,
char *codigo) {
	for (std::vector<std::vector<int>>::iterator it = 
	data.begin(); it != data.end(); ++it) {
		socket.send_msj(codigo);
		for (std::vector<int>::iterator it2 = (*it).begin();
		it2 != (*it).end(); ++it2) {
			socket.send_int(*it2);
		}
	}
}

void Server::aceptar_cliente() {
	Socket *otro_socket = socket->aceptar();
	
	delete otro_socket;
}

void Server::enviar_mapa() {
	std::vector<std::vector<int>> edificios = {{0, 0, 1, 300,
	300, 50, 50}, {1, 1, 1, 300, 300, 1000, 1000}}
	std::std::vector<std::vector<int>> terrenos = {{0, 500, 500, 50, 50},
	{2, 200, 200, 700, 700}}
	enviar_info_vectores_enteros(edificios, 'e');
	enviar_info_vectores_enteros(terrenos, 't');
	socket.send_msj('s');
}
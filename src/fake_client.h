#ifndef FAKE_CLIENT_H
#define FAKE_CLIENT_H

#include <vector>
#include "partida.h"
#include "Socket.h"

/*Clase que representa a un mapa del mundo Dune.*/
class Cliente {
	private:
		Socket socket;

	public:
		/*Constructor de la clase.*/
		Cliente(const char *ip, const char *puerto);

		operar();

		~Cliente();
};

#endif 
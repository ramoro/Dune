#include "organizador_juegos.h"
#include "juego.h"
#include "protocolo_cliente.h"

#define TAM_COLA 1000

OrganizadorJuegos::OrganizadorJuegos() {
	contador_id_clientes = 0;
	contador_id_juegos = 0;
}

void OrganizadorJuegos::agregar_cliente(Socket sckt_cliente) {
	int id_cliente = contador_id_clientes;
	sckt_cliente.send_int(id_cliente);
    std::shared_ptr<ProtocoloCliente> cliente_nuevo(new 
  	ProtocoloCliente(std::move(sckt_cliente), id_cliente, *this));
	this->clientes.emplace(std::pair<int, std::shared_ptr<ProtocoloCliente>>
	(id_cliente, cliente_nuevo));
	// << "se agrego nuevo cliente con id " << id_cliente << std::endl; 
	contador_id_clientes++;
	cliente_nuevo->iniciar_protocolo_en_salas();
}

int OrganizadorJuegos::crear_juego() {
	std::shared_ptr<Partida> part(new Partida());
	std::shared_ptr<Juego> juego_nuevo(new Juego(part));
	partidas.emplace(std::pair<int, std::shared_ptr<Partida>>(
	contador_id_juegos, part));
  	juegos.emplace(std::pair<int, std::shared_ptr<Juego>>(contador_id_juegos,
  	juego_nuevo));
	int id_juego_nuevo = contador_id_juegos;
	contador_id_juegos++;
	return id_juego_nuevo;
}

void OrganizadorJuegos::iniciar_juego(int id_juego) {
	for (std::map<int, std::shared_ptr<ProtocoloCliente>>::iterator it = 
	clientes.begin(); it != clientes.end(); ++it) {
		if (it->second->pedir_id_juego_asociado() == id_juego) {
			it->second->cambiar_a_modo_juego();
			juegos.at(id_juego)->agregar_jugador(it->second,
			"harkonnen");
		}
	}

	// << "se inicio juego" << std::endl;
	juegos.at(id_juego)->start();
}

OrganizadorJuegos::~OrganizadorJuegos() {
	for (std::map<int, std::shared_ptr<Juego>>::iterator it = 
	juegos.begin(); it != juegos.end(); ++it) {
		it->second->join();
	}
}
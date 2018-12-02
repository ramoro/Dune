#include "organizador_juegos.h"
#include "juego.h"
#include "protocolo_cliente.h"
#include "sala.h"

#define TAM_COLA 1000

OrganizadorJuegos::OrganizadorJuegos() {
	contador_id_clientes = 1;
	contador_id_salas = 0;
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

int OrganizadorJuegos::crear_sala() {
	std::shared_ptr<Partida> part(new Partida());
	std::shared_ptr<Juego> juego_nuevo(new Juego(part));
	std::shared_ptr<Sala> sala_nueva(new Sala(juego_nuevo, part));
	salas.emplace(std::pair<int, std::shared_ptr<Sala>>(contador_id_salas,
  	sala_nueva));
	int id_sala_nueva = contador_id_salas;
	contador_id_salas++;
	return id_sala_nueva;
}

void OrganizadorJuegos::iniciar_juego(int id_sala) {
	for (std::map<int, std::shared_ptr<ProtocoloCliente>>::iterator it = 
	clientes.begin(); it != clientes.end(); ++it) {
		if (it->second->pedir_id_sala_asociada() == id_sala) {
			it->second->cambiar_a_modo_juego();
			salas.at(id_sala)->agregar_jugador_a_juego(it->second,
			"harkonnen");
		}
	}

	// << "se inicio juego" << std::endl;
	salas.at(id_sala)->largar_juego();
	
}

OrganizadorJuegos::~OrganizadorJuegos() {
	/*for (std::map<int, std::shared_ptr<Juego>>::iterator it = 
	juegos.begin(); it != juegos.end(); ++it) {
		it->second->join();
	}*/
}
#include "organizador_juegos.h"
#include "juego.h"
#include "protocolo_cliente.h"
#include "sala.h"

#define TAM_COLA 1000

OrganizadorJuegos::OrganizadorJuegos() {
	contador_id_clientes = 1;
	contador_id_salas = 0;
	contador_id_mapas = 0;
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

int OrganizadorJuegos::crear_sala(int id_mapa, int max_jugadores) {
	std::unique_lock<std::mutex> lock(mutex);
	std::shared_ptr<Partida> part(new Partida(mapas.at(id_mapa)));
	std::shared_ptr<Juego> juego_nuevo(new Juego(part));
	std::shared_ptr<Sala> sala_nueva(new Sala(juego_nuevo, part, 
	mapas.at(id_mapa), max_jugadores));
	salas.emplace(std::pair<int, std::shared_ptr<Sala>>(contador_id_salas,
  	sala_nueva));
	int id_sala_nueva = contador_id_salas;
	contador_id_salas++;
	return id_sala_nueva;
}

void OrganizadorJuegos::iniciar_juego(int id_sala) {
	std::unique_lock<std::mutex> lock(mutex);
	for (std::map<int, std::shared_ptr<ProtocoloCliente>>::iterator it = 
	clientes.begin(); it != clientes.end(); ++it) {
		if (it->second->pedir_id_sala_asociada() == id_sala) {
			it->second->cambiar_a_modo_juego();
			salas.at(id_sala)->agregar_jugador_a_juego(it->second);
		}
	}
	salas.at(id_sala)->cerrar_sala();
	// << "se inicio juego" << std::endl;
	salas.at(id_sala)->largar_juego();
	
}

void OrganizadorJuegos::recorrer_mapas_para_enviar(int id_cliente) {
	std::unique_lock<std::mutex> lock(mutex);
	for (std::map<int, std::string>::iterator it = mapas.begin();
	it != mapas.end(); ++it) {
		clientes.at(id_cliente)->enviar_mapa_o_sala(it->second, it->first);
	}
}

void OrganizadorJuegos::recorrer_salas_para_enviar(int id_cliente) {
	std::unique_lock<std::mutex> lock(mutex);
	for (std::map<int, std::shared_ptr<Sala>>::iterator it = salas.begin();
	it != salas.end(); ++it) {
		if (!(it->second->esta_llena())) { 
			clientes.at(id_cliente)->enviar_mapa_o_sala(
			it->second->pedir_nombre_mapa(), it->first);
		}
	}
}

void OrganizadorJuegos::agregar_cliente_a_sala(int id_sala) {
	std::unique_lock<std::mutex> lock(mutex);
	salas.at(id_sala)->agregar_cliente();
}

void OrganizadorJuegos::agregar_mapa(std::string nombre_mapa) {
	mapas.emplace(std::pair<int, std::string> (contador_id_mapas, 
	nombre_mapa));
	contador_id_mapas++;
}

void OrganizadorJuegos::desconectar_cliente(int id_cliente) {
	std::unique_lock<std::mutex> lock(mutex);
	int id_sala_asociada = clientes.at(id_cliente)->pedir_id_sala_asociada();
	clientes_desconectados.insert(clientes.at(id_cliente));
	if (id_sala_asociada != -1) {
		salas.at(id_sala_asociada)->sacar_cliente();
	}
	clientes.erase(id_cliente);
}

void OrganizadorJuegos::apagar() {
	for (std::map<int, std::shared_ptr<ProtocoloCliente>>::iterator it = 
	clientes.begin(); it != clientes.end(); ++it) {
		if(it->second->esta_esperando_para_jugar()) {
			clientes_desconectados.insert(clientes.at(it->first));
		}
	}
}

OrganizadorJuegos::~OrganizadorJuegos() {
	for(std::set<std::shared_ptr<ProtocoloCliente>>::iterator it =
	clientes_desconectados.begin(); it != clientes_desconectados.end(); it++) {
		std::cout << "destructor org juegos" << std::endl;
		(*it)->joinear_hilo_espera_a_jugar();
	}
}
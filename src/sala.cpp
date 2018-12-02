#include "sala.h"
#include "juego.h"
#include "protocolo_cliente.h"

Sala::Sala(std::shared_ptr<Juego> juego, std::shared_ptr<Partida> partida):
juego(juego), partida(partida) {}

void Sala::agregar_jugador_a_juego(std::shared_ptr<ProtocoloCliente> jugador,
std::string casa) {
	juego->agregar_jugador(jugador, casa);
}

void Sala::largar_juego() {
	juego->start();
}

Sala::~Sala() {
	juego->join();
}

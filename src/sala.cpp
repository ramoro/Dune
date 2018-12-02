#include "sala.h"
#include "juego.h"
#include "protocolo_cliente.h"

Sala::Sala(std::shared_ptr<Juego> juego, std::shared_ptr<Partida> partida,
std::string nombre_mapa, int cantidad_maxima_jugadores):
juego(juego), partida(partida), nombre_mapa(nombre_mapa), 
cantidad_maxima_jugadores(cantidad_maxima_jugadores) {
	cantidad_jugadores_dentro = 1;
	sala_llena = false;
}

void Sala::agregar_jugador_a_juego(std::shared_ptr<ProtocoloCliente> jugador,
std::string casa) {
	juego->agregar_jugador(jugador, casa);
}

void Sala::largar_juego() {
	juego->start();
}

void Sala::agregar_cliente() {
	cantidad_jugadores_dentro += 1;
	if (cantidad_maxima_jugadores == cantidad_jugadores_dentro) {
		sala_llena = true;
	}
}

std::string Sala::pedir_nombre_mapa() {
	return nombre_mapa;
}

bool Sala::esta_llena() {
	return sala_llena;
}

void Sala::cerrar_sala() {
	sala_llena = true;
}

Sala::~Sala() {
	juego->join();
}

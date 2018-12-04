#include "sala.h"
#include "juego.h"
#include "protocolo_cliente.h"

Sala::Sala(std::shared_ptr<Juego> juego, std::shared_ptr<Partida> partida,
std::string nombre_mapa, int cantidad_maxima_jugadores, int id_creador):
juego(juego), partida(partida), nombre_mapa(nombre_mapa), 
cantidad_maxima_jugadores(cantidad_maxima_jugadores), id_creador(id_creador) {
	cantidad_jugadores_dentro = 1;
	sala_llena = false;
	juego_empezado = false;
}

void Sala::agregar_jugador_a_juego(std::shared_ptr<ProtocoloCliente> jugador) {
	juego->agregar_jugador(jugador);
}

void Sala::largar_juego() {
	juego_empezado = true;
	try {
		juego->start();
	} catch(...) {
		std::cout << "Error desconocido en Sala::largar_juego" << std::endl;
	}
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

bool Sala::tiene_juego_empezado() {
	return juego_empezado;
}

void Sala::joinear_juego() {
	juego->join();
}

void Sala::sacar_cliente() {
	cantidad_jugadores_dentro -= 1;
	sala_llena = false;
}

int Sala::pedir_id_creador() {
	return id_creador;
}

Sala::~Sala() {
	if (juego_empezado) {
		juego->join();
	}
}

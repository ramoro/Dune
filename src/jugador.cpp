#include "jugador.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include <iostream>
#include <algorithm>

#define NO_ESTA_ENTRENANDO -1

Jugador::Jugador(Config &config) {
	dinero = config["Jugadores"].get("dinero", 0).asInt();
	capacidad_especia = 0;
	capacidad_especia_disponible = 0;
	energia_disponible = 0;
	casa = -1;
}

void Jugador::agregar_edificio(Edificio* edificio, 
int id_objeto, std::pair<int, int> centro) {
	reducir_dinero(edificio->obtener_costo());
	energia_disponible += edificio->obtener_aporte_energetico();
	if (edificios_por_tipo.count(edificio->pedir_id_tipo()) > 0) {
		(edificios_por_tipo.at(edificio->pedir_id_tipo()))++;
	} else {
		edificios_por_tipo.insert(std::pair<int, 
		int>(edificio->pedir_id_tipo(), 1));
	}
}

void Jugador::reducir_dinero(int valor) {
	dinero -= valor;
}

void Jugador::eliminar_edificio(std::shared_ptr<Edificio> edificio) {
	energia_disponible -= edificio->obtener_aporte_energetico();
	(edificios_por_tipo.at(edificio->pedir_id_tipo()))--;
}

void Jugador::aumentar_dinero(int valor) {
	dinero += valor;
}

bool Jugador::agregado_edificio(ObjetoDune* objeto) {
	if (objeto->obtener_costo() > dinero) return false;
	return true;
}

void Jugador::aumentar_capacidad_especia(int capacidad) {
	capacidad_especia += capacidad;
	capacidad_especia_disponible += capacidad;
}

void Jugador::reducir_capacidad_especia(int cap_a_reducir) {
	capacidad_especia -= cap_a_reducir;
	if (capacidad_especia_disponible - cap_a_reducir < 0) {
		capacidad_especia_disponible = 0;
	} else {
		capacidad_especia_disponible -= cap_a_reducir;
	}
}

bool Jugador::agregada_unidad(UnidadMovible* unidad) {
	std::vector<int> casas= unidad->obtener_casa();
	if (unidad->obtener_costo() > dinero || (std::find(casas.begin(),
	 casas.end(), casa) == casas.end())){
		return false;
	}
	bool creacion = true;
	std::vector<int> edificios_necesitados = unidad->
	obtener_edificios_necesarios();
	for (std::vector<int>::iterator it = edificios_necesitados.begin();
	it != edificios_necesitados.end(); ++it) {
		if (*it == 66 ){
			if ((edificios_por_tipo.count(6) > 0) && (edificios_por_tipo.at(6) > 0)){
				continue;
			} else if ((edificios_por_tipo.count(7) > 0) && (edificios_por_tipo.at(7) > 0)){
				continue;
			} else if ((edificios_por_tipo.count(8) > 0) && (edificios_por_tipo.at(8) > 0)){
				continue;
			} else {
				creacion = false;
				break;
			}
		} else {
			if (edificios_por_tipo.count(*it) == 0) {
				creacion = false;
				break;
			}
			if (edificios_por_tipo.at(*it) == 0) {
				creacion = false;
				break;
			}
		}
	}
	return creacion;
}

int Jugador::pedir_energia_disponible() {
	return energia_disponible;
}

void Jugador::agregar_tipo_unidad_entrenando(int id_tipo_unidad, 
int id_edificio_que_entrena) {
	unidades_entrenando.emplace(std::pair<int, int>(id_tipo_unidad,
	id_edificio_que_entrena));
}

void Jugador::sacar_tipo_unidad_entrenandose(int id_tipo_unidad) {
	unidades_entrenando.erase(id_tipo_unidad);
}

bool Jugador::tiene_tipo_de_unidad_entrenando(int id_tipo_unidad) {
	if (unidades_entrenando.count(id_tipo_unidad) > 0) return true;
	return false;
}

int Jugador::agregar_especia(int cant_especia) {
	if (capacidad_especia_disponible - cant_especia < 0) {
		int especia_agregada = capacidad_especia_disponible;
		capacidad_especia_disponible = 0;
		return especia_agregada;
	} else {
		capacidad_especia_disponible -= cant_especia;
		return cant_especia;
	}
}

int Jugador::pedir_dinero() {
	return dinero;
}

int Jugador::obtener_casa() {
	return casa;
}

void Jugador::asignar_casa(int id_casa) {
	casa = id_casa;
}

std::map<int ,int> Jugador::pedir_unidades_entrenandose() {
	return unidades_entrenando;
}

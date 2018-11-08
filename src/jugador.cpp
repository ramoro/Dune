#include "jugador.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"

Jugador::Jugador(std::string casa, Root &root): casa(casa) {
	//dinero = 100000000; //INICIO DE DINERO DE UN JUGADOR -->HACER SETEABLE
	dinero = root["Jugadores"].get("dinero", 0).asInt();
	std::cout << "dinero inicial " << dinero << std::endl; 
	capacidad_especia = 0;
	capacidad_especia_disponible = 0;
}

void Jugador::agregar_edificio(Edificio* edificio, 
int id_objeto, std::pair<int, int> centro) {
	//int costo = edificio->obtener_costo();
	//if (costo > dinero) return false;
	reducir_dinero(edificio->obtener_costo());
	energia_disponible += edificio->obtener_aporte_energetico();
	//edificios.insert(std::pair<int, std::shared_ptr<Edificio>>(id_edificio, 
	//edificio));
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

void Jugador::eliminar_edificio(Edificio *edificio) {
	//edificios.erase(id_edificio);
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
	if (unidad->obtener_costo() > dinero) return false;
	bool creacion = true;
	std::vector<int> edificios_necesitados = unidad->
	obtener_edificios_necesarios();
	for (std::vector<int>::iterator it = edificios_necesitados.begin();
	it != edificios_necesitados.end(); ++it) {
		if (edificios_por_tipo.count(*it) <= 0) {
			creacion = false;
			break;
		}
		if (edificios_por_tipo.at(*it) == 0) {
			creacion = false;
			break;
		}
	}
	return creacion;
}
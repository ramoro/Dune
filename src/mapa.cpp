#include "mapa.h"
#include "Terrenos/no_especia.h"

//INICIALIAZDOR DE MAPA HARDCODEADO
Mapa::Mapa() {
	for (int i = 0; i < 100; i++) {
		std::vector<Coordenada> fila;
		for (int j = 0; j < 100; j++) {
			NoEspecia roca("roca");
			Coordenada coord(0, roca);
			fila.push_back(coord);
		}
		coordenadas.push_back(fila);
	}
}

bool Mapa::agregar_objeto(ObjetoDune objeto, int id_objeto, 
std::pair<int, int> posicion) {
	bool agregado = coordenadas[std::get<0>(posicion)][std::get<1>(posicion)].
	poner_objeto(&objeto);

	if (agregado) {
		mapa_objetos_posiciones.insert(std::pair<int, std::pair<ObjetoDune,
		std::pair<int, int>>>(id_objeto, std::pair<ObjetoDune, std::pair<int, 
		int>>(objeto, posicion)));
	}
	return agregado;
}

std::string Mapa::pedir_terreno_coordenada(std::pair<int, int> posicion) {
	return coordenadas[std::get<0>(posicion)][std::get<1>(posicion)].
	obtener_terreno();
}

int Mapa::pedir_id_tipo_objeto(int id_objeto) {
	return std::get<0>(mapa_objetos_posiciones.at(id_objeto))
	.pedir_id_tipo();
}

void Mapa::eliminar_objeto(int id_objeto) {
	std::pair<int, int> posicion_objeto = obtener_posicion_objeto(id_objeto);
	mapa_objetos_posiciones.erase(id_objeto);
	coordenadas[std::get<0>(posicion_objeto)][std::get<1>(posicion_objeto)].
	sacar_objeto();
}

bool Mapa::daniar_objeto(int danio, int id_objeto) {
	if (std::get<0>(mapa_objetos_posiciones.at(id_objeto)).
	reducir_vida(danio) <= 0) {
		eliminar_objeto(id_objeto);
		return true;
	} else {
		return false;
	}
}

int Mapa::pedir_costo_objeto(int id_objeto) {
	return std::get<0>(mapa_objetos_posiciones.at(id_objeto)).
	obtener_costo();
}

std::pair<int, int> Mapa::obtener_posicion_objeto(int id_objeto) {
	return std::get<1>(mapa_objetos_posiciones.at(id_objeto));
}
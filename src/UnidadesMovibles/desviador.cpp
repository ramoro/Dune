#include "desviador.h"
#include "../Armas/lanza_misiles.h"

#define ID_DESVIADOR 18 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Desviador::Desviador(int id, int id_duenio, std::pair<int, int> centro) : 
	Vehiculo(5, 12, 4, 400, 300, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_DESVIADOR;
		LanzaMisiles lanza_misiles;
		armas.push_back(LanzaMisiles(lanza_misiles));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(5);
		ids_tipos_edificios_necesarios.push_back(7);
	}

std::vector<int> Desviador::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	std::vector<int> objetivos = UnidadMovible::atacar(mapa, id_objetivo);
	if (!objetivos.empty()) {
		mapa.cambiar_equipo(id_objetivo, this->id_duenio);
	}
	return objetivos;
}

std::vector<int> Desviador::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<int> vecinos_afectados;
	return vecinos_afectados;
}
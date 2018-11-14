#include "desviador.h"
#include "../Armas/lanza_misiles.h"

#define ID_DESVIADOR 18 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Desviador::Desviador(int id, int id_duenio, std::pair<int, int> centro,
 Root &root) : 
	Vehiculo(root["Desviador"].get("rango", 0).asInt(),
	 root["Desviador"].get("velocidad", 0).asInt(),
	 root["Desviador"].get("tiempo_entrenamiento", 0).asFloat(),
	 root["Desviador"].get("costo", 0).asInt(), 
	 root["Desviador"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["Desviador"].get("dimension_ancho", 0).asInt(),
	 root["Desviador"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_DESVIADOR;
		LanzaMisiles lanza_misiles(root);
		armas.push_back(LanzaMisiles(lanza_misiles));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		for (unsigned int i = 0; i < root["Desviador"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(root["Desviador"]["edificios_necesarios"][i].asInt());
		}
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
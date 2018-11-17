#include "cosechadora.h"

#define ID_COSECHADORA 20 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Cosechadora::Cosechadora(int id, int id_duenio, std::pair<int, int> centro,
 Root &root) : 
	Vehiculo(root["Cosechadora"].get("rango", 0).asInt(),
	 root["Cosechadora"].get("velocidad", 0).asInt(),
	 root["Cosechadora"].get("tiempo_entrenamiento", 0).asFloat(),
	 root["Cosechadora"].get("costo", 0).asInt(), 
	 root["Cosechadora"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["Cosechadora"].get("dimension_ancho", 0).asInt(),
	 root["Cosechadora"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_COSECHADORA;
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		for (unsigned int i = 0; i < 
		root["Cosechadora"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			root["Cosechadora"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> Cosechadora::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> aux;
	return aux;
}

void Cosechadora::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> Cosechadora::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}


#include "cosechadora.h"

#define ID_COSECHADORA 20 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Cosechadora::Cosechadora(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Vehiculo(config["Cosechadora"].get("rango", 0).asInt(),
	 config["Cosechadora"].get("velocidad", 0).asInt(),
	 config["Cosechadora"].get("tiempo_entrenamiento", 0).asFloat(),
	 config["Cosechadora"].get("costo", 0).asInt(), 
	 config["Cosechadora"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Cosechadora"].get("dimension_ancho", 0).asInt(),
	 config["Cosechadora"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_COSECHADORA;
		for (unsigned int i = 0; i < 
		config["Cosechadora"]["casas"].size(); i++) {
			casa.push_back(config["Cosechadora"]["casas"][i].asString());
		}	
		for (unsigned int i = 0; i < 
		config["Cosechadora"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Cosechadora"]["edificios_necesarios"][i].asInt());
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


#include "desviador.h"
#include "../Armas/lanza_misiles.h"

#define ID_DESVIADOR 18 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Desviador::Desviador(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Vehiculo(config["Desviador"].get("rango", 0).asInt(),
	 config["Desviador"].get("velocidad", 0).asInt(),
	 config["Desviador"].get("tiempo_entrenamiento", 0).asFloat(),
	 config["Desviador"].get("costo", 0).asInt(), 
	 config["Desviador"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Desviador"].get("dimension_ancho", 0).asInt(),
	 config["Desviador"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_DESVIADOR;
		LanzaMisiles lanza_misiles(config);
		armas.push_back(LanzaMisiles(lanza_misiles));
		for (unsigned int i = 0; i < 
		config["Desviador"]["casas"].size(); i++) {
			casa.push_back(config["Desviador"]["casas"][i].asString());
		}
		for (unsigned int i = 0; i < 
		config["Desviador"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Desviador"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> Desviador::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> aux;
	return aux;
	/*std::vector<int> objetivos = UnidadMovible::atacar(mapa, id_objetivo);
	if (!objetivos.empty()) {
		mapa.cambiar_equipo(id_objetivo, this->id_duenio);
	}
	return objetivos;VERR!!*/ 
}

void Desviador::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> Desviador::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}
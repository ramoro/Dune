#include "infanteria_pesada.h"
#include "../Armas/lanza_misiles.h"

#define ID_INFANTERIA_PESADA 11 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaPesada::InfanteriaPesada(int id, int id_duenio, std::pair<int, int>
centro, Config &config) : 
	UnidadInfanteria(config["InfanteriaPesada"].get("rango", 0).asInt(),
	 config["InfanteriaPesada"].get("velocidad", 0).asInt(), 
	 config["InfanteriaPesada"].get("tiempo_entrenamiento", 0).asInt(), 
	 config["InfanteriaPesada"].get("costo", 0).asInt(), 
	 config["InfanteriaPesada"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["InfanteriaPesada"].get("dimension_ancho", 0).asInt(), 
	 config["InfanteriaPesada"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_INFANTERIA_PESADA;
		LanzaMisiles lanza_misiles(config);
		armas.push_back(LanzaMisiles(lanza_misiles));
		for (unsigned int i = 0; i < 
		config["InfanteriaPesada"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["InfanteriaPesada"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> InfanteriaPesada::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> objetos_afectados;
	objetos_afectados.push_back(mapa.obtener_objeto(id_objetivo));
	return objetos_afectados;
}

void InfanteriaPesada::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> InfanteriaPesada::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}

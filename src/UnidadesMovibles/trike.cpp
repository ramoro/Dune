#include "trike.h"
#include "../Armas/rifle_asalto.h"

#define ID_TRIKE 14 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Trike::Trike(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Vehiculo(config["Trike"].get("rango", 0).asInt(),
	 config["Trike"].get("velocidad", 0).asInt(),
	 config["Trike"].get("tiempo_entrenamiento", 0).asFloat(),
	 config["Trike"].get("costo", 0).asInt(), 
	 config["Trike"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Trike"].get("dimension_ancho", 0).asInt(),
	 config["Trike"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_TRIKE;
		RifleAsalto rifle_asalto(config);
		armas.push_back(RifleAsalto(rifle_asalto));
		for (unsigned int i = 0; i < 
		config["Trike"]["casas"].size(); i++) {
			casa.push_back(config["Trike"]["casas"][i].asString());
		}
		for (unsigned int i = 0; i < 
		config["Trike"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Trike"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> Trike::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	std::vector<ObjetoDune*> objetos_afectados;
	objetos_afectados.push_back(mapa.obtener_objeto(id_objetivo));
	return objetos_afectados;
}

void Trike::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> Trike::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}

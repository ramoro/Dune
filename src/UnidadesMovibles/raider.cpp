#include "raider.h"
#include "../Armas/canion_22mm.h"

#define ID_RAIDER 15 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Raider::Raider(int id, int id_duenio, std::pair<int, int> centro,Config &config) : 
	Vehiculo(config["Raider"].get("rango", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Raider"].get("velocidad", 0).asInt(),
	 config["Raider"].get("tiempo_entrenamiento", 0).asFloat(),
	 config["Raider"].get("costo", 0).asInt(), 
	 config["Raider"].get("puntos_vida", 1000).asInt(), id, id_duenio, 
	 config["Raider"].get("dimension_ancho", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Raider"].get("dimension_alto", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(), centro) {
		id_tipo = ID_RAIDER;
		Canion22mm canion22mm(config);
		armas.push_back(Canion22mm(canion22mm));
		for (unsigned int i = 0; i < 
		config["Raider"]["casas"].size(); i++) {
			casa.push_back(config["Raider"]["casas"][i].asInt());
		}		
		for (unsigned int i = 0; i < 
		config["Raider"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Raider"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> Raider::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	std::vector<ObjetoDune*> objetos_afectados;
	objetos_afectados.push_back(mapa.obtener_objeto(id_objetivo));
	return objetos_afectados;
}

void Raider::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> Raider::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}

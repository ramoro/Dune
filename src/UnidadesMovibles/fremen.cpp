#include "fremen.h"
#include "../Armas/lanza_misiles.h"
#include "../Armas/rifle_asalto.h"

#define ID_FREMEN 12 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Fremen::Fremen(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	UnidadInfanteria(config["Fremen"].get("rango", 0).asInt(),
	 config["Fremen"].get("velocidad", 0).asInt(), 
	 config["Fremen"].get("tiempo_entrenamiento", 0).asInt(), 
	 config["Fremen"].get("costo", 0).asInt(), 
	 config["Fremen"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Fremen"].get("dimension_ancho", 0).asInt(), 
	 config["Fremen"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_FREMEN;
		RifleAsalto rifle_asalto(config);
		LanzaMisiles lanza_misiles(config);
		armas.push_back(RifleAsalto(rifle_asalto));
		armas.push_back(LanzaMisiles(lanza_misiles));
		for (unsigned int i = 0; i < 
		config["Fremen"]["casas"].size(); i++) {
			casa.push_back(config["Fremen"]["casas"][i].asString());
		}	
		for (unsigned int i = 0; i < 
		config["Fremen"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Fremen"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> Fremen::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> objetos_afectados;
	objetos_afectados.push_back(mapa.obtener_objeto(id_objetivo));
	return objetos_afectados;
}

void Fremen::matar() {
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> Fremen::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}

#include "sardaukar.h"
#include "../Armas/rifle_asalto.h"
#include "../Armas/lanza_misiles.h"

#define ID_SARDAUKAR 13 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Sardaukar::Sardaukar(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	UnidadInfanteria(config["Sardaukar"].get("rango", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Sardaukar"].get("velocidad", 0).asInt(), 
	 config["Sardaukar"].get("tiempo_entrenamiento", 0).asInt(), 
	 config["Sardaukar"].get("costo", 0).asInt(), 
	 config["Sardaukar"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Sardaukar"].get("dimension_ancho", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(), 
	 config["Sardaukar"].get("dimension_alto", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(), centro) {
		id_tipo = ID_SARDAUKAR;
		RifleAsalto rifle_asalto(config);
		LanzaMisiles lanza_misiles(config);
		armas.push_back(RifleAsalto(rifle_asalto));
		armas.push_back(LanzaMisiles(lanza_misiles));
		for (unsigned int i = 0; i < 
		config["Sardaukar"]["casas"].size(); i++) {
			casa.push_back(config["Sardaukar"]["casas"][i].asInt());
		}	
		for (unsigned int i = 0; i < 
		config["Sardaukar"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Sardaukar"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> Sardaukar::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> objetos_afectados;
	objetos_afectados.push_back(mapa.obtener_objeto(id_objetivo));
	return objetos_afectados;
}

void Sardaukar::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> Sardaukar::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}

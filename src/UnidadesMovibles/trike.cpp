#include "trike.h"
#include "../Armas/rifle_asalto.h"

#define ID_TRIKE 14 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Trike::Trike(int id, int id_duenio, std::pair<int, int> centro,
 Root &root) : 
	Vehiculo(root["Trike"].get("rango", 0).asInt(),
	 root["Trike"].get("velocidad", 0).asInt(),
	 root["Trike"].get("tiempo_entrenamiento", 0).asFloat(),
	 root["Trike"].get("costo", 0).asInt(), 
	 root["Trike"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["Trike"].get("dimension_ancho", 0).asInt(),
	 root["Trike"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_TRIKE;
		RifleAsalto rifle_asalto(root);
		armas.push_back(RifleAsalto(rifle_asalto));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		for (unsigned int i = 0; i < 
		root["Trike"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			root["Trike"]["edificios_necesarios"][i].asInt());
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

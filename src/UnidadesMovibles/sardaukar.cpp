#include "sardaukar.h"
#include "../Armas/rifle_asalto.h"
#include "../Armas/lanza_misiles.h"

#define ID_SARDAUKAR 13 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Sardaukar::Sardaukar(int id, int id_duenio, std::pair<int, int> centro,
 Root &root) : 
	UnidadInfanteria(root["Sardaukar"].get("rango", 0).asInt(),
	 root["Sardaukar"].get("velocidad", 0).asInt(), 
	 root["Sardaukar"].get("tiempo_entrenamiento", 0).asInt(), 
	 root["Sardaukar"].get("costo", 0).asInt(), 
	 root["Sardaukar"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["Sardaukar"].get("dimension_ancho", 0).asInt(), 
	 root["Sardaukar"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_SARDAUKAR;
		RifleAsalto rifle_asalto(root);
		LanzaMisiles lanza_misiles(root);
		armas.push_back(RifleAsalto(rifle_asalto));
		armas.push_back(LanzaMisiles(lanza_misiles));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(6);
		ids_tipos_edificios_necesarios.push_back(7);
	}

std::vector<int> Sardaukar::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}

std::vector<int> Sardaukar::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<int> vecinos_afectados;
	return vecinos_afectados;
}
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
		ids_tipos_edificios_necesarios.push_back(4);
	}

std::vector<int> Trike::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}

std::vector<int> Trike::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<int> vecinos_afectados;
	return vecinos_afectados;
}

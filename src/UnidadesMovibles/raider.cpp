#include "raider.h"
#include "../Armas/canion_22mm.h"

#define ID_RAIDER 15 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Raider::Raider(int id, int id_duenio, std::pair<int, int> centro,Root &root) : 
	Vehiculo(root["Raider"].get("rango", 0).asInt(),
	 root["Raider"].get("velocidad", 0).asInt(),
	 root["Raider"].get("tiempo_entrenamiento", 0).asFloat(),
	 root["Raider"].get("costo", 0).asInt(), 
	 root["Raider"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["Raider"].get("dimension_ancho", 0).asInt(),
	 root["Raider"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_RAIDER;
		Canion22mm canion22mm(root);
		armas.push_back(Canion22mm(canion22mm));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(4);
	}

std::vector<int> Raider::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}

std::vector<int> Raider::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<int> vecinos_afectados;
	return vecinos_afectados;
}
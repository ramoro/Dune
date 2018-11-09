#include "infanteria_pesada.h"
#include "../Armas/lanza_misiles.h"

#define ID_INFANTERIA_PESADA 11 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaPesada::InfanteriaPesada(int id, int id_duenio, std::pair<int, int>
centro, Root &root) : 
	UnidadInfanteria(root["Infanteria pesada"].get("rango", 0).asInt(),
	 root["Infanteria pesada"].get("velocidad", 0).asInt(), 
	 root["Infanteria pesada"].get("tiempo_entrenamiento", 0).asInt(), 
	 root["Infanteria pesada"].get("costo", 0).asInt(), 
	 root["Infanteria pesada"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["Infanteria pesada"].get("dimension_ancho", 0).asInt(), 
	 root["Infanteria pesada"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_INFANTERIA_PESADA;
		LanzaMisiles lanza_misiles(root);
		armas.push_back(LanzaMisiles(lanza_misiles));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(6);
	}

std::vector<int> InfanteriaPesada::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}

std::vector<int> InfanteriaPesada::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<int> vecinos_afectados;
	return vecinos_afectados;
}
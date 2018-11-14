#include "infanteria_pesada.h"
#include "../Armas/lanza_misiles.h"

#define ID_INFANTERIA_PESADA 11 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaPesada::InfanteriaPesada(int id, int id_duenio, std::pair<int, int>
centro, Root &root) : 
	UnidadInfanteria(root["InfanteriaPesada"].get("rango", 0).asInt(),
	 root["InfanteriaPesada"].get("velocidad", 0).asInt(), 
	 root["InfanteriaPesada"].get("tiempo_entrenamiento", 0).asInt(), 
	 root["InfanteriaPesada"].get("costo", 0).asInt(), 
	 root["InfanteriaPesada"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["InfanteriaPesada"].get("dimension_ancho", 0).asInt(), 
	 root["InfanteriaPesada"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_INFANTERIA_PESADA;
		LanzaMisiles lanza_misiles(root);
		armas.push_back(LanzaMisiles(lanza_misiles));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		for (unsigned int i = 0; i < root["InfanteriaPesada"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(root["InfanteriaPesada"]["edificios_necesarios"][i].asInt());
		}
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
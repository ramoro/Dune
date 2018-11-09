#include "fremen.h"
#include "../Armas/lanza_misiles.h"
#include "../Armas/rifle_asalto.h"

#define ID_FREMEN 12 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Fremen::Fremen(int id, int id_duenio, std::pair<int, int> centro,
 Root &root) : 
	UnidadInfanteria(root["Fremen"].get("rango", 0).asInt(),
	 root["Fremen"].get("velocidad", 0).asInt(), 
	 root["Fremen"].get("tiempo_entrenamiento", 0).asInt(), 
	 root["Fremen"].get("costo", 0).asInt(), 
	 root["Fremen"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["Fremen"].get("dimension_ancho", 0).asInt(), 
	 root["Fremen"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_FREMEN;
		RifleAsalto rifle_asalto(root);
		LanzaMisiles lanza_misiles(root);
		armas.push_back(RifleAsalto(rifle_asalto));
		armas.push_back(LanzaMisiles(lanza_misiles));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(6);
		ids_tipos_edificios_necesarios.push_back(7);
	}

std::vector<int> Fremen::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}

std::vector<int> Fremen::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<int> vecinos_afectados;
	return vecinos_afectados;
}

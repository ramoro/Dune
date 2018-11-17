#include "infanteria_ligera.h"
#include "../Armas/rifle_asalto.h"

#define ID_INFANTERIA_LIGERA 10 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaLigera::InfanteriaLigera(int id, int id_duenio, std::pair<int, int>
centro, Root &root) : 
	UnidadInfanteria(root["InfanteriaLigera"].get("rango", 0).asInt(),
	 root["InfanteriaLigera"].get("velocidad", 0).asInt(), 
	 root["InfanteriaLigera"].get("tiempo_entrenamiento", 0).asInt(), 
	 root["InfanteriaLigera"].get("costo", 0).asInt(), 
	 root["InfanteriaLigera"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["InfanteriaLigera"].get("dimension_ancho", 0).asInt(), 
	 root["InfanteriaLigera"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_INFANTERIA_LIGERA;
		RifleAsalto rifle(root);
		armas.push_back(RifleAsalto(rifle));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		for (unsigned int i = 0; i < 
		root["InfanteriaLigera"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			root["InfanteriaLigera"]["edificios_necesarios"][i].asInt());
		}
	}
	

std::vector<ObjetoDune*> InfanteriaLigera::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> objetos_afectados;
	objetos_afectados.push_back(mapa.obtener_objeto(id_objetivo));
	return objetos_afectados;
}

void InfanteriaLigera::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> InfanteriaLigera::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}


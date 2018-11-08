#include "infanteria_ligera.h"
#include "../Armas/rifle_asalto.h"

#define ID_INFANTERIA_LIGERA 10 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaLigera::InfanteriaLigera(int id, int id_duenio, std::pair<int, int>
centro) : 
	UnidadInfanteria(3, 16, 1, 50, 50, id, id_duenio, 2, 2, centro) {
		id_tipo = ID_INFANTERIA_LIGERA;
		RifleAsalto rifle;
		armas.push_back(RifleAsalto(rifle));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(6);
	}

std::vector<int> InfanteriaLigera::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}

std::vector<int> InfanteriaLigera::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<int> vecinos_afectados;
	return vecinos_afectados;
}


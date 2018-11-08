#include "trike.h"
#include "../Armas/rifle_asalto.h"

#define ID_TRIKE 14 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Trike::Trike(int id, int id_duenio, std::pair<int, int> centro) : 
	Vehiculo(4, 64, 2, 100, 80, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_TRIKE;
		RifleAsalto rifle_asalto;
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

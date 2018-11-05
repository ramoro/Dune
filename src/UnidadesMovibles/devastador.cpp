#include "devastador.h"
#include "../Armas/canion_plasma.h"

#define ID_DEVASTADOR 9 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Devastador::Devastador(int id, int id_duenio, std::pair<int, int> centro) : 
	Vehiculo(4, 12, 5, 400, 400, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_DEVASTADOR;
		danio_explosion = 20;
		CanionPlasma canion_plasma;
		armas.push_back(CanionPlasma(canion_plasma));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(5);
		ids_tipos_edificios_necesarios.push_back(7);
	}

std::vector<int> Devastador::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}

std::vector<std::pair<int, int>> Devastador::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<std::pair<int, int>> vecinos_afectados;
	return vecinos_afectados;
}

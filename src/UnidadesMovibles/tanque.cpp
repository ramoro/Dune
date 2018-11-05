#include "tanque.h"
#include "../Armas/canion.h"

#define ID_TANQUE 6 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Tanque::Tanque(int id, int id_duenio, std::pair<int, int> centro) : 
	Vehiculo(4, 40, 4, 400, 30, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_TANQUE;
		Canion canion;
		armas.push_back(Canion(canion));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(5);
	}

std::vector<int> Tanque::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}
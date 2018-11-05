#include "raider.h"
#include "../Armas/canion_22mm.h"

#define ID_RAIDER 5 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Raider::Raider(int id, int id_duenio, std::pair<int, int> centro) : 
	Vehiculo(4, 84, 2, 100, 80, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_RAIDER;
		Canion22mm canion22mm;
		armas.push_back(Canion22mm(canion22mm));
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(4);
	}

std::vector<int> Raider::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	return UnidadMovible::atacar(mapa, id_objetivo);
}
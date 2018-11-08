#include "infanteria_pesada.h"
#include "../Armas/lanza_misiles.h"

#define ID_INFANTERIA_PESADA 11 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaPesada::InfanteriaPesada(int id, int id_duenio, std::pair<int, int>
centro) : 
	UnidadInfanteria(3, 12, 1.3, 70, 80, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_INFANTERIA_PESADA;
		LanzaMisiles lanza_misiles;
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
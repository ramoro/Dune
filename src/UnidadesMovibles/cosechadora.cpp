#include "cosechadora.h"

#define ID_COSECHADORA 10 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Cosechadora::Cosechadora(int id, int id_duenio, std::pair<int, int> centro) : 
	Vehiculo(0, 12, 3, 300, 600, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_COSECHADORA;
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		ids_tipos_edificios_necesarios.push_back(5);
	}

std::vector<int> Cosechadora::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	std::vector<int> objetivos;
	return objetivos;
}

std::vector<int> Cosechadora::matar(Mapa &mapa) { 
	UnidadMovible::eliminar(mapa);
	std::vector<int> vecinos_afectados;
	return vecinos_afectados;
}


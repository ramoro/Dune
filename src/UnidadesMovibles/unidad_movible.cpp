#include "unidad_movible.h"
#include <stdlib.h> 
#include <iostream>

UnidadMovible::UnidadMovible(int rango, int velocidad, 
float tiempo_creacion, int costo_dinero, int vida, int id, int id_duenio,
int base, int altura, std::pair<int, int> centro) :
	ObjetoDune(vida, costo_dinero, id, id_duenio, base, altura, centro),
	rango(rango), velocidad(velocidad), tiempo_creacion(tiempo_creacion){}

int UnidadMovible::pedir_danio(std::string objetivo) {
	int arma_seleccionada = rand() % armas.size();
	return armas[arma_seleccionada].obtener_danio(objetivo);
}

std::vector<int> UnidadMovible::atacar(Mapa &mapa,
int id_objetivo) {
	std::pair<int, int> cercania = mapa.pedir_cercania(this->id, id_objetivo);
	if (cercania.first > this->rango_ataque_fila && cercania.second > 
	this->rango_ataque_columna) {
		//mapa.mover_unidad(this, id_objetivo); aca se desmarca las coordenadas que ocupaba
		//la unidad, se la mueve con A* y se marcan las nuevas coordenadas	
	}
	std::vector<int> objetivo;
	objetivo.push_back(id_objetivo);
	return objetivo;
}

std::vector<int> UnidadMovible::atacar_objetivo(Mapa &mapa, int id_objetivo) {
	std::vector<int> aux;
	return aux;
}

int UnidadMovible::daniar(std::shared_ptr<UnidadMovible> unidad_atacante) {
	return 0;
}

/*std::vector<std::pair<int, int>> UnidadMovible::matar(Mapa &mapa) {
	std::vector<std::pair<int, int>> aux;
	return aux;
}*/

void UnidadMovible::eliminar(Mapa &mapa) {
	mapa.eliminar_objeto(this->id);
}

std::vector<int> UnidadMovible::obtener_edificios_necesarios() {
	return ids_tipos_edificios_necesarios;
}

std::pair<int, int> UnidadMovible::agregar(Mapa &mapa, Jugador 
&jugador) {
	if (!jugador.agregada_unidad(this)) {
		std::pair<int, int> unidad_no_creada(-1, -1);
		return unidad_no_creada;
	}

	std::cout << "unidad en x " << (this->centro).first << " y " << (this->centro).second << std::endl;
	mapa.agregar_objeto(this, this->id,
	this->centro);
	return this->centro;
}
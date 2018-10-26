#ifndef UNIDAD_MOVIBLE_H
#define UNIDAD_MOVIBLE_H

#include "../objeto_dune.h"
#include "../Armas/arma.h"
#include <string>
#include <vector>

/*Clase abstracta que representa una unidad movible en el mundo de Dune
que puede ser tanto un vehiculo como una unidad de infanteria.*/
class UnidadMovible: public ObjetoDune {
	private:
		int rango;
		int velocidad; //en km/h
		float tiempo_creacion; //en minutos

	protected:
		std::vector<Arma> armas;

	public:
		/*Constructor de la clase.*/
		UnidadMovible(int rango, int velocidad, 
		float tiempo_cracion, int costo_dinero, int vida);

		/*Recibe un string con el objetivo al que esta atacando
		la unidad y devuelve el danio que le realiza al objetivo.*/
		int pedir_danio(std::string objetivo);
};

#endif 
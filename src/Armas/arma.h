#ifndef ARMA_H
#define ARMA_H

#include <string>
#include <map>
#include "../src/root.h"

/*Clase abstracta que representa un arma en el mundo de Dune.*/
class Arma {
	private:
		int danio;
		int frecuencia_disparo; //en segundos

	protected:
		std::map<std::string, int> bonificaciones;

	public:
		/*Constructor de la clase.*/
		Arma(int danio, int frecuencia_disparo);

		/*Constructor por copia.*/
		explicit Arma(const Arma& other);

		/*Recibe un string indicando si el objetivo es un edificio, una
		unidad de infanteria o un vehiculo y devuelve el danio que hace
		el arma, sumado a la bonificacion si es que tiene hacia el objetivo.*/
		int obtener_danio(std::string objetivo);
};

#endif 
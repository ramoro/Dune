#ifndef ARMA_H
#define ARMA_H

#include <string>
#include <map>
#include "../src/config.h"

/*Clase abstracta que representa un arma en el mundo de Dune.*/
class Arma {
	private:
		int danio;
		int frecuencia_disparo; //tantos disparos en un segundo
		int contador_seg; //cuenta un segundo en ms y se reinicia

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

		/*Recibe un tiempo determinado que se suma al contador de segundo
		y devuelve true si el arma puede atacar o false en caso contrario.*/
		bool puede_atacar(int tiempo_transcurrido);

		/*Devuelve la frecuencia de disparo del arma.*/
		int obtener_frecuencia_disparo();
};

#endif 
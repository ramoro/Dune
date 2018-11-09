#include "arma.h"
#include <iostream>

Arma::Arma(int danio, int frecuencia_disparo) :
	danio(danio), frecuencia_disparo(frecuencia_disparo){}

Arma::Arma(const Arma& other) {
	danio = other.danio;
	frecuencia_disparo = other.frecuencia_disparo;
	bonificaciones = other.bonificaciones;
}

int Arma::obtener_danio(std::string objetivo) {
	return (danio + bonificaciones.at(objetivo)); 
}
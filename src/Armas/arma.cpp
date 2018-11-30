#include "arma.h"
#include <iostream>

#define SEGUNDO_EN_MILIS 1000

Arma::Arma(int danio, int frecuencia_disparo) :
	danio(danio), frecuencia_disparo(frecuencia_disparo){
		contador_seg = 0;
	}

Arma::Arma(const Arma& other) {
	danio = other.danio;
	frecuencia_disparo = other.frecuencia_disparo;
	bonificaciones = other.bonificaciones;
	contador_seg = other.contador_seg;
}

int Arma::obtener_danio(std::string objetivo) {
	return (danio + bonificaciones.at(objetivo)); 
}

bool Arma::puede_atacar(int tiempo_transcurrido) {
	std::cout << "entro a puede atacar y contador_seg es: " << contador_seg << std::endl;
	contador_seg += tiempo_transcurrido;
	if (contador_seg >= SEGUNDO_EN_MILIS) {
		contador_seg = 0;
		return true;
	}
	return false;
}

int Arma::obtener_frecuencia_disparo() {
	return frecuencia_disparo;
}

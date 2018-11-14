#include "explosion.h"
#include <string>
#include <iostream>

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Explosion::Explosion(std::vector<int> &config_explosion) :
 Arma(config_explosion[0], config_explosion[1]) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 config_explosion[2]));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 config_explosion[3]));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 config_explosion[4]));
	dimesion_altura = 5;
	dimesion_base = 5;
}

int Explosion::pedir_dimension_altura() {
	return dimesion_altura;
}

int Explosion::pedir_dimension_base() {
	return dimesion_base;
}
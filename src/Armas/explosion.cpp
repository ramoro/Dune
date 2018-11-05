#include "explosion.h"
#include <string>

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Explosion::Explosion() : Arma(10, 0) {
	bonificaciones.insert(std::pair<std::string, int>("edificio", 0));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo", 0));
	bonificaciones.insert(std::pair<std::string, int>("infanteria", 0));
}
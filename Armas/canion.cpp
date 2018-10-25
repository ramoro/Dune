#include "canion.h"
#include <string>

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Canion::Canion() : Arma(7, 1) {
	bonificaciones.insert(std::pair<std::string, int>("edificio", 0));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo", 0));
	bonificaciones.insert(std::pair<std::string, int>("infanteria", 0));
}
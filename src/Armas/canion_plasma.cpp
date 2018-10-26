#include "canion_plasma.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
CanionPlasma::CanionPlasma() : Arma(8, 1) {
	bonificaciones.insert(std::pair<std::string, int>("edificio", 2));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo", 2));
	bonificaciones.insert(std::pair<std::string, int>("infanteria", 0));
}
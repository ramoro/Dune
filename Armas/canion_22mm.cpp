#include "canion_22mm.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Canion22mm::Canion22mm() : Arma(6, 6) {
	bonificaciones.insert(std::pair<std::string, int>("edificio", 2));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo", 2));
	bonificaciones.insert(std::pair<std::string, int>("infanteria", 0));
}
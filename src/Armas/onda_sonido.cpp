#include "onda_sonido.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
OndaSonido::OndaSonido() : Arma(4, 1) {
	bonificaciones.insert(std::pair<std::string, int>("edificio", 0));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo", 0));
	bonificaciones.insert(std::pair<std::string, int>("infanteria", 4));
}
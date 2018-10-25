#include "rifle_asalto.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
RifleAsalto::RifleAsalto() : Arma(2, 6) {
	bonificaciones.insert(std::pair<std::string, int>("edificio", 0));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo", 0));
	bonificaciones.insert(std::pair<std::string, int>("infanteria", 1));
}
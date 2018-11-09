#include "canion_plasma.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
CanionPlasma::CanionPlasma(Root &root) : Arma(root["CanionPlasma"].get("danio", 0).asInt(),
	 root["CanionPlasma"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 root["CanionPlasma"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 root["CanionPlasma"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 root["CanionPlasma"].get("bonificacion_danio_infanteria", 0).asInt()));
}
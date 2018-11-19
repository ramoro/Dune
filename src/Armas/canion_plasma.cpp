#include "canion_plasma.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
CanionPlasma::CanionPlasma(Config &config) : Arma(config["CanionPlasma"].get("danio", 0).asInt(),
	 config["CanionPlasma"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 config["CanionPlasma"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 config["CanionPlasma"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 config["CanionPlasma"].get("bonificacion_danio_infanteria", 0).asInt()));
}
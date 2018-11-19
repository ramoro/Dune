#include "canion.h"
#include <string>

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Canion::Canion(Config &config) : Arma(config["Canion"].get("danio", 0).asInt(),
	 config["Canion"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 config["Canion"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 config["Canion"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 config["Canion"].get("bonificacion_danio_infanteria", 0).asInt()));
}

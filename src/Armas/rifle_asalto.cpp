#include "rifle_asalto.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
RifleAsalto::RifleAsalto(Config &config) : Arma(config["RifleAsalto"].get("danio", 0).asInt(),
	 config["RifleAsalto"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 config["RifleAsalto"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 config["RifleAsalto"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 config["RifleAsalto"].get("bonificacion_danio_infanteria", 0).asInt()));
}
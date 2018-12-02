#include "onda_sonido.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
OndaSonido::OndaSonido(Config &config) : Arma(config["OndaSonido"].get("danio", 10).asInt(),
	 config["OndaSonido"].get("frecuencia_disparo", 2).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 config["OndaSonido"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 config["OndaSonido"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 config["OndaSonido"].get("bonificacion_danio_infanteria", 0).asInt()));
}
#include "onda_sonido.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
OndaSonido::OndaSonido(Root &root) : Arma(root["OndaSonido"].get("danio", 0).asInt(),
	 root["OndaSonido"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 root["OndaSonido"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 root["OndaSonido"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 root["OndaSonido"].get("bonificacion_danio_infanteria", 0).asInt()));
}
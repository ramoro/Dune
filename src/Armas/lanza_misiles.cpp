#include "lanza_misiles.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
LanzaMisiles::LanzaMisiles(Config &config) : Arma(config["LanzaMisiles"].get("danio", 0).asInt(),
	 config["LanzaMisiles"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 config["LanzaMisiles"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 config["LanzaMisiles"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 config["LanzaMisiles"].get("bonificacion_danio_infanteria", 0).asInt()));
}
#include "canion_22mm.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Canion22mm::Canion22mm(Config &config) : 
Arma(config["Canion22mm"].get("danio", 0).asInt(),
	 config["Canion22mm"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 config["Canion22mm"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 config["Canion22mm"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 config["Canion22mm"].get("bonificacion_danio_infanteria", 0).asInt()));
}

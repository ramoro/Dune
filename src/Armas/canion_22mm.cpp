#include "canion_22mm.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Canion22mm::Canion22mm(Root &root) : 
Arma(root["Canion22mm"].get("danio", 0).asInt(),
	 root["Canion22mm"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 root["Canion22mm"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 root["Canion22mm"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 root["Canion22mm"].get("bonificacion_danio_infanteria", 0).asInt()));
}

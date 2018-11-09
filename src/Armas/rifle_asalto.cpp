#include "rifle_asalto.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
RifleAsalto::RifleAsalto(Root &root) : Arma(root["RifleAsalto"].get("danio", 0).asInt(),
	 root["RifleAsalto"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 root["RifleAsalto"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 root["RifleAsalto"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 root["RifleAsalto"].get("bonificacion_danio_infanteria", 0).asInt()));
}
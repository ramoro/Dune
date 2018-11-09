#include "lanza_misiles.h"

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
LanzaMisiles::LanzaMisiles(Root &root) : Arma(root["LanzaMisiles"].get("danio", 0).asInt(),
	 root["LanzaMisiles"].get("frecuencia_disparo", 0).asInt()) {
	bonificaciones.insert(std::pair<std::string, int>("edificio",
	 root["LanzaMisiles"].get("bonificacion_danio_edificios", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("vehiculo",
	 root["LanzaMisiles"].get("bonificacion_danio_vehiculo", 0).asInt()));
	bonificaciones.insert(std::pair<std::string, int>("infanteria",
	 root["LanzaMisiles"].get("bonificacion_danio_infanteria", 0).asInt()));
}
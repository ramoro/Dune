#include "terreno.h"

Terreno::Terreno(std::string material): material(material) {}

std::string Terreno::obtener_nombre_material() {
	return material;
}
#include "jugador.h"

bool Jugador::agregar_edificio(Edificio* edificio, int id_edificio,
int id_tipo_edificio) {
	int costo = edificio->obtener_costo();
	if (costo > dinero) return false;
	else {
		reducir_dinero(costo);
		edificios.insert(std::pair<int, Edificio*>(id_edificio, 
		edificio));
		if (edificios_por_tipo.count(id_tipo_edificio) > 0) {
			(edificios_por_tipo.at(id_tipo_edificio))++;
		} else {
			edificios_por_tipo.insert(std::pair<int, 
			int>(id_tipo_edificio, 1));
		}
		return true;
	}
}

void Jugador::reducir_dinero(int valor) {
	dinero -= valor;
}

void Jugador::eliminar_edificio(int id_edificio, int id_tipo_edificio) {
	edificios.erase(id_edificio);
	(edificios_por_tipo.at(id_tipo_edificio))--;
}

void Jugador::aumentar_dinero(int valor) {
	dinero += valor;
}
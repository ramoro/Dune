#include "partida.h"

#define OBJETO_MUERTO -1 //CODIGO PARA ENVIAR POR PROTOCOLO INDICANDO 
//QUE OBJ MURIO

Partida::Partida() {
	contador_ids_jugadores = 0;
	contador_ids_edificios = 0;
}

void Partida::agregar_jugador() {
	Jugador jugador;
	jugadores.insert(std::pair<int, Jugador>(contador_ids_jugadores, 
	jugador));
	contador_ids_jugadores++;
}

bool Partida::agregar_edificio(int id_jugador, std::pair<int, int>
posicion, int id_tipo_edificio) {
	std::string terreno = mapa.pedir_terreno_coordenada(posicion);
	if (terreno != "roca") return false;
	Edificio edificio = fabrica_edificios.crear_edificio(id_tipo_edificio);
	if (!mapa.agregar_objeto(edificio, contador_ids_edificios, posicion)) return false;
	if (!(jugadores.at(id_jugador).agregar_edificio(&edificio, 
	contador_ids_edificios, id_tipo_edificio))) {
		mapa.eliminar_objeto(contador_ids_edificios);
		return false;
	}
	contador_ids_edificios++;
	return true;
}

int Partida::atacar_edificio(int id_jugador_atacado, int id_tipo_unidad_atacante, 
int id_edificio_atacado) {
	UnidadMovible unidad = fabrica_unidades_movibles.crear_unidad_movible(
	id_tipo_unidad_atacante);
	int danio = unidad.pedir_danio("edificio");
	bool objeto_aniquilado = mapa.daniar_objeto(danio, id_edificio_atacado);
	int id_tipo_edificio = mapa.pedir_id_tipo_objeto(id_edificio_atacado);
	if (objeto_aniquilado) {
		jugadores.at(id_jugador_atacado).eliminar_edificio(id_edificio_atacado, 
		id_tipo_edificio);
		return OBJETO_MUERTO;
	}
	return danio;
}

void Partida::autodemoler_edificio(int id_jugador, int id_edificio) {
	int costo_edificio = mapa.pedir_costo_objeto(id_edificio);
	int id_tipo_edificio = mapa.pedir_id_tipo_objeto(id_edificio);
	jugadores.at(id_jugador).eliminar_edificio(id_edificio, id_tipo_edificio);
	mapa.eliminar_objeto(id_edificio);
	jugadores.at(id_jugador).aumentar_dinero(costo_edificio / 2);
}

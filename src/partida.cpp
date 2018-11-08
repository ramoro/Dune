#include "partida.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include <memory>
#include <iostream>

#define OBJETO_MUERTO -1 //CODIGO PARA ENVIAR POR PROTOCOLO INDICANDO 
//QUE OBJ MURIO
#define UNIDAD_NO_AGREGADA -1

Partida::Partida() {
	contador_ids_jugadores = 0;
	contador_ids_objetos = 0;
}

void Partida::agregar_jugador(std::string casa_jugador,Root &root) {
	Jugador jugador(casa_jugador,root);
	jugadores.insert(std::pair<int, Jugador>(contador_ids_jugadores, 
	jugador));
	contador_ids_jugadores++;
}

std::shared_ptr<Edificio> Partida::agregar_edificio(int id_jugador, std::pair<int, int>
posicion_central, int id_tipo_edificio) {
	std::shared_ptr<Edificio> ptr_edificio = fabrica_edificios.crear_edificio(id_tipo_edificio,
	contador_ids_objetos, id_jugador, posicion_central);

	bool agregado = ptr_edificio->agregar_al_juego(mapa, jugadores.at(id_jugador), 
	contador_ids_objetos, id_tipo_edificio);
	if (agregado) {
		edificios.insert(std::pair<int, 
		std::shared_ptr<Edificio>>(contador_ids_objetos, ptr_edificio));
		contador_ids_objetos++;
	} else {
		ptr_edificio = NULL;
	}

	return ptr_edificio;
}

void Partida::ejecutar_ataque(std::vector<int> objetos_afectados, 
std::shared_ptr<UnidadMovible> atacante, std::vector<std::pair<int, int>>
&ids_vidas) {

	for (std::vector<int>::iterator it = objetos_afectados.begin(); 
	it != objetos_afectados.end(); ++it) {
		int vida_restante;
		if (edificios.count(*it) > 0) {
			vida_restante = (edificios.at(*it))->daniar(atacante);
			if (vida_restante <= 0) {
				(edificios.at(*it))->destruir(mapa, 
				jugadores.at((edificios.at(*it))->pedir_id_duenio()));
				edificios.erase(*it);
			}
		} else {
			vida_restante =(unidades_movibles.at(*it))->daniar(atacante);
			if (vida_restante <= 0) {
				std::vector<int> vecinos_afectados = (unidades_movibles.
				at(*it))->matar(mapa);
				if (!vecinos_afectados.empty()) {
					ejecutar_ataque(vecinos_afectados, 
					unidades_movibles.at(*it), ids_vidas);
				}
				unidades_movibles.erase(*it);
			}
		}
		ids_vidas.push_back(std::pair<int, int>(*it, vida_restante));
	}
}

std::vector<std::pair<int, int>> Partida::atacar_objeto(int id_unidad_atacante, 
int id_objeto_atacado) {
	//std::shared_ptr<UnidadMovible> unidad = fabrica_unidades_movibles.crear_unidad_movible(
	//5, 0, 3, std::pair<int, int>(0,0));
	std::vector<int> objetos_afectados = (unidades_movibles.
	at(id_unidad_atacante))->atacar_objetivo(mapa, id_objeto_atacado);
	std::vector<std::pair<int, int>> ids_vidas;
	ejecutar_ataque(objetos_afectados, unidades_movibles.
	at(id_unidad_atacante), ids_vidas);
	return ids_vidas;
}

void Partida::autodemoler_edificio(int id_edificio) {
	(edificios.at(id_edificio))->autodemoler(mapa, jugadores.at(
	(edificios.at(id_edificio))->pedir_id_duenio()));
}

std::pair<int, std::pair<int,int>> Partida::agregar_unidad_movible(
int id_tipo_unidad, int id_edificio) {
	edificios.at(id_edificio)->
	pedir_id_duenio();
	std::shared_ptr<UnidadMovible> unidad = (edificios.at(id_edificio))->
	agregar_unidad(mapa, jugadores.at((edificios.at(id_edificio))->
	pedir_id_duenio()), id_tipo_unidad, contador_ids_objetos);
	std::pair<int, std::pair<int, int>> nueva_unidad;
	if ((unidad->obtener_centro()).first != UNIDAD_NO_AGREGADA) {
		nueva_unidad.first = contador_ids_objetos;
		unidades_movibles.insert(std::pair<int, 
		std::shared_ptr<UnidadMovible>> (contador_ids_objetos, unidad));
		contador_ids_objetos++;
	} else {
		nueva_unidad.first = UNIDAD_NO_AGREGADA;
	}
	nueva_unidad.second = unidad->obtener_centro();
	return nueva_unidad;
}

std::vector<std::pair<int, int>> Partida::mover_unidad(int id_unidad, 
std::pair<int, int> posicion_destino) {
	return mapa.mover(id_unidad, posicion_destino);
}

std::vector<int> Partida::generar_gusano() {
	return mapa.desenterrar_gusano();
}
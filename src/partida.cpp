#include "partida.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include <memory>

#define OBJETO_MUERTO -1 //CODIGO PARA ENVIAR POR PROTOCOLO INDICANDO 
//QUE OBJ MURIO
#define UNIDAD_NO_AGREGADA -1

Partida::Partida() {
	contador_ids_jugadores = 0;
	contador_ids_objetos = 0;
}

void Partida::agregar_jugador(std::string casa_jugador) {
	Jugador jugador(casa_jugador);
	jugadores.insert(std::pair<int, Jugador>(contador_ids_jugadores, 
	jugador));
	contador_ids_jugadores++;
}

bool Partida::agregar_edificio(int id_jugador, std::pair<int, int>
posicion_central, int id_tipo_edificio) {
	std::shared_ptr<Edificio> ptr_edificio = fabrica_edificios.crear_edificio(id_tipo_edificio,
	contador_ids_objetos, id_jugador, posicion_central);

	bool agregado = ptr_edificio->agregar_al_juego(mapa, jugadores.at(id_jugador), 
	contador_ids_objetos, id_tipo_edificio);
	
	if (agregado) {
		edificios.insert(std::pair<int, 
		std::shared_ptr<Edificio>>(contador_ids_objetos, ptr_edificio));
		contador_ids_objetos++;
	}

	return agregado;
}

int Partida::atacar_objeto(int id_jugador_atacado, int id_tipo_unidad_atacante, 
int id_objeto_atacado) {
	std::shared_ptr<UnidadMovible> unidad = fabrica_unidades_movibles.crear_unidad_movible(
	5, 0, 3, std::pair<int, int>(0,0));
	std::vector<int> unidades_afectadas = unidad->atacar_objetivo(mapa, 
	id_objeto_atacado);
	/*std::vector<int, int> ids_vidas;
	for (std::vector<int>::iterator it = unidades_afectadas.begin(); 
	it != unidades_afectadas.end(); ++it) {
		int vida_restante;
		if (edificios.count(*it) > 0) {
			vida_restante = (edificios.at(*it))->daniar(unidad);
			if (vida_restante <= 0) (edificios.at(*it))->destruir(mapa, 
			jugadores.at((edificios.at(*it)).pedir_id_duenio()));
		} else {
			vida_restante =(unidades_movibles.at(*it))->daniar(unidad);
			if (vida_restante <= 0) (unidades_movibles.at(*it))->matar(mapa,
			jugadores.at((unidades_movibles.at(*it)).pedir_id_duenio()));
		}
		ids_vidas.push_back(std::pair<int, int>(*it, vida_restante);
	}*/
	return 9;
}

void Partida::autodemoler_edificio(int id_edificio) {
	(edificios.at(id_edificio))->autodemoler(mapa, jugadores.at(
	(edificios.at(id_edificio))->pedir_id_duenio()));
}

std::pair<int, std::pair<int,int>> Partida::agregar_unidad_movible(
int id_tipo_unidad, int id_edificio) {
	edificios.at(id_edificio);
	edificios.at(id_edificio)->
	pedir_id_duenio();
	std::pair<int, int> pos_unidad_nueva = (edificios.at(id_edificio))->
	agregar_unidad(mapa, jugadores.at((edificios.at(id_edificio))->
	pedir_id_duenio()), id_tipo_unidad, contador_ids_objetos);
	std::pair<int, std::pair<int, int>> nueva_unidad;
	if (pos_unidad_nueva.first != UNIDAD_NO_AGREGADA) {
		nueva_unidad.first = contador_ids_objetos;
		contador_ids_objetos++;
	} else {
		nueva_unidad.first = UNIDAD_NO_AGREGADA;
	}
	nueva_unidad.second = pos_unidad_nueva;
	return nueva_unidad;
}

/*std::stack<std::pair<int, int>> Partida::mover_unidad(int id_unidad, 
int tipo_unidad, std::pair<int, int> posicion_inicial, 
std::pair<int, int> posicion_final) {
	//pedir tipo a la unidad para pasarlo por parametro
	return buscador_mejor_camino.buscar_mejor_camino(mapa, posicion_inicial,
	posicion_final, id_tipo_unidad);
}*/

std::vector<std::pair<int, int>> Partida::generar_gusano() {
	return mapa.desenterrar_gusano();
}
#include "partida.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include "UnidadesMovibles/raider.h"
#include "Edificios/fabrica_ligera.h"
#include <memory>

#define OBJETO_MUERTO -1 //CODIGO PARA ENVIAR POR PROTOCOLO INDICANDO 
//QUE OBJ MURIO

Partida::Partida() {
	contador_ids_jugadores = 0;
	contador_ids_edificios = 0;
	contador_ids_unidades_movibles = 0;
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
	contador_ids_edificios, id_jugador, posicion_central);
	//FabricaLigera edificio(contador_ids_edificios, id_jugador,
	//posicion_central);
	if(!mapa.verificar_terreno_alrededores(posicion_central, 
	ptr_edificio->obtener_altura(), 
	ptr_edificio->obtener_base(), "roca")) return false;
	
	if (!mapa.agregar_objeto(ptr_edificio, contador_ids_edificios,
	posicion_central)) return false;

	if (!(jugadores.at(id_jugador).agregar_edificio(ptr_edificio, 
	contador_ids_edificios, id_tipo_edificio))) {
		mapa.eliminar_objeto(contador_ids_edificios);
		return false;
	}
	contador_ids_edificios++;
	return true;
}

int Partida::atacar_edificio(int id_jugador_atacado, int id_tipo_unidad_atacante, 
int id_edificio_atacado) {
	std::shared_ptr<UnidadMovible> unidad = fabrica_unidades_movibles.crear_unidad_movible(
	5, 0, 3, std::pair<int, int>(0,0));
	int danio = (*unidad).pedir_danio("edificio");
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

/*int Partida::crear_unidad_movible(int id_jugador, int id_tipo_unidad,
	int id_edificio) {
	//UnidadMovible unidad = fabrica_unidades_movibles.
	//crear_unidad_movible(id_tipo_unidad, id_contador_unidades_movibles, id_jugador);
	Raider unidad(0, 0);
	int id_tipo_edificio = mapa.obtener_id_tipo_objeto(id_edificio);
	std::pair<int, int> posicion = mapa.obtener_espacio_unidad(id_edificio); NACHITO TIENE QUE HACER ESTO
	mapa.agregar_objeto(edificio, contador_ids_unidades_movibles, posicion);
	if (!(jugadores.at(id_jugador).unidad_movible_agregada(&unidad, //CREAR ESTE METODO
	contador_ids_edificios, id_tipo_unidad))) {
		mapa.eliminar_objeto(contador_ids_unidades_movibles);
		return false;
	}
	contador_ids_unidades_movibles++;
	return true;
}*/

/*int Partida::atacar_unidad_movible(int id_jugador_atacado, int id_unidad_atacante,
int id_unidad_atacada) {

}*/

/*std::stack<std::pair<int, int>> Partida::mover_unidad(int id_unidad, 
int tipo_unidad, std::pair<int, int> posicion_inicial, 
std::pair<int, int> posicion_final) {
	//pedir tipo a la unidad para pasarlo por parametro
	return buscador_mejor_camino.buscar_mejor_camino(mapa, posicion_inicial,
	posicion_final, id_tipo_unidad);
}*/

/*void Partida::convertir_unidad_enemiga(int id_jugador_atacante,
int unidad_atacada) {
	mapa.cambiar_duenio(unidad_atacada);
}*/

std::vector<std::pair<int, int>> Partida::generar_gusano() {
	return mapa.desenterrar_gusano();
}
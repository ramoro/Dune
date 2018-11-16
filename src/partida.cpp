#include "partida.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include <memory>
#include <iostream>

#define OBJETO_MUERTO -1 //CODIGO PARA ENVIAR POR PROTOCOLO INDICANDO 
//QUE OBJ MURIO
#define UNIDAD_NO_AGREGADA -1

#define CODIGO_CREACION_EDIFICIO_RECHAZADA 'r'

Partida::Partida() {
	contador_ids_jugadores = 0;
	contador_ids_objetos = 0;
	Root json("../src/input.json");
	root = std::move(json);
}

void Partida::agregar_jugador(std::string casa_jugador) {
	Jugador jugador(casa_jugador,root);
	jugadores.emplace(std::pair<int, Jugador>(contador_ids_jugadores, 
	jugador));
	contador_ids_jugadores++;
}

//DEBERIA PASAR COLA BLOQUEANTE
void Partida::agregar_edificio(int id_jugador, std::pair<int, int>
posicion_central, int id_tipo_edificio) {
	std::shared_ptr<Edificio> ptr_edificio = fabrica_edificios.crear_edificio(id_tipo_edificio,
	contador_ids_objetos, id_jugador, posicion_central,root);

	bool agregado = ptr_edificio->agregar_al_juego(mapa, jugadores.at(id_jugador), 
	contador_ids_objetos, id_tipo_edificio);
	if (agregado) {
		edificios.emplace(std::pair<int, 
		std::shared_ptr<Edificio>>(contador_ids_objetos, ptr_edificio));
		contador_ids_objetos++;
		ptr_edificio->serializar_mensaje_creacion_objeto(ptr_edificio);
		/*PARTE COLA BLOQUEANTE/AL SACAR MENSAJE LUEGO DEBO LIMPIAR MENSAJE
		cola.push(ptr_edificio.pedir_mensaje_protocolo());
		*/
	} else {
		MensajeProtocolo mensaje;
		mensaje.asignar_accion(CODIGO_CREACION_EDIFICIO_RECHAZADA);
		mensaje.agregar_parametro(id_tipo_edificio);
	}
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

bool Partida::se_puede_agregar_unidad_movible(int id_tipo_unidad, 
int id_edificio) {
	bool se_puede_agregar = ((edificios.at(id_edificio))->
	se_puede_agregar_unidad(jugadores.at((edificios.at(id_edificio))->
	pedir_id_duenio()), id_tipo_unidad, contador_ids_objetos,root));
	if (se_puede_agregar) {
		contador_ids_objetos++;
		return true;
	}
	return false;
}

void Partida::comenzar_movimiento_unidad(
int id_unidad, std::pair<int, int> posicion_destino) {
	unidades_movibles.at(id_unidad)->empezar_a_mover(mapa, 
	posicion_destino);
}

void Partida::actualizar_creacion_unidades(std::shared_ptr<Edificio> 
edificio, double tiempo_transcurrido) {
	int energia_jugador = jugadores.at(edificio->pedir_id_duenio()).
	pedir_energia_disponible();
	if (energia_jugador < 0) {
		//diminucion del tiempo que paso segun la energia encontra que se tiene
	}
	bool entrenamiento_terminado = edificio->
	avanzar_tiempo_creacion(tiempo_transcurrido);
	if (entrenamiento_terminado) {
		std::shared_ptr<UnidadMovible> unidad_nueva = edificio->
		agregar_unidad(mapa); //VERIFICAR ESTE AGREGADO CON GDB LUEGO
		unidades_movibles.emplace(std::pair<int, 
		std::shared_ptr<UnidadMovible>> (unidad_nueva->pedir_id(), 
		unidad_nueva));
		//mando sus datos por la cola bloqueante
	}
}

//deberia pasarle COLA BLOQUEANTE para desde aca dentro
//mandar el mensaje sobre la unidad agregada
void Partida::actualizar_modelo(double tiempo_transcurrido) {
	mapa.actualizar_salida_gusano(tiempo_transcurrido);
	for (std::map<int, std::shared_ptr<Edificio>>::iterator it_edifs = 
	edificios.begin(); it_edifs != edificios.end(); ++it_edifs) {
		actualizar_creacion_unidades((it_edifs->second), tiempo_transcurrido);
	}
}
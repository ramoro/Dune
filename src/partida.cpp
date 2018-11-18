#include "partida.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include <memory>
#include <iostream>
#include <set>

#define CODIGO_CREACION_EDIFICIO_RECHAZADA 'r'
#define CODIGO_MUERTE_OBJETO 'd'
#define CODIGO_PERDIO_JUGADOR 'e'

Partida::Partida() {
	contador_ids_jugadores = 0;
	contador_ids_objetos = 0;
	Root json("../src/input.json");
	root = std::move(json);
	Mapa map(this->root);
	mapa = std::move(map);
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
		//PARTE COLA BLOQUEANTE/AL SACAR MENSAJE LUEGO DEBO LIMPIAR MENSAJE
		//cola.push(ptr_edificio.pedir_mensaje_protocolo());
	
	} else {
		//lo meto directo en cola bloqueante
		MensajeProtocolo mensaje;
		mensaje.asignar_accion(CODIGO_CREACION_EDIFICIO_RECHAZADA);
		mensaje.agregar_parametro(id_tipo_edificio);
	}
}

void Partida::atacar_objeto(int id_unidad_atacante, 
int id_objeto_atacado) {
	//std::shared_ptr<UnidadMovible> unidad = fabrica_unidades_movibles.crear_unidad_movible(
	//5, 0, 3, std::pair<int, int>(0,0));
	if (edificios.count(id_objeto_atacado) > 0) {
		(unidades_movibles.at(id_unidad_atacante))->iniciar_ataque(mapa, 
		edificios.at(id_objeto_atacado));
	} else {
		(unidades_movibles.at(id_unidad_atacante))->iniciar_ataque(mapa, 
		unidades_movibles.at(id_objeto_atacado));
	}
}

void Partida::autodemoler_edificio(int id_edificio) {
	(edificios.at(id_edificio))->autodemoler(mapa, jugadores.at(
	(edificios.at(id_edificio))->pedir_id_duenio()));
}

void Partida::iniciar_entrenamiento_unidad_movible(int id_tipo_unidad, 
int id_edificio) {
	bool se_puede_agregar = ((edificios.at(id_edificio))->
	se_puede_agregar_unidad(jugadores.at((edificios.at(id_edificio))->
	pedir_id_duenio()), id_tipo_unidad, contador_ids_objetos,root));
	if (se_puede_agregar) {
		contador_ids_objetos++;
		//mando mensaje que se agrego?
	}
	//aca mando mensaje que no se pudo agregar
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
		jugadores.at(edificio->pedir_id_duenio()).setear_no_entrenando();
		//mando sus datos por la cola bloqueante
	}
}

void Partida::eliminar_edificio_del_juego(std::shared_ptr<Edificio> 
edificio_a_remover) {
	jugadores.at(edificio_a_remover->pedir_id_duenio()).
	eliminar_edificio(edificio_a_remover);
	edificios.erase(edificio_a_remover->pedir_id());
	mapa.eliminar_objeto(edificio_a_remover->pedir_id());
}

void Partida::eliminar_unidad_del_juego(std::shared_ptr<UnidadMovible> 
unidad_a_remover) {
	unidades_movibles.erase(unidad_a_remover->pedir_id());
	mapa.eliminar_objeto(unidad_a_remover->pedir_id());
}

//deberia pasarle COLA BLOQUEANTE para desde aca dentro
//mandar el mensaje sobre la unidad agregada
void Partida::actualizar_modelo(double tiempo_transcurrido) {
	//mapa.actualizar_salida_gusano(tiempo_transcurrido);
	for (std::map<int, Jugador>::iterator it_jugadores = 
	jugadores.begin(); it_jugadores != jugadores.end(); ++it_jugadores) {
		int id_edificio_entrenando = (it_jugadores->second).
		pedir_id_edificio_entrenando();
		if (id_edificio_entrenando != -1) {
			//verificacion por si un edificio esta creando una unidad
			//y lo destruyen
			if (edificios.count(id_edificio_entrenando) < 0) {
				(it_jugadores->second).setear_no_entrenando();
				continue;
			}
			actualizar_creacion_unidades(edificios.at(id_edificio_entrenando),
			tiempo_transcurrido);
		}
	}

	for (std::map<int, std::shared_ptr<Edificio>>::iterator it_edifs = 
	edificios.begin(); it_edifs != edificios.end(); ++it_edifs) {
		
		(it_edifs->second)->actualizar_existencia(
		jugadores.at((it_edifs->second)->pedir_id_duenio()));
	}

	for (std::map<int, std::shared_ptr<UnidadMovible>>::iterator it_unidades = 
	unidades_movibles.begin(); it_unidades != unidades_movibles.end(); 
	++it_unidades) {
		(it_unidades->second)->actualizar_unidad(tiempo_transcurrido, mapa);
	}
	
	std::set<std::shared_ptr<Edificio>> edificios_a_eliminar;
	std::set<std::shared_ptr<UnidadMovible>> unidades_a_eliminar;
	for (std::map<int, std::shared_ptr<Edificio>>::iterator it_edifs = 
	edificios.begin(); it_edifs != edificios.end(); ++it_edifs) {
		std::vector<MensajeProtocolo> mensajes = (it_edifs->second)->
		obtener_mensajes_para_mandar();
		for (std::vector<MensajeProtocolo>::iterator it_mensajes = 
		mensajes.begin(); it_mensajes != mensajes.end(); ++it_mensajes) {
			if ((*it_mensajes).pedir_accion() == CODIGO_MUERTE_OBJETO) {
				edificios_a_eliminar.insert(it_edifs->second);
			} else if ((*it_mensajes).pedir_accion() == CODIGO_PERDIO_JUGADOR) {
				int id_jugador_afuera = (it_edifs->second)->pedir_id_duenio();
				for (std::map<int, std::shared_ptr<Edificio>>::iterator it_edifs2 = 
				edificios.begin(); it_edifs2 != edificios.end(); ++it_edifs) {
					if ((it_edifs2->second)->pedir_id_duenio() == 
					id_jugador_afuera) {
						edificios_a_eliminar.insert(it_edifs2->second);
					}
				}
				for (std::map<int, std::shared_ptr<UnidadMovible>>::iterator it_unidades = 
				unidades_movibles.begin(); it_unidades != unidades_movibles.end(); 
				++it_unidades) {
					if ((it_unidades->second)->pedir_id_duenio() == 
					id_jugador_afuera) {
						unidades_a_eliminar.insert(it_unidades->second);
					}
				}
			}
			//encolar menasje en cola bloqueante
		}
		(it_edifs->second)->limpiar_lista_mensajes();
	}

	for (std::map<int, std::shared_ptr<UnidadMovible>>::iterator it_unidades = 
	unidades_movibles.begin(); it_unidades != unidades_movibles.end(); 
	++it_unidades) {
		std::vector<MensajeProtocolo> mensajes = (it_unidades->second)->
		obtener_mensajes_para_mandar();
		for (std::vector<MensajeProtocolo>::iterator it_mensajes = 
		mensajes.begin(); it_mensajes != mensajes.end(); ++it_mensajes) {
			if ((*it_mensajes).pedir_accion() == CODIGO_MUERTE_OBJETO) {
				unidades_a_eliminar.insert(it_unidades->second);
			}
			//encolar mensaje
		}
		(it_unidades->second)->limpiar_lista_mensajes();
	}

	for (std::set<std::shared_ptr<Edificio>>::iterator it_edificios = 
	edificios_a_eliminar.begin(); it_edificios != edificios_a_eliminar.end();
	++it_edificios) {
		eliminar_edificio_del_juego(*it_edificios);
	}

	for (std::set<std::shared_ptr<UnidadMovible>>::iterator it_unidades = 
	unidades_a_eliminar.begin(); it_unidades != unidades_a_eliminar.end();
	++it_unidades) {
		std::cout << "unidad murio de tipo" << (*it_unidades)->pedir_id_tipo() <<std::endl;
		eliminar_unidad_del_juego(*it_unidades);
	}
}
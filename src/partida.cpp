#include "partida.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include "Edificios/refineria.h"
#include <memory>
#include <iostream>
#include <set>
#include <stdlib.h> 

#define CODIGO_CREACION_OBJETO_RECHAZADA 'r'
#define CODIGO_MUERTE_OBJETO 'd'
#define CODIGO_PERDIO_JUGADOR 'e'
#define CODIGO_CAMBIO_DINERO 'p'
#define CODIGO_CAMBIO_ENERGIA 'w'
#define CODIGO_GANO_JUGADOR 'e'
#define DISTANCIA_MINIMA_EDIFICIO_ALIADO 7000
#define CONSTANTE_REDUCCION_TIEMPO 100

Partida::Partida() {
	contador_ids_objetos = 0;
	Config json("../src/input.json");
	config = std::move(json);
	Mapa map(this->config, contador_ids_objetos);
	mapa = std::move(map);
}

void Partida::asignar_casa_a_jugador(int id_casa, int id_jugador) {
	jugadores.at(id_jugador).asignar_casa(id_casa);
}

int Partida::obtener_limite_mapa_fila(){
	return mapa.pedir_limite_filas();
}

int Partida::obtener_limite_mapa_columna(){
	return mapa.pedir_limite_columnas();
}

void Partida::agregar_jugador(int id_jugador, 
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes) {
	Jugador jugador(config);
	jugadores.emplace(std::pair<int, Jugador>(id_jugador, 
	jugador));
	agregar_edificio(id_jugador, mapa.obtener_centro_construccion(id_jugador),
	 0, colas_mensajes);
	std::cout << mapa.obtener_centro_construccion(id_jugador).first << " x centro " << id_jugador << " e y " << mapa.obtener_centro_construccion(id_jugador).second << std::endl;
}

std::pair<int,int> Partida::buscar_ubicacion(std::pair<int,int> esquina){
	esquina.first+=50;
	esquina.second+=50;
	return esquina;
}
std::pair<int,int> Partida::ubicar_centro_construccion(int id_jugador){
	std::pair<int,int> ubicacion_centro;
	int limite_col = (int)mapa.pedir_limite_columnas();
	int limite_fil = (int)mapa.pedir_limite_filas();

	int rango_col = limite_col/3;
	int rango_fil = limite_fil/3;
	switch (id_jugador){
		case 0:
		{
			ubicacion_centro = buscar_ubicacion(std::pair<int,int> (0,0));
			break;
		}
		case 1:
		{
			ubicacion_centro = buscar_ubicacion(std::pair<int,int> (0,
				limite_col - rango_col));
			break;
		}
		case 2:
		{
			ubicacion_centro = buscar_ubicacion(std::pair<int,int> 
				(limite_fil - rango_fil,0));
			break;
		}
		case 3:
		{
			ubicacion_centro = buscar_ubicacion(std::pair<int,int> 
				(limite_fil - rango_fil, limite_col - rango_col));
			break;
		}
	}
	return ubicacion_centro;
}

bool Partida::esta_dentro(int id_jugador,std::pair<int,int> &posicion_central){
	int cant_propios = 0;
	for (std::map<int, std::shared_ptr<Edificio>>::iterator 
		it=edificios.begin(); it!=edificios.end(); ++it){
		if (it->second->pedir_id_duenio() == id_jugador){
			if(it->second->calcular_distancia_baldosas(posicion_central) <= 
				DISTANCIA_MINIMA_EDIFICIO_ALIADO){
				return true;
			}
			cant_propios++;
		}
	}
	if (cant_propios == 0){
		return true;
	}
    return false;
}

void Partida::agregar_edificio(int id_jugador, std::pair<int, int>
posicion_central, int id_tipo_edificio, 
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes) {
	std::shared_ptr<Edificio> ptr_edificio = fabrica_edificios.
	crear_edificio(id_tipo_edificio, contador_ids_objetos, id_jugador,
	posicion_central,config);

	bool esta_dentro_rango = esta_dentro(id_jugador, posicion_central);
	bool agregado = ptr_edificio->agregar_al_juego(mapa, 
	jugadores.at(id_jugador), contador_ids_objetos, id_tipo_edificio);
	if (agregado && esta_dentro_rango) {
		edificios.emplace(std::pair<int, 
		std::shared_ptr<Edificio>>(contador_ids_objetos, ptr_edificio));
		contador_ids_objetos++;
		ptr_edificio->serializar_mensaje_creacion_objeto(ptr_edificio);
		serializar_mensaje_dinero(jugadores.at(id_jugador).pedir_dinero(),
		id_jugador, colas_mensajes);
		serializar_mensaje_energia(jugadores.at(id_jugador).
		pedir_energia_disponible(), id_jugador, colas_mensajes);
	} else {
		serializar_mensaje_rechazo_creacion(colas_mensajes, id_tipo_edificio,
		id_jugador);
	}
}

void Partida::atacar_objeto(int id_unidad_atacante, 
int id_objeto_atacado) {
	if (edificios.count(id_objeto_atacado) > 0) {
		(unidades_movibles.at(id_unidad_atacante))->iniciar_ataque(mapa, 
		edificios.at(id_objeto_atacado));
	} else if(unidades_movibles.count(id_objeto_atacado) > 0) {
		(unidades_movibles.at(id_unidad_atacante))->iniciar_ataque(mapa, 
		unidades_movibles.at(id_objeto_atacado));
	} else {
		//si el id no es de unidad o edificio significa que es de terreno
		//y que es la cosechadora la que ataca 
		(unidades_movibles.at(id_unidad_atacante))->iniciar_ataque(mapa,
		mapa.obtener_baldosa_con_especia(id_objeto_atacado));
	}
}

void Partida::iniciar_entrenamiento_unidad_movible(int id_tipo_unidad, 
int id_edificio, int id_jugador, 
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes) {
	if (jugadores.at(id_jugador).
	tiene_tipo_de_unidad_entrenando(id_tipo_unidad)) {
		serializar_mensaje_rechazo_creacion(colas_mensajes, id_tipo_unidad,
		id_jugador);
	} else {
		bool se_puede_agregar = ((edificios.at(id_edificio))->
		se_puede_agregar_unidad(jugadores.at(id_jugador), 
		id_tipo_unidad, contador_ids_objetos,config));
		if (!se_puede_agregar) {

			serializar_mensaje_rechazo_creacion(colas_mensajes, id_tipo_unidad,
			id_jugador);
		} else {
			serializar_mensaje_dinero(jugadores.at(id_jugador).pedir_dinero(),
			id_jugador, colas_mensajes);
			contador_ids_objetos++;
		}
	}
}

void Partida::comenzar_movimiento_unidad(
int id_unidad, std::pair<int, int> posicion_destino) {
	unidades_movibles.at(id_unidad)->empezar_a_mover(mapa, 
	posicion_destino);
}

void Partida::actualizar_creacion_unidades(std::shared_ptr<Edificio> 
edificio, int tiempo_transcurrido, int id_tipo_unidad) {
	int energia_jugador = jugadores.at(edificio->pedir_id_duenio()).
	pedir_energia_disponible();
	if (energia_jugador < 0) {
		tiempo_transcurrido -= abs(energia_jugador/CONSTANTE_REDUCCION_TIEMPO);
		if (tiempo_transcurrido < 0) {
			tiempo_transcurrido = 0;
		}
	}
	bool entrenamiento_terminado = edificio->
	avanzar_tiempo_creacion(tiempo_transcurrido, id_tipo_unidad);
	if (entrenamiento_terminado) {
		std::shared_ptr<UnidadMovible> unidad_nueva = edificio->
		agregar_unidad(mapa, id_tipo_unidad);
		unidades_movibles.emplace(std::pair<int, 
		std::shared_ptr<UnidadMovible>> (unidad_nueva->pedir_id(), 
		unidad_nueva));
		jugadores.at(edificio->pedir_id_duenio()).
		sacar_tipo_unidad_entrenandose(unidad_nueva->pedir_id_tipo());
	}
}

void Partida::vender_edificio(int id_edificio,
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes) {
	int id_duenio = edificios.at(id_edificio)->pedir_id_duenio();
	edificios.at(id_edificio)->vender(jugadores.at(id_duenio));
	serializar_mensaje_dinero(jugadores.at(id_duenio).pedir_dinero(),
	id_duenio, colas_mensajes);
}

void Partida::eliminar_edificio_del_juego(std::shared_ptr<Edificio> 
edificio_a_remover, std::map<int, std::shared_ptr<ColaBloqueante>> 
colas_mensajes) {
	edificio_a_remover->poner_fuera_de_juego();
	int id_duenio = edificio_a_remover->pedir_id_duenio();
	jugadores.at(edificio_a_remover->pedir_id_duenio()).
	eliminar_edificio(edificio_a_remover);
	edificios.erase(edificio_a_remover->pedir_id());
	mapa.eliminar_objeto(edificio_a_remover->pedir_id());
	serializar_mensaje_energia(jugadores.at(id_duenio).
	pedir_energia_disponible(), id_duenio, colas_mensajes);
}

void Partida::eliminar_unidad_del_juego(std::shared_ptr<UnidadMovible> 
unidad_a_remover) {
	unidad_a_remover->poner_fuera_de_juego();
	unidades_movibles.erase(unidad_a_remover->pedir_id());
	mapa.eliminar_objeto(unidad_a_remover->pedir_id());
}

void Partida::serializar_mensaje_rechazo_creacion(
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes,
int id_tipo_objeto_rechazado, int id_jugador) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_CREACION_OBJETO_RECHAZADA);
	mensaje.agregar_parametro(id_tipo_objeto_rechazado);
  	colas_mensajes[id_jugador]->push(mensaje);
}

void Partida::guardar_mensaje_en_colas(
std::map<int, std::shared_ptr<ColaBloqueante>> colas,
MensajeProtocolo mensaje) {
	for (std::map<int, std::shared_ptr<ColaBloqueante>>::iterator
	it = colas.begin(); it != colas.end(); ++it) {
		(it->second)->push(mensaje);
	} 
}


void Partida::serializar_mensaje_dinero(int dinero, int id_jugador,
std::map<int, std::shared_ptr<ColaBloqueante>> colas) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_CAMBIO_DINERO);
	mensaje.agregar_parametro(dinero);
	colas.at(id_jugador)->push(mensaje);
}

void Partida::serializar_mensaje_energia(int energia, int id_jugador,
std::map<int, std::shared_ptr<ColaBloqueante>> colas) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_CAMBIO_ENERGIA);
	mensaje.agregar_parametro(energia);
	colas.at(id_jugador)->push(mensaje);
}

void Partida::eliminar_jugador(int id_jugador,
std::map<int, std::shared_ptr<ColaBloqueante>> colas) {
	std::set<std::shared_ptr<Edificio>> edificios_a_eliminar;
	std::set<std::shared_ptr<UnidadMovible>> unidades_a_eliminar;
	agregar_objetos_a_eliminar(edificios_a_eliminar, unidades_a_eliminar,
	id_jugador, colas);
	eliminar_objetos_de_sets(edificios_a_eliminar, unidades_a_eliminar,
	colas);
	jugadores.erase(id_jugador);
}

void Partida::serializar_mensaje_muerte(int id_objeto_a_remover, 
std::map<int, std::shared_ptr<ColaBloqueante>> &colas) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion('d');
	mensaje.agregar_parametro(id_objeto_a_remover);
	guardar_mensaje_en_colas(colas, mensaje);
}

void Partida::agregar_objetos_a_eliminar(std::set<std::shared_ptr<Edificio>> 
&edificios_a_eliminar, std::set<std::shared_ptr<UnidadMovible>> 
&unidades_a_eliminar, int id_duenio_objetos, 
std::map<int, std::shared_ptr<ColaBloqueante>> colas) {
	for (std::map<int, std::shared_ptr<Edificio>>::iterator it_edifs2 = 
	edificios.begin(); it_edifs2 != edificios.end(); ++it_edifs2) {
		if ((it_edifs2->second)->pedir_id_duenio() == 
		id_duenio_objetos) {
			edificios_a_eliminar.insert(it_edifs2->second);
			serializar_mensaje_muerte(it_edifs2->second->pedir_id(),
			colas);
		}
	}

	for (std::map<int, std::shared_ptr<UnidadMovible>>::iterator it_unidades =
	unidades_movibles.begin(); it_unidades != unidades_movibles.end(); 
	++it_unidades) {
		if ((it_unidades->second)->pedir_id_duenio() == 
		id_duenio_objetos) {
			unidades_a_eliminar.insert(it_unidades->second);
			serializar_mensaje_muerte(it_unidades->second->pedir_id(),
			colas);
		}
	}
}

void Partida::eliminar_objetos_de_sets(std::set<std::shared_ptr<Edificio>> 
&edificios_a_eliminar, std::set<std::shared_ptr<UnidadMovible>> 
&unidades_a_eliminar, std::map<int, std::shared_ptr<ColaBloqueante>> colas) {
	for (std::set<std::shared_ptr<Edificio>>::iterator it_edificios = 
	edificios_a_eliminar.begin(); it_edificios != edificios_a_eliminar.end();
	++it_edificios) {
		eliminar_edificio_del_juego(*it_edificios, colas);
	}

	for (std::set<std::shared_ptr<UnidadMovible>>::iterator it_unidades = 
	unidades_a_eliminar.begin(); it_unidades != unidades_a_eliminar.end();
	++it_unidades) {
		// << "Unidad de tipo " << (*it_unidades)->pedir_id_tipo()<< " e id " << (*it_unidades)->pedir_id() << " murio." <<std::endl;
		eliminar_unidad_del_juego(*it_unidades);
	}
}

void Partida::actualizar_modelo(int tiempo_transcurrido, 
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes) {
	//actualizo salida del gusano
	mapa.actualizar_salida_gusano(tiempo_transcurrido, colas_mensajes);
	
	//por cada jugador me fijo si tiene un id de un edificio
	//entrenando. De ser asi actualizo la reacion de la
	//unidad que tenga en entrenamiento
	for (std::map<int, Jugador>::iterator it_jugadores = 
	jugadores.begin(); it_jugadores != jugadores.end(); ++it_jugadores) {
		std::map<int, int> unidades_entrenandose = it_jugadores->second.
		pedir_unidades_entrenandose();
		for (std::map<int, int>::iterator it_entrenamiento = 
		unidades_entrenandose.begin(); it_entrenamiento != 
		unidades_entrenandose.end(); ++it_entrenamiento) {
			//verificacion por si un edificio esta creando una unidad
			//y lo destruyen
			if (edificios.count(it_entrenamiento->second) < 0) {
				(it_jugadores->second).sacar_tipo_unidad_entrenandose(
				it_entrenamiento->first);
				continue;
			}
			actualizar_creacion_unidades(edificios.
			at(it_entrenamiento->second), tiempo_transcurrido, 
			it_entrenamiento->first);
		}
	}

	//por cada edificio actualizo el estado en caso de que haya muerto
	for (std::map<int, std::shared_ptr<Edificio>>::iterator it_edifs = 
	edificios.begin(); it_edifs != edificios.end(); ++it_edifs) {
		
		(it_edifs->second)->actualizar_existencia(
		jugadores.at((it_edifs->second)->pedir_id_duenio()));
	}

	//actualizo cada unidad
	for (std::map<int, std::shared_ptr<UnidadMovible>>::iterator it_unidades = 
	unidades_movibles.begin(); it_unidades != unidades_movibles.end(); 
	++it_unidades) {
		(it_unidades->second)->actualizar_unidad(tiempo_transcurrido, mapa);
	}

	//por cada refineria me fijo si tiene especia encima y si tiene
	// y el jugador tiene espacio se le agrega, convirtiendose en dinero
	std::map<int, Refineria*> refinerias = mapa.pedir_refinerias();
	for (std::map<int, Refineria*>::iterator it_ref = 
	refinerias.begin(); it_ref != refinerias.end(); 
	++it_ref){
		int especia_almacenada_en_ref = it_ref->second->obtener_especia();
		int especia_agregada = jugadores.at(it_ref->second->pedir_id_duenio()).
		agregar_especia(especia_almacenada_en_ref);
		if (especia_agregada > 0) {
			it_ref->second->reducir_especia(especia_agregada);
			jugadores.at(it_ref->second->pedir_id_duenio()).
			aumentar_dinero(especia_agregada);
			serializar_mensaje_dinero(jugadores.at(
			it_ref->second->pedir_id_duenio()).pedir_dinero(),
			it_ref->second->pedir_id_duenio(), colas_mensajes);
		}
	}

	//por cada terreno con especia me fijo si la sigue teniendo
	//si no la tiene, mando mensaje de que no hay mas especia ahi
	std::vector<MensajeProtocolo> terrenos_sin_especia = mapa.
	obtener_mensajes_terrenos_sin_especia();
	for (std::vector<MensajeProtocolo>::iterator it_mensajes = 
	terrenos_sin_especia.begin(); it_mensajes != 
	terrenos_sin_especia.end(); ++it_mensajes) {
		guardar_mensaje_en_colas(colas_mensajes, *it_mensajes);
	}
	

	std::set<std::shared_ptr<Edificio>> edificios_a_eliminar;
	std::set<std::shared_ptr<UnidadMovible>> unidades_a_eliminar;
	std::set<int> jugadores_a_eliminar;
	//por cada edificio me fijo los mensajes que tiene para enviar
	//si hay mensaje de muerte se agrega a edificios a eliminar
	//y en caso de que sea el centro de cosntruccion se agregan
	//todos los objetos del jugador para eliminar
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
				agregar_objetos_a_eliminar(edificios_a_eliminar, 
				unidades_a_eliminar, id_jugador_afuera, colas_mensajes);
				jugadores_a_eliminar.insert(id_jugador_afuera);
			}
			guardar_mensaje_en_colas(colas_mensajes, *it_mensajes);
		}
		(it_edifs->second)->limpiar_lista_mensajes();
	}

	//por cada unidad la actualizo y si tiene menasje de muerte
	//las pongo para eliminar
	for (std::map<int, std::shared_ptr<UnidadMovible>>::iterator it_unidades = 
	unidades_movibles.begin(); it_unidades != unidades_movibles.end(); 
	++it_unidades) {
		std::vector<MensajeProtocolo> mensajes = (it_unidades->second)->
		obtener_mensajes_para_mandar();
		for (std::vector<MensajeProtocolo>::iterator it_mensajes = 
		mensajes.begin(); it_mensajes != mensajes.end(); ++it_mensajes) {
			std::vector<int> v = (*it_mensajes).pedir_parametros();
			if ((*it_mensajes).pedir_accion() == CODIGO_MUERTE_OBJETO) {
				unidades_a_eliminar.insert(it_unidades->second);
			}
			guardar_mensaje_en_colas(colas_mensajes, *it_mensajes);
		}
		(it_unidades->second)->limpiar_lista_mensajes();
	}

	eliminar_objetos_de_sets(edificios_a_eliminar, unidades_a_eliminar,
	colas_mensajes);

	for (std::set<int>::iterator it_jugadores = jugadores_a_eliminar.begin(); 
	it_jugadores!= jugadores_a_eliminar.end(); ++it_jugadores) {
		jugadores.erase(*it_jugadores);
	}

	//significa que queda un jugador y gano
	if (jugadores.size() == 1) {
		MensajeProtocolo mensaje;
		mensaje.asignar_accion(CODIGO_GANO_JUGADOR);
		mensaje.agregar_parametro(jugadores.begin()->first);
		guardar_mensaje_en_colas(colas_mensajes, mensaje);
	}
}

void Partida::terreno_inicial(std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes){
	mapa.terreno_inicial(colas_mensajes);
}
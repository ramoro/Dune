#include "partida.h"
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include "Edificios/refineria.h"
#include <memory>
#include <iostream>
#include <set>

#define CODIGO_CREACION_OBJETO_RECHAZADA 'r'
#define CODIGO_MUERTE_OBJETO 'd'
#define CODIGO_PERDIO_JUGADOR 'e'
#define CODIGO_CAMBIO_DINERO 'p'
#define CODIGO_CAMBIO_ENERGIA 'o'
#define JUGADOR_NO_ENTRENANDO -1
#define DISTANCIA_MINIMA_EDIFICIO_ALIADO 7000

Partida::Partida() {
	contador_ids_jugadores = 0;
	contador_ids_objetos = 0;
	Config json("../src/input.json");
	config = std::move(json);
	Mapa map(this->config, contador_ids_objetos);
	mapa = std::move(map);
	std::cout << "contador_ids_objetos " << contador_ids_objetos << std::endl;
}

int Partida::pedir_id_nuevo_cliente() {
	return contador_ids_jugadores;
}

int Partida::obtener_limite_mapa_fila(){
	return mapa.pedir_limite_filas();
}

int Partida::obtener_limite_mapa_columna(){
	return mapa.pedir_limite_columnas();
}

void Partida::agregar_jugador(std::string casa_jugador, 
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes) {
	Jugador jugador(casa_jugador,config);
	jugadores.emplace(std::pair<int, Jugador>(contador_ids_jugadores, 
	jugador));
	std::pair<int,int> ubicacion_centro = ubicar_centro_construccion();
	std::cout << "centro constuccion en " << ubicacion_centro.first << " " << ubicacion_centro.second << std::endl;
	agregar_edificio(contador_ids_jugadores, ubicacion_centro, 0, colas_mensajes);
#ifdef DEBUG 
	//agregar_edificio(contador_ids_jugadores, std::pair<int,int>(7,7), 6, cola_mensajes);

#endif
	contador_ids_jugadores++;
}

std::pair<int,int> Partida::buscar_ubicacion(std::pair<int,int> esquina){
	esquina.first+=50;
	esquina.second+=50;
	return esquina;
}
std::pair<int,int> Partida::ubicar_centro_construccion(){
	std::pair<int,int> ubicacion_centro;
	int limite_col = (int)mapa.pedir_limite_columnas();
	int limite_fil = (int)mapa.pedir_limite_filas();

#ifdef NACHO 
	std::cout << "limite_col " << limite_col << " limite_fil " << limite_fil << std::endl;

	std::cout << "limite_col_bald " << mapa.pedir_limite_columnas_baldosa() << " limite_fil_bald " << mapa.pedir_limite_filas_baldosa() << std::endl;
#endif

	int rango_col = limite_col/3;
	int rango_fil = limite_fil/3;
	switch (contador_ids_jugadores){
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
		std::cout << "No se pudo construir edificio de tipo " << id_tipo_edificio << std::endl;
		serializar_mensaje_rechazo_creacion(colas_mensajes, id_tipo_edificio);
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
	int id_edificio_entrenando = jugadores.at(id_jugador).
	pedir_id_edificio_entrenando();
	if (id_edificio_entrenando != JUGADOR_NO_ENTRENANDO) {
		std::cout << "ERROR JUGADRO YA ENTRENANDO" << std::endl;
		serializar_mensaje_rechazo_creacion(colas_mensajes, id_tipo_unidad);
	} else {
		bool se_puede_agregar = ((edificios.at(id_edificio))->
		se_puede_agregar_unidad(jugadores.at(id_jugador), 
		id_tipo_unidad, contador_ids_objetos,config));
		if (!se_puede_agregar) {
			std::cout << "ERRO no se puede agregar" << std::endl;
			serializar_mensaje_rechazo_creacion(colas_mensajes, id_tipo_unidad);
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
edificio, int tiempo_transcurrido) {
	int energia_jugador = jugadores.at(edificio->pedir_id_duenio()).
	pedir_energia_disponible();
	if (energia_jugador < 0) {
		//diminucion del tiempo que paso segun la energia encontra que se tiene
	}
	bool entrenamiento_terminado = edificio->
	avanzar_tiempo_creacion(tiempo_transcurrido);
	if (entrenamiento_terminado) {
		std::cout << "se creo unidad" << std::endl;
		std::shared_ptr<UnidadMovible> unidad_nueva = edificio->
		agregar_unidad(mapa); //VERIFICAR ESTE AGREGADO CON GDB LUEGO
		unidades_movibles.emplace(std::pair<int, 
		std::shared_ptr<UnidadMovible>> (unidad_nueva->pedir_id(), 
		unidad_nueva));
		jugadores.at(edificio->pedir_id_duenio()).setear_no_entrenando();
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

void Partida::serializar_mensaje_rechazo_creacion(
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes,
int id_tipo_objeto_rechazado) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_CREACION_OBJETO_RECHAZADA);
	mensaje.agregar_parametro(id_tipo_objeto_rechazado);
  	guardar_mensaje_en_colas(colas_mensajes, mensaje);
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

void Partida::actualizar_modelo(int tiempo_transcurrido, 
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes) {
	//std::cout << "ACTUALIZA MODELO con tiempo " << tiempo_transcurrido << std::endl; 
	//actualizo salida del gusano

	mapa.actualizar_salida_gusano(tiempo_transcurrido, colas_mensajes);

	//por cada jugador me fijo si tiene un id de un edificio
	//entrenando. De ser asi actualizo la reacion de la
	//unidad que tenga en entrenamiento
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
		std::cout << "Pasa por verificacion terrenos" << std::endl;
		std::cout << "Mensaje de accion " << (*it_mensajes).pedir_accion() << " encolandose" << std::endl;
		guardar_mensaje_en_colas(colas_mensajes, *it_mensajes);
	}
	

	std::set<std::shared_ptr<Edificio>> edificios_a_eliminar;
	std::set<std::shared_ptr<UnidadMovible>> unidades_a_eliminar;
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
			std::cout << "Mensaje de accion " << (*it_mensajes).pedir_accion() << " encolandose" << std::endl;
			if ((*it_mensajes).pedir_accion() == CODIGO_MUERTE_OBJETO) {
				edificios_a_eliminar.insert(it_edifs->second);
			} else if ((*it_mensajes).pedir_accion() == CODIGO_PERDIO_JUGADOR) {
				int id_jugador_afuera = (it_edifs->second)->pedir_id_duenio();
				for (std::map<int, std::shared_ptr<Edificio>>::iterator it_edifs2 = 
				edificios.begin(); it_edifs2 != edificios.end(); ++it_edifs2) {
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
			std::cout << "Mensaje de accion " << (*it_mensajes).pedir_accion() << " encolandose de "   << v[0] << " a " << v[1] << std::endl;
			if ((*it_mensajes).pedir_accion() == CODIGO_MUERTE_OBJETO) {
				unidades_a_eliminar.insert(it_unidades->second);
			}
			guardar_mensaje_en_colas(colas_mensajes, *it_mensajes);
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
		std::cout << "Unidad de tipo " << (*it_unidades)->pedir_id_tipo()<< " e id " << (*it_unidades)->pedir_id() << " murio." <<std::endl;
		eliminar_unidad_del_juego(*it_unidades);
	}
}

void Partida::terreno_inicial(std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes){
	mapa.terreno_inicial(colas_mensajes);
}
#include "unidad_movible.h"
#include "../Estados/estado.h"
#include "../Estados/movimiento_para_atacar.h"
#include "../Estados/ataque.h"
#include <stdlib.h> 
#include <iostream>

#define CODIGO_MOVIMIENTO 'm'
#define CODIGO_ATAQUE 'a'
#define PASAJE_A_MILISEGS 1000
#define SEGUNDO_EN_MILIS 1000
#define CODIGO_DUNA 31

UnidadMovible::UnidadMovible(int rango, int velocidad, 
double tiempo_creacion, int costo_dinero, int vida, int id, int id_duenio,
int base, int altura, std::pair<int, int> centro) :
	ObjetoDune(vida, costo_dinero, id, id_duenio, base, altura, centro),
	rango(rango), velocidad(velocidad), 
	tiempo_creacion(tiempo_creacion * PASAJE_A_MILISEGS){
		tiempo_acumulado = 0;
	}

void UnidadMovible::resetear_tiempo_acumulado(){ 
	tiempo_acumulado = 0;
}

void UnidadMovible::acumular_tiempo(int tiempo_transcurrido){
	tiempo_acumulado+=tiempo_transcurrido;
}

int UnidadMovible::obtener_tiempo_acumulado(){
	return tiempo_acumulado;
}


int UnidadMovible::pedir_danio(std::string objetivo, int tiempo_transcurrido) {
	int danio_mayor = 0;
	int indice = 0;
	int indice_arma_mayor_danio;
	int danio_total = 0;
	for (std::vector<Arma>::iterator it = armas.begin();
	it != armas.end(); ++it) {
		if ((*it).obtener_danio(objetivo) > danio_mayor) {
			danio_mayor = (*it).obtener_danio(objetivo);
			indice_arma_mayor_danio = indice;
		}
		indice++;
	}
	if (armas[indice_arma_mayor_danio].puede_atacar(tiempo_transcurrido)) {
		int cantidad_disparos = armas[indice_arma_mayor_danio].
		obtener_frecuencia_disparo();
		for (int i = 0; i < cantidad_disparos; i++) {
			danio_total += danio_mayor;
		}
		std::cout << "cantidad disparos" << cantidad_disparos << std::endl;
	}
	return danio_total;
}

std::vector<ObjetoDune*> UnidadMovible::atacar_objetivo(Mapa &mapa,
int id_objetivo) {
	std::vector<ObjetoDune*> aux;
	return aux;
}

int UnidadMovible::daniar(std::shared_ptr<UnidadMovible> unidad_atacante) {
	return 0;
}

void UnidadMovible::matar() {}

std::vector<ObjetoDune*> ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> aux;
	return aux;
}

void UnidadMovible::poner_estado_muerta() {
	estado = estado->cambiar_a_muerte();
	fuera_de_juego = true;
}

std::vector<int> UnidadMovible::obtener_edificios_necesarios() {
	return ids_tipos_edificios_necesarios;
}

int UnidadMovible::obtener_rango_ataque() {
	return rango;
}

int UnidadMovible::obtener_velocidad(int tipo_terreno) {
	if (tipo_terreno == CODIGO_DUNA){
		//std::cout << "Mover UNidad sobre duna a velocidad " << velocidad/2 << std::endl;
		return velocidad/2;
	}
	return velocidad;
}

bool UnidadMovible::se_puede_agregar(Jugador 
&jugador) {
	return (jugador.agregada_unidad(this));
}

void UnidadMovible::agregar(Mapa &mapa) {
	std::cout << "unidad en x " << (this->centro).first << " y " << (this->centro).second << std::endl;
	mapa.agregar_objeto(this, this->id,
	this->centro,false);
	estado = estado->cambiar_a_inactividad();
}

int UnidadMovible::tiempo_creacion_faltante(int milisegs) {
	tiempo_creacion -= milisegs;
	return tiempo_creacion;
}

void UnidadMovible::empezar_a_mover(Mapa &mapa, std::pair<int, int> 
pos_destino) {
	camino = mapa.obtener_camino(this->centro, pos_destino, this);
	estado = estado->cambiar_a_movimiento();
}

void UnidadMovible::actualizar_unidad(int tiempo_transcurrido, 
Mapa &mapa) {
	//por si sale algo mal y no se vacio del todo el camino
	//cuando la unidad llego
	//if (camino.empty()) return;
//	std::cout << "centro: " << centro.first << centro.second << " de la unidad " << id << std::endl;
	if (estado) {
		std::shared_ptr<Estado> nuevo_estado = estado->actualizar(this, mapa,
		tiempo_transcurrido);
//		std::cout << "estado actual de "<< id << " estado: " << estado->pedir_nombre() << std::endl;
		//si no es null le asigno el nuevo estado
		if (nuevo_estado) {
			std::cout << "nuevo estado " << " estado: " << nuevo_estado->pedir_nombre() << std::endl;
			estado = nuevo_estado;
		}
	}
}

std::list<std::pair<int, int>> UnidadMovible::pedir_camino() {
	return camino;
}

void UnidadMovible::avanzar_camino() {
	if (!camino.empty()){
		camino.pop_front();
	}
}

void UnidadMovible::asignar_nuevo_camino(std::list<std::pair<int, int>>
nuevo_camino) {
	camino = nuevo_camino;
}

void UnidadMovible::iniciar_ataque(Mapa &mapa, 
std::shared_ptr<ObjetoDune> objetivo) {
	std::pair<int, int> cercania = mapa.pedir_cercania(this->id, 
	objetivo->pedir_id());
	if (cercania.first > this->rango || cercania.second > 
	this->rango) {
		estado = estado->cambiar_a_movimiento_para_atacar(objetivo);
		asignar_nuevo_camino(mapa.obtener_camino(this->centro, 
		objetivo->obtener_centro(),this));
	} else {
		estado = estado->cambiar_a_ataque(objetivo);
		serializar_mensaje_ataque(objetivo->pedir_id());
	}
}

void UnidadMovible::serializar_mensaje_movimiento() {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_MOVIMIENTO);
	mensaje.agregar_parametro(this->id);
	mensaje.agregar_parametro(this->centro.first);
	mensaje.agregar_parametro(this->centro.second);
	mensajes.push_back(std::move(mensaje));
}

void UnidadMovible::serializar_mensaje_termino_ataque() {
	serializar_mensaje_movimiento();
}

void UnidadMovible::serializar_mensaje_ataque(int id_unidad_atacada) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_ATAQUE);
	mensaje.agregar_parametro(this->id);
	mensaje.agregar_parametro(id_unidad_atacada);
	mensajes.push_back(std::move(mensaje));
}

void UnidadMovible::serializar_mensaje_muerte() {
	ObjetoDune::mensaje_muerte();
}

void UnidadMovible::limpiar_camino() {
	camino.clear();
}

std::vector<std::string> UnidadMovible::obtener_casa(){
	return casa;
}

void UnidadMovible::afectar_terreno(std::shared_ptr<ObjetoDune> terreno,
Mapa &mapa, int tiempo_transcurrido) {}

int UnidadMovible::depositar_especia_en_segundo() {
	std::cout << "se llamo a depositar_especia_en_segundo de un mov" 
	<< std::endl;
	return 0;
}

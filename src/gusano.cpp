#include "gusano.h"
#include <iostream>
	
#define CODIGO_SALIDA_GUSANO 'g'
#define ID_GUSANO 50 //esto es por el protocolo
#define PASAJE_A_MILISEGS 1000

/*bool es_arena = verificar_terreno_alrededor(posicion_centro,
		root["Gusano"].get("dimension_alto",0).asInt(), 
		root["Gusano"].get("dimension_ancho",0).asInt(), "arena");
		if (es_arena) {
			objetivos = buscar_unidades_alrededor(posicion_centro, 
			root["Gusano"].get("dimension_alto",0).asInt(),
			root["Gusano"].get("dimension_ancho",0).asInt(), false, 
			false, -1);
			if (!objetivos.empty()) {
				espacio_valido = true;
			}
		}*/

//DATOS DEL GUSANO VIENEN DEL CONFIG
Gusano::Gusano(Config &config) {
	dimension_ancho = config["Gusano"].get("dimension_ancho", 0).asInt()*
	config["cant_pixeles_por_baldosa"].asInt();
	dimension_alto = config["Gusano"].get("dimension_alto", 0).asInt()*
	config["cant_pixeles_por_baldosa"].asInt();
	tiempo_salida =  config["Gusano"].get("tiempo_salida_segs", 0).asInt() 
	* PASAJE_A_MILISEGS;
	contador_salida = tiempo_salida;
	std::pair<int ,int> centro(0, 0);
	centro_salida = centro;
}

Gusano::Gusano() {}

int Gusano::obtener_dimesion_alto() {
	return dimension_alto;
}

int Gusano::obtener_dimesion_ancho(){ 
	return dimension_ancho;
}

bool Gusano::actualizar_salida(int tiempo_transcurrido) {
	int tiempo_faltante = contador_salida - tiempo_transcurrido;
	if (tiempo_faltante <= 0) {
		contador_salida = tiempo_salida + tiempo_faltante;
		return true;
	}
	contador_salida -= tiempo_transcurrido;
	return false;
}

MensajeProtocolo Gusano::serializar_mensaje_salida() {
	mensaje.asignar_accion(CODIGO_SALIDA_GUSANO);
	mensaje.agregar_parametro(ID_GUSANO);
	mensaje.agregar_parametro(dimension_ancho);
	mensaje.agregar_parametro(dimension_alto);
	mensaje.agregar_parametro(centro_salida.first);
	mensaje.agregar_parametro(centro_salida.second);
	return mensaje;
}

void Gusano::asignar_centro(std::pair<int, int> nuevo_centro) {
	centro_salida = nuevo_centro;
}

void Gusano::limpiar_mensaje() {
	mensaje.limpiar_mensaje();
}
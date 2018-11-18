#include "gusano.h"
	
#define CODIGO_SALIDA_GUSANO 'g'
#define ID_GUSANO 50 //esto es por el protocolo

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
Gusano::Gusano() {
	dimension_alto = 1;
	dimension_ancho = 1;
	tiempo_salida = 240;
	contador_salida = 240;
}

int Gusano::obtener_dimesion_alto() {
	return dimension_alto;
}

int Gusano::obtener_dimesion_ancho(){ 
	return dimension_ancho;
}

bool Gusano::actualizar_salida(double tiempo_transcurrido) {
	contador_salida -= tiempo_transcurrido;
	if (contador_salida <= 0) {
		contador_salida = tiempo_salida;
		return true;
	}
	return false;
}

void Gusano::serializar_mensaje_salida() {
	mensaje.asignar_accion(CODIGO_SALIDA_GUSANO);
	mensaje.agregar_parametro(ID_GUSANO);
	mensaje.agregar_parametro(dimension_ancho);
	mensaje.agregar_parametro(dimension_alto);
	mensaje.agregar_parametro(centro_salida.first);
	mensaje.agregar_parametro(centro_salida.second);
}

void Gusano::asignar_centro(std::pair<int, int> nuevo_centro) {
	centro_salida = nuevo_centro;
}
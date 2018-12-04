#include "desviador.h"
#include "../Armas/lanza_misiles.h"

#define ID_DESVIADOR 18 //para usarlo en el protocolo
#define CODIGO_CAMBIO_EQUIPO 'k'

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Desviador::Desviador(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Vehiculo(config["Desviador"].get("rango", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Desviador"].get("velocidad", 0).asInt(),
	 config["Desviador"].get("tiempo_entrenamiento", 0).asFloat(),
	 config["Desviador"].get("costo", 0).asInt(), 
	 config["Desviador"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Desviador"].get("dimension_ancho", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Desviador"].get("dimension_alto", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(), centro) {
		id_tipo = ID_DESVIADOR;
		LanzaMisiles lanza_misiles(config);
		armas.push_back(LanzaMisiles(lanza_misiles));
		for (unsigned int i = 0; i < 
		config["Desviador"]["casas"].size(); i++) {
			casa.push_back(config["Desviador"]["casas"][i].asInt());
		}
		for (unsigned int i = 0; i < 
		config["Desviador"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Desviador"]["edificios_necesarios"][i].asInt());
		}
	}

bool Desviador::puede_atacar_aliado(){
	return true;
}

std::vector<ObjetoDune*> Desviador::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> objetos_afectados;		
	objetos_afectados.push_back(mapa.obtener_objeto(id_objetivo));
	objetos_afectados[0]->asignar_duenio(this->id_duenio);
	serializar_mensaje_cambio_equipo(objetos_afectados[0]->pedir_id(),
	objetos_afectados[0]->pedir_id_tipo());
	return objetos_afectados;
}

void Desviador::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> Desviador::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}

void Desviador::serializar_mensaje_cambio_equipo(int id_objetivo,
int id_tipo_objetivo) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_CAMBIO_EQUIPO);
	mensaje.agregar_parametro(id_objetivo);
	mensaje.agregar_parametro(id_tipo_objetivo);
	mensaje.agregar_parametro(this->id_duenio);
	mensajes.push_back(mensaje);
}

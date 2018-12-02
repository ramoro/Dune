#include "cosechadora.h"
#include "../Estados/movimiento_para_depositar.h"
#include "../mapa.h"

#define ID_COSECHADORA 20 //para usarlo en el protocolo
#define SEGUNDO_EN_MILIS 1000

Cosechadora::Cosechadora(int id, int id_duenio, std::pair<int, int> centro,
Config &config) : 
	Vehiculo(config["Cosechadora"].get("rango", 0).asInt(),
	 config["Cosechadora"].get("velocidad", 0).asInt(),
	 config["Cosechadora"].get("tiempo_entrenamiento", 0).asFloat(),
	 config["Cosechadora"].get("costo", 0).asInt(), 
	 config["Cosechadora"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Cosechadora"].get("dimension_ancho", 0).asInt(),
	 config["Cosechadora"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_COSECHADORA;
		contador_segundo = 0;
		especia_encima = 0;
		limite_especia = config["Cosechadora"].get("limite_especia", 0).
		asInt();
		extraccion_especia_por_segundo = config["Cosechadora"].
		get("extraccion_especia_por_segundo", 50).asInt();
		deposito_especia_por_segundo = config["Cosechadora"].
		get("deposito_especia_por_segundo", 50).asInt();
		estado = NULL;

		for (unsigned int i = 0; i < 
		config["Cosechadora"]["casas"].size(); i++) {
			casa.push_back(config["Cosechadora"]["casas"][i].asString());
		}	
		for (unsigned int i = 0; i < 
		config["Cosechadora"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Cosechadora"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> Cosechadora::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> aux;
	return aux;
}

void Cosechadora::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> Cosechadora::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}

void Cosechadora::afectar_terreno(std::shared_ptr<ObjetoDune> terreno,
Mapa &mapa, int tiempo_transcurrido) {
	//esto es por si esta llena la cosechadora y le dicen de ir
	//a sacar mas especia
	if (terreno->obtener_cantidad_especia() == 0 || especia_encima == limite_especia) {
		buscar_depositar_especia(mapa, terreno);
		return;
	}
	contador_segundo += tiempo_transcurrido;
	if (contador_segundo >= SEGUNDO_EN_MILIS) {
		contador_segundo -= SEGUNDO_EN_MILIS;
		especia_encima += extraccion_especia_por_segundo;
		int especia_sobrante = terreno->remover_especia(this);
		if (especia_sobrante <= 0) {
			especia_encima += especia_sobrante; //es por las dudas de si el
												//rsltdo es negativo. No puedo
												//sumar mas de lo que tenia
												//el terreno
			terreno->matar();
		}

	}

	//tiro la especia que sobra
	if (especia_encima >= limite_especia) {
		int resto = especia_encima - limite_especia;
		especia_encima -= resto;
		buscar_depositar_especia(mapa, terreno);
	}
}

int Cosechadora::obtener_extraccion_especia() {
	return extraccion_especia_por_segundo;
}

void Cosechadora::buscar_depositar_especia(Mapa &mapa, 
std::shared_ptr<ObjetoDune> terreno) {
	Refineria* refineria = mapa.obtener_refineria_mas_cercana(this);
	if (!refineria) {
//		std::cout << "Cosechadora::buscar_depositar_especia no hay refinerias" <<std::endl;
		estado = NULL;
	} else {
		estado = estado->cambiar_a_movimiento_para_depositar(refineria, 
		terreno);
	}
//	std::cout << "Cosechadora::buscar_depositar_especia" <<std::endl;
}

int Cosechadora::depositar_especia_en_segundo() {
//	std::cout << "Cosechadora::depositar_especia_en_segundo " << especia_encima << std::endl;
	if (especia_encima < extraccion_especia_por_segundo) {
		int especia_devuelta = especia_encima;
		especia_encima = 0;
		return especia_devuelta;
	} else {
		especia_encima -= extraccion_especia_por_segundo;
		return extraccion_especia_por_segundo;
	}
}
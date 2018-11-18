#include "devastador.h"
#include "../Armas/canion_plasma.h"
#include "../Armas/explosion.h"

#define ID_DEVASTADOR 19 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Devastador::Devastador(int id, int id_duenio, std::pair<int, int> centro,
 Root &root) : 
	Vehiculo(root["Devastador"].get("rango", 0).asInt(),
	 root["Devastador"].get("velocidad", 0).asInt(),
	 root["Devastador"].get("tiempo_entrenamiento", 0).asFloat(),
	 root["Devastador"].get("costo", 0).asInt(), 
	 root["Devastador"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 root["Devastador"].get("dimension_ancho", 0).asInt(),
	 root["Devastador"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_DEVASTADOR;
		danio_explosion = root["Devastador"].get("danio_explosion", 0).asInt();
		CanionPlasma canion_plasma(root);
		armas.push_back(CanionPlasma(canion_plasma));
		config_explosion.push_back(
			root["Explosion"].get("danio", 0).asInt());
		config_explosion.push_back(
			root["Explosion"].get("frecuencia_disparo", 0).asInt());
		config_explosion.push_back(
			root["Explosion"].get("bonificacion_danio_edificios", 0).asInt());
		config_explosion.push_back(
			root["Explosion"].get("bonificacion_danio_vehiculo", 0).asInt());
		config_explosion.push_back(
			root["Explosion"].get("bonificacion_danio_infanteria", 0).asInt());
		rango_ataque_fila = 10;
		rango_ataque_columna = 10;
		for (unsigned int i = 0;
		 i < root["Devastador"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
				root["Devastador"]["edificios_necesarios"][i].asInt());
		}
	}

std::vector<ObjetoDune*> Devastador::atacar_objetivo(Mapa &mapa, 
int id_objetivo) {
	std::vector<ObjetoDune*> objetos_afectados;		
	objetos_afectados.push_back(mapa.obtener_objeto(id_objetivo));
	return objetos_afectados;
}

void Devastador::matar() { 
	UnidadMovible::poner_estado_muerta();
	armas.clear();
	Explosion explosion(config_explosion);
	armas.push_back(Explosion(explosion));
}

std::vector<ObjetoDune*> Devastador::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objetos_afectados = mapa.
	buscar_unidades_alrededor(this->centro, this->altura, 
	this->base, false, false, -1, false);
	return objetos_afectados;
}

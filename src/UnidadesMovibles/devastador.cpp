#include "devastador.h"
#include "../Armas/canion_plasma.h"
#include "../Armas/explosion.h"

#define ID_DEVASTADOR 19 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Devastador::Devastador(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Vehiculo(config["Devastador"].get("rango", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Devastador"].get("velocidad", 0).asInt(),
	 config["Devastador"].get("tiempo_entrenamiento", 0).asFloat(),
	 config["Devastador"].get("costo", 0).asInt(), 
	 config["Devastador"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Devastador"].get("dimension_ancho", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Devastador"].get("dimension_alto", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(), centro) {
		id_tipo = ID_DEVASTADOR;
		danio_explosion = config["Devastador"].get("danio_explosion", 0).asInt();
		CanionPlasma canion_plasma(config);
		armas.push_back(CanionPlasma(canion_plasma));
		config_explosion.push_back(
		config["Explosion"].get("danio", 70).asInt());
		config_explosion.push_back(
		config["Explosion"].get("frecuencia_disparo", 1).asInt());
		config_explosion.push_back(
		config["Explosion"].get("bonificacion_danio_edificios", 1).asInt());
		config_explosion.push_back(
		config["Explosion"].get("bonificacion_danio_vehiculo", 1).asInt());
		config_explosion.push_back(
		config["Explosion"].get("bonificacion_danio_infanteria", 1).asInt());
		config_explosion.push_back(
		config["Explosion"].get("dimension_alto", 100).asInt()
	 *config["cant_pixeles_por_baldosa"].asInt());
		config_explosion.push_back(
		config["Explosion"].get("dimension_ancho", 100).asInt()
	 *config["cant_pixeles_por_baldosa"].asInt());
		
		for (unsigned int i = 0; i < 
		config["Devastador"]["casas"].size(); i++) {
			casa.push_back(config["Devastador"]["casas"][i].asInt());
		}	
		for (unsigned int i = 0;
		 i < config["Devastador"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
				config["Devastador"]["edificios_necesarios"][i].asInt());
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
	buscar_unidades_devastador(this);
	 std::cout << "objetos_afectados contains:";
  	for (std::vector<ObjetoDune*>::iterator it = objetos_afectados.begin() ; it != objetos_afectados.end(); ++it)
    	std::cout << ' ' << (*it)->pedir_id();
  	std::cout << '\n';
	return objetos_afectados;
}

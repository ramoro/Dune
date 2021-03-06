#include "tanque_sonico.h"
#include "../Armas/onda_sonido.h"

#define ID_TANQUE_SONICO 17 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
TanqueSonico::TanqueSonico(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Vehiculo(config["Tanque sonico"].get("rango", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Tanque sonico"].get("velocidad", 0).asInt(),
	 config["Tanque sonico"].get("tiempo_entrenamiento", 0).asFloat(),
	 config["Tanque sonico"].get("costo", 0).asInt(), 
	 config["Tanque sonico"].get("puntos_vida", 0).asInt(), id, id_duenio, 
	 config["Tanque sonico"].get("dimension_ancho", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	 config["Tanque sonico"].get("dimension_alto", 0).asFloat()
	 *config["cant_pixeles_por_baldosa"].asInt(), centro) {
		id_tipo = ID_TANQUE_SONICO;
		OndaSonido arma_ondas_sonidos(config);
		armas.push_back(OndaSonido(arma_ondas_sonidos));
		//expansion_altura_arma_sonica = 70;
		//expansion_base_arma_sonica = 50;
		for (unsigned int i = 0; i < 
		config["Tanque sonico"]["casas"].size(); i++) {
			casa.push_back(config["Tanque sonico"]["casas"][i].asInt());
		}		
		for (unsigned int i = 0; i < 
		config["Tanque sonico"]["edificios_necesarios"].size(); i++) {
			ids_tipos_edificios_necesarios.push_back(
			config["Tanque sonico"]["edificios_necesarios"][i].asInt());
		}
	}
	

std::vector<ObjetoDune*> TanqueSonico::atacar_objetivo(Mapa &mapa,
int id_objetivo) {
	std::vector<ObjetoDune*> afectados = mapa.buscar_unidades_devastador(this);
	for (std::vector<ObjetoDune*>::iterator it = 
	afectados.begin(); it != afectados.end(); ++it) {
		std::cout << "TanqueSonico::atacar_objetivo afectados " << (*it)->pedir_id_tipo() << std::endl;
	}
	return afectados;
}

void TanqueSonico::matar() { 
	UnidadMovible::poner_estado_muerta();
}

std::vector<ObjetoDune*> TanqueSonico::ataque_al_morir(Mapa &mapa) {
	std::vector<ObjetoDune*> objs;
	return objs;
}

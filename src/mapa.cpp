#include "mapa.h"
#include "Terrenos/no_especia.h"
#include <stdlib.h> 

#define DIMENSION_EXPANSION_BASE 3 //significa que lo minimo que se expande
//la explosion del tanque o el gusano es en un cuadrado de 3x3
#define DIREC_EXPANSION_BASE -1 //define el numero base que se le resta
//a la posicion central desde donde se genera la expansion ya sea del
//gusano o la explosion del tanque
	
//ESTO VIENE EN EL CONFIG
#define ANCHO_COMIDA_GUSANO 100
#define ALTO_COMIDA_GUSANO 100

#define RANGO_EXPASION 0 //ESTA HARDCODEADO. ESTO SE DEBERIA
//CARGAR POR CONFIG. TANTO EXPASION DE GUSANO COMO LA EXPOSION DEL TANQUE

//INICIALIAZDOR DE MAPA HARDCODEADO
Mapa::Mapa() {
	for (int i = 0; i < 1000; i++) {
		std::vector<Coordenada> fila;
		for (int j = 0; j < 1000; j++) {
				NoEspecia roca("roca");
				Coordenada coord(0, roca);
				fila.push_back(coord);
		}
		coordenadas.push_back(fila);
	}
}
bool Mapa::verificar_terreno_alrededores(std::pair<int, int> centro, 
int altura, int base, std::string terreno) {
	bool terreno_adecuado = true;
	std::vector<std::pair<int, int>> direcs_verificacion = {{0, base/2},
	{0, -(base/2)}, {altura/2,0}, {-(altura/2), 0}, {altura/2, -(base/2)},
	{-(altura/2), base/2}, {-(altura/2), -(base/2)}, {altura/2, base/2}};

	for (std::vector<std::pair<int, int>>::iterator it = 
	direcs_verificacion.begin(); it != direcs_verificacion.end(); ++it) {
		if ((centro.first + ((*it).first)) > (int)(coordenadas.size() - 1) || 
  		(centro.first + ((*it).first)) < 0 || (centro.second + ((*it).second))
  		> (int)(coordenadas[coordenadas.size() - 1]).size() || 
  		(centro.second + ((*it).second)) < 0) {
			terreno_adecuado = false;
			break;
  		}

  		if (coordenadas[centro.first + (*it).first]
  		[centro.second + (*it).second].obtener_terreno() != terreno) {
  			terreno_adecuado = false;
  			break;
  		}
	}
	return terreno_adecuado;
}

std::vector<std::pair<int, int>> Mapa::buscar_objetos_en_alrededores(
std::pair<int, int> centro_objeto1, int base_objeto1, int altura_objeto1) {
	std::vector<std::pair<int, int>> objetivos;
	for (std::map<int, ObjetoDune>::iterator it = mapa_ids_objetos.begin();
	it != mapa_ids_objetos.end(); ++it) {
		std::pair<int, int> centro_objeto2 = (it->second).obtener_centro();
		int base_objeto2 = (it->second).obtener_base();
		int altura_objeto2 = (it->second).obtener_altura();
		//verifico que existencia de una unidad o edificio en las
		//esquinas superiores asi como en el medio
		if ((centro_objeto2.first + (altura_objeto2 / 2)) > 
		(centro_objeto1.first - (altura_objeto1 / 2))) {
			if ((centro_objeto2.second - (base_objeto2 / 2)) <
			(centro_objeto1.second + (base_objeto1 / 2)) || 
			(centro_objeto2.second + (base_objeto2 / 2)) > 
			(centro_objeto1.second - (base_objeto1 / 2))) {
				std::pair<int, int> objetivo((it->second).pedir_id(), 
				(it->second).pedir_id_duenio());
				objetivos.push_back(objetivo);
				continue;
			}
		//verifico existencia parte de una unidad o edificio en las esquinas
		//inferiores		
		} else if ((centro_objeto2.first - (altura_objeto2 / 2) < 
		(centro_objeto1.first + (altura_objeto1 / 2)))) {
			if ((centro_objeto2.second - (base_objeto2 / 2)) <
			(centro_objeto1.second + (base_objeto1 / 2)) || 
			(centro_objeto2.second + (base_objeto2 / 2)) > 
			(centro_objeto1.second - (base_objeto1 / 2))) {
				std::pair<int, int> objetivo((it->second).pedir_id(), 
				(it->second).pedir_id_duenio());
				objetivos.push_back(objetivo);
				continue;
			}
		}

		//verifico que no haya ninguna unidad o edificio dentro del espacio
		//donde se quiere poner el objeto
		if ((centro_objeto2.first <= (centro_objeto1.first + 
		(altura_objeto1 / 2)) && centro_objeto2.first >= 
		(centro_objeto1.first - (altura_objeto1 / 2))) && 
		((centro_objeto2.second <= (centro_objeto1.second + 
		(base_objeto1 / 2)) && centro_objeto2.second >= 
		(centro_objeto1.second - (base_objeto1 / 2))))) {
			std::pair<int, int> objetivo((it->second).pedir_id(), 
			(it->second).pedir_id_duenio());
			objetivos.push_back(objetivo);
			continue;
		}
	}
	return objetivos;
}

bool Mapa::agregar_objeto(std::shared_ptr<ObjetoDune> objeto, int id_objeto, 
std::pair<int, int> centro) {
	bool lugar_valido = false;
	int base_objeto1 = objeto->obtener_base();
	int altura_objeto1 = objeto->obtener_altura();

	std::vector<std::pair<int, int>> objetos_en_espacio = 
	buscar_objetos_en_alrededores(centro, altura_objeto1, base_objeto1);

	if (objetos_en_espacio.empty()) {
		coordenadas[centro.first][centro.second].poner_objeto(objeto);
		mapa_ids_objetos.insert(std::pair<int, ObjetoDune>(id_objeto, *objeto));
		lugar_valido = true;
	}
	return lugar_valido;
}

int Mapa::pedir_id_tipo_objeto(int id_objeto) {
	return (mapa_ids_objetos.at(id_objeto)).pedir_id_tipo();
}

void Mapa::eliminar_objeto(int id_objeto) {
	std::pair<int, int> posicion_objeto = obtener_posicion_objeto(id_objeto);
	mapa_ids_objetos.erase(id_objeto);
	coordenadas[posicion_objeto.first][posicion_objeto.second].
	sacar_objeto();
}

bool Mapa::daniar_objeto(int danio, int id_objeto) {
	if ((mapa_ids_objetos.at(id_objeto)).reducir_vida(danio) <= 0) {
		eliminar_objeto(id_objeto);
		return true;
	} else {
		return false;
	}
}

int Mapa::pedir_costo_objeto(int id_objeto) {
	return (mapa_ids_objetos.at(id_objeto)).obtener_costo();
}

std::pair<int, int> Mapa::obtener_posicion_objeto(int id_objeto) {
	return (mapa_ids_objetos.at(id_objeto)).obtener_centro();
}

std::vector<std::pair<int, int>> Mapa::desenterrar_gusano() {
	int fila_random;
	int columna_random;
	bool espacio_valido = false;
	std::vector<std::pair<int, int>> objetivos;
	while(!espacio_valido) {
		fila_random = rand() % coordenadas.size();
		columna_random = rand() % coordenadas.size();

		std::pair<int, int> posicion_centro(fila_random, columna_random);
		bool es_arena = verificar_terreno_alrededores(posicion_centro,
		ALTO_COMIDA_GUSANO, ANCHO_COMIDA_GUSANO, "arena");
		if (es_arena) {
			objetivos = buscar_objetos_en_alrededores(posicion_centro, 
			ANCHO_COMIDA_GUSANO, ALTO_COMIDA_GUSANO);
			if (!objetivos.empty()) {
				espacio_valido = true;
			}
		}
	}

	for (std::vector<std::pair<int, int>>::iterator it = objetivos.begin();
	it != objetivos.end(); ++it) {
		eliminar_objeto((*it).first);
	}
	return objetivos;
}

unsigned int Mapa::pedir_limite_filas() {
	return coordenadas.size();
}

unsigned int Mapa::pedir_limite_columnas() {
	return (coordenadas[coordenadas.size() - 1]).size();
}

std::string Mapa::pedir_terreno_coordenada(std::pair<int, int> posicion) {
	return coordenadas[posicion.first][posicion.second].obtener_terreno();
}
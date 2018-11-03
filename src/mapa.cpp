#include "mapa.h"
#include "Terrenos/no_especia.h"
#include <stdlib.h> 
#include <iostream>

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
	/*
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
	*/
	return objetivos;
}

/*void Mapa::marcar_coordenadas_ocupadas(std::pair<int, int> pos_central, 
int altura, int base) {
	std::pair<int, int> inicio((pos_central.first + altura/2) - (altura - 1), 
	(pos_central.second + base/2) - (base - 1));
	//for (int i = 0; i <)
}*/

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
		//marcar_coordenadas_ocupadas(centro, altura_objeto1, base_objeto1);
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

bool Mapa::ubicar_unidad(int id_edificio, std::pair<int, int> &centro_unidad) {
	std::pair<int, int> pos_edificio = obtener_posicion_objeto(id_edificio);
	
	//esto deberiamos tomarlo de algun lado, definir donde
	int base_unidad = 1;
	int altura_unidad = 2;

	int rango_x = (mapa_ids_objetos.at(id_edificio)).obtener_base();
	int rango_y = (mapa_ids_objetos.at(id_edificio)).obtener_altura();
	std::pair<int, int> pos_inicial;
	pos_inicial.first = pos_edificio.first - (rango_x/2) - (base_unidad/2) - 1 ;
	pos_inicial.second = pos_edificio.second + (rango_y/2) + (altura_unidad/2) + 1; 
	if (recorrer_horizontal(pos_inicial,rango_x,base_unidad)){
		centro_unidad = pos_inicial;
		return true;
	}
	pos_inicial.second-=altura_unidad;
	if (recorrer_vertical(pos_inicial,rango_y,altura_unidad)){
		centro_unidad = pos_inicial;
		return true;
	}
	pos_inicial.second-= rango_y;
	pos_inicial.first+=base_unidad;
	if (recorrer_horizontal(pos_inicial,rango_x,base_unidad)){
		centro_unidad = pos_inicial;
		return true;
	}
	pos_inicial.first+= rango_x;
	pos_inicial.second+= rango_y + altura_unidad; 
	if (recorrer_vertical(pos_inicial,rango_y,altura_unidad)){
		centro_unidad = pos_inicial;
		return true;
	}
	return false;
}

bool Mapa::recorrer_horizontal(std::pair<int, int> &pos_inicial, int rango,int base) {
	std::pair<int, int> pos_return(pos_inicial);
	for (; pos_return.first <= pos_inicial.first + rango;){
		if (!esta_ocupada_coordenada(pos_return)){
			pos_inicial = pos_return;
			return true;
		}
		pos_return.first+=base;
	}
	return false;
}
bool Mapa::recorrer_vertical(std::pair<int, int> &pos_inicial, int rango,int altura) {
	std::pair<int, int> pos_return(pos_inicial);
	for (; pos_return.second >= pos_inicial.second - rango;){
		if (!esta_ocupada_coordenada(pos_return)){
			pos_inicial = pos_return;
			return true;
		}
		pos_return.second-=altura;
	}
	return false;
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

bool Mapa::esta_ocupada_coordenada(std::pair<int, int> posicion) {
	return coordenadas[posicion.first][posicion.second].esta_ocupada();
}

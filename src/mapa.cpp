#include "mapa.h"
#include "Terrenos/no_especia.h"
#include <stdlib.h>
#include <iostream> 

#define DIMENSION_EXPANSION_BASE 3 //significa que lo minimo que se expande
//la explosion del tanque o el gusano es en un cuadrado de 3x3
#define DIREC_EXPANSION_BASE -1 //define el numero base que se le resta
//a la posicion central desde donde se genera la expansion ya sea del
//gusano o la explosion del tanque

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

bool Mapa::esta_dentro(std::pair<int, int> pos_objeto1, std::pair<int, int>
centro_objeto2, int altura_objeto2, int base_objeto2) {
	if ((pos_objeto1.first <= (centro_objeto2.first + 
		(altura_objeto2 / 2)) && pos_objeto1.first >= 
		(centro_objeto2.first - (altura_objeto2/ 2))) && 
		((centro_objeto2.second <= centro_objeto2.second + 
		(base_objeto2 / 2)) && pos_objeto1.second >= 
		(centro_objeto2.second - (base_objeto2/ 2)))) {
		return true;
	}
	return false;
}

std::vector<int> Mapa::buscar_unidades_alrededor(std::pair<int, int>
centro_unidad, int altura, int base, bool verificar_asentamiento) {
	std::vector<int> unidades_alrededor;

	for (std::map<int, ObjetoDune>::iterator it = 
	mapa_ids_objetos.begin(); it != mapa_ids_objetos.end(); ++it) {
		//veo si el centro del objeto se encuentra dentro del lugar
		//abarcado por la base y la altura
		if(esta_dentro((it->second).obtener_centro(), centro_unidad, 
		altura, base)) {
			if (it->second.obtener_centro() == centro_unidad) continue;
			unidades_alrededor.push_back(it->first);
			if (verificar_asentamiento) break;
		}
		//en caso de querer poner un edificio por cada objeto dune
		//me fijo que no se encuentre atravezando el espacio donde
		//se establecera el edificio
		if (verificar_asentamiento) {
			bool espacio_invalido = false;
			if (espacio_invalido) break;
			std::vector<std::pair<int, int>> direcs_verificacion = {{0, base/2},
			{0, -(base/2)}, {altura/2,0}, {-(altura/2), 0},
			{altura/2, -(base/2)},{-(altura/2), base/2}, 
			{-(altura/2), -(base/2)}, {altura/2, base/2}};
			for (std::vector<std::pair<int, int>>::iterator it_direc = 
			direcs_verificacion.begin(); it_direc != direcs_verificacion.end();
			++it_direc) {
				std::pair<int, int> pos_a_verificar(((it->second).
				obtener_centro().first) + (*it_direc).first, ((it->second).
				obtener_centro().second) + (*it_direc).second);
				if(esta_dentro(pos_a_verificar, centro_unidad, altura, base)) {
					unidades_alrededor.push_back(it->first);
					espacio_invalido = true;
					break;
				}
			}
		}
	}
	return unidades_alrededor;
}

bool Mapa::verificar_terreno_alrededor(std::pair<int, int> centro, 
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
  		}
  		
  		if (coordenadas[centro.first + (*it).first]
  		[centro.second + (*it).second].obtener_terreno() != terreno) {
  			terreno_adecuado = false;
  			break;
  		}
	}
	return terreno_adecuado;
}

void Mapa::marcar_estado_coordenadas_alrededor(std::pair<int, int> pos_central, 
int altura, int base, bool ocupar) {
	std::pair<int, int> inicio((pos_central.first + base/2) - (base - 1), 
	(pos_central.second + altura/2) - (altura- 1));
	for (int i = 0; i < base; i++) {
		for (int j = 0; j < altura; j++) {
			//ignoro el centro ya que ya le agregue el objeto antes
			if (inicio.first == pos_central.first && inicio.second == 
			pos_central.second) {
				inicio.second++;
				continue;
			}
			
			//esto del if dsp se podria reemplazar con un metodo de la coord
			//que le invierta el estado nomas
			if (ocupar){
				coordenadas[inicio.first][inicio.second].
				marcar_como_ocupada();
			} else {
				coordenadas[inicio.first][inicio.second].
				marcar_como_desocupada();
			}
			inicio.second++;
		}
		inicio.second -= altura;
		inicio.first++;
	}
}

void Mapa::agregar_objeto(ObjetoDune* objeto, int id_objeto, 
std::pair<int, int> &centro) {
	int base_objeto1 = objeto->obtener_base();
	int altura_objeto1 = objeto->obtener_altura();
	coordenadas[centro.first][centro.second].poner_objeto(objeto);
	mapa_ids_objetos.insert(std::pair<int, 
	ObjetoDune>(id_objeto, *objeto));
	marcar_estado_coordenadas_alrededor(centro, altura_objeto1, base_objeto1, 
	true);
}

void Mapa::eliminar_objeto(int id_objeto) {
	std::pair<int, int> centro_objeto = (mapa_ids_objetos.at(id_objeto)).
	obtener_centro();
	int altura_objeto = (mapa_ids_objetos.at(id_objeto)).
	obtener_altura();
	int base_objeto = (mapa_ids_objetos.at(id_objeto)).
	obtener_base();
	marcar_estado_coordenadas_alrededor(centro_objeto, altura_objeto,
	base_objeto, false);
	mapa_ids_objetos.erase(id_objeto);
	coordenadas[centro_objeto.first][centro_objeto.second].
	sacar_objeto();
}

std::vector<int> Mapa::desenterrar_gusano(Root &root) {
	int fila_random;
	int columna_random;
	bool espacio_valido = false;
	std::vector<int> objetivos;
	while(!espacio_valido) {
		fila_random = rand() % coordenadas.size();
		columna_random = rand() % coordenadas.size();

		std::pair<int, int> posicion_centro(fila_random, columna_random);
		bool es_arena = verificar_terreno_alrededor(posicion_centro,
		root["Gusano"].get("dimension_alto",0).asInt(), 
		root["Gusano"].get("dimension_ancho",0).asInt(), "arena");
		if (es_arena) {
			objetivos = buscar_unidades_alrededor(posicion_centro, 
			root["Gusano"].get("dimension_alto",0).asInt(),
			 root["Gusano"].get("dimension_ancho",0).asInt(), false);
			if (!objetivos.empty()) {
				espacio_valido = true;
			}
		}
	}

	for (std::vector<int>::iterator it = objetivos.begin();
	it != objetivos.end(); ++it) {
		eliminar_objeto(*it);
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

bool Mapa::agregado_edificio(ObjetoDune* objeto) {
	std::pair<int, int> posicion_central = objeto->obtener_centro();
	bool terreno_valido;
	std::vector<int> unidades_alrededor; 
	terreno_valido = verificar_terreno_alrededor(posicion_central, 
	objeto->obtener_altura(), objeto->obtener_base(), "roca");
	//verifico que no haya ninguna unidad o edificio dentro del espacio
	//donde se quiere poner el objeto
	unidades_alrededor = buscar_unidades_alrededor(posicion_central, 
	objeto->obtener_altura(), objeto->obtener_base(), true);
	if(terreno_valido && unidades_alrededor.empty()) {
		return true;
	}
	return false;
	//FALTA ANALIZAR CASO BORDE SI SE METEN EN EL DIOME PERO
	//NO ENTERAMENTE (NO CON EL CENTRO)
}

/*void Mapa::agregar_edificio(ObjetoDune* objeto, 
int id_objeto, std::pair<int, int> &centro) {
	agregar_objeto(objeto, id_objeto, centro);
}*/

std::pair<int,int> Mapa::pedir_cercania(int id, int id_objetivo) {
	std::pair<int, int> centro_unidad = (mapa_ids_objetos.at(id)).
	obtener_centro();
	std::pair<int, int> centro_objetivo = (mapa_ids_objetos.at(
	id_objetivo).obtener_centro());

	return std::pair<int, int> (abs(centro_unidad.first - 
	centro_objetivo.first), abs(centro_unidad.second - 
	centro_objetivo.second));
}

void Mapa::cambiar_equipo(int id_unidad_a_cambiar, int id_nuevo_duenio) {
	(mapa_ids_objetos.at(id_unidad_a_cambiar)).asignar_duenio(id_nuevo_duenio);
}

bool Mapa::esta_ocupada_coordenada(std::pair<int, int> posicion) {
	return coordenadas[posicion.first][posicion.second].esta_ocupada();
}

bool Mapa::recorrer_horizontal(std::pair<int, int> &pos_inicial, int rango, 
int base) {
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

bool Mapa::recorrer_vertical(std::pair<int, int> &pos_inicial, int rango, 
int altura) {
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

bool Mapa::ubicar_unidad(int id_edificio, std::pair<int, int> &centro_unidad,
	int base_unidad, int altura_unidad) {
	std::pair<int, int> pos_edificio = (mapa_ids_objetos.at(id_edificio)).
	obtener_centro();

	int rango_x = (mapa_ids_objetos.at(id_edificio)).obtener_base();
	int rango_y = (mapa_ids_objetos.at(id_edificio)).obtener_altura();
	std::pair<int, int> pos_inicial;
	pos_inicial.first = pos_edificio.first - (rango_x/2) - 
	(base_unidad/2) - 1 ;
	pos_inicial.second = pos_edificio.second + (rango_y/2) + 
	(altura_unidad/2) + 1; 
	
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

std::vector<std::pair<int, int>> Mapa::mover(int id_unidad, 
std::pair<int, int> &pos_destino) {
	ObjetoDune objeto = mapa_ids_objetos.at(id_unidad);
	std::pair<int, int> centro_objeto = objeto.obtener_centro();
	std::vector<std::pair<int, int>> camino = buscador_mejor_camino.
	buscar_mejor_camino(*this, centro_objeto, pos_destino);
	marcar_estado_coordenadas_alrededor(centro_objeto, 
	objeto.obtener_altura(), objeto.obtener_base(), false);
	coordenadas[centro_objeto.first][centro_objeto.second].sacar_objeto();
	coordenadas[camino[camino.size() / 3].first][camino[camino.size() / 3].
	second].poner_objeto(&(mapa_ids_objetos.at(id_unidad)));
	marcar_estado_coordenadas_alrededor(camino[camino.size() / 3], 
	objeto.obtener_altura(), objeto.obtener_base(), true);
	std::vector<std::pair<int, int>> sub_camino(&camino[0], 
	&camino[camino.size() / 3]);
	return sub_camino;
}

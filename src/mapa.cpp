#include "mapa.h"
#include "Terrenos/terreno.h"
#include "Edificios/refineria.h"
#include "UnidadesMovibles/cosechadora.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

//codigos de terrenos para el protocolo
#define CODIGO_ROCA 30
#define CODIGO_DUNA 31
#define CODIGO_ESPECIAFUERTE 32
#define CODIGO_ESPECIASUAVE 33
#define CODIGO_CIMA 34
#define CODIGO_PRECIPICIO 35
#define CODIGO_ARENA 36

#define LIMITE_ITERACIONES_GUSANO 100

Mapa::Mapa() {}

Mapa::Mapa(Config &root,int &contador_ids_objetos) : cant_pixeles_por_baldosa(root["cant_pixeles_por_baldosa"].asInt()) {
	for (unsigned int i = 0; i < root["terreno"].size(); i++) {
		std::vector<Baldosa> fila_baldosa;
			std::vector<Coordenada> fila;
			for (unsigned int j = 0; j < root["terreno"][0].size(); j++) {
				std::pair<int,int> esquina(i,j);
					switch (root["terreno"][i][j].asInt()){
						case CODIGO_ROCA:
						{
							Terreno roca(CODIGO_ROCA, root);
							Baldosa bald(0, roca, contador_ids_objetos,
							std::pair<int, int> (i*root["tamanio_terreno"].asInt(),
							 j*root["tamanio_terreno"].asInt()));
							for (int q = 0; q < root["cant_pixeles_por_baldosa"].asInt(); q++){ 
								Coordenada coord(0, roca);
								fila.push_back(coord);
							}
							bald.serializar_mensaje_baldosa(
								root["tamanio_terreno"].asInt());
							fila_baldosa.push_back(bald);
							break;
						}
						case CODIGO_DUNA:
						{
							Terreno duna(CODIGO_DUNA, root);
							Baldosa bald(0, duna, contador_ids_objetos,
							std::pair<int, int> (i*root["tamanio_terreno"].asInt(),
							 j*root["tamanio_terreno"].asInt()));
							for (int q = 0; q < root["cant_pixeles_por_baldosa"].asInt(); q++){ 
								Coordenada coord(0, duna);
								fila.push_back(coord);
							}
							bald.serializar_mensaje_baldosa(
								root["tamanio_terreno"].asInt());
							fila_baldosa.push_back(bald);
							break;
						}
						case CODIGO_ESPECIAFUERTE:
						{
							Terreno especiafuerte(CODIGO_ESPECIAFUERTE, root);
							std::shared_ptr<Baldosa> bald(new 
							Baldosa(0, especiafuerte, contador_ids_objetos,
							std::pair<int, int> (i*root["tamanio_terreno"].asInt(),
							 j*root["tamanio_terreno"].asInt())));
							for (int q = 0; q < root["cant_pixeles_por_baldosa"].asInt(); q++){ 
								Coordenada coord(0, especiafuerte);
								fila.push_back(coord);
							}
							bald->serializar_mensaje_baldosa(
								root["tamanio_terreno"].asInt());
							fila_baldosa.push_back(*bald);
							terrenos_con_especia.emplace(
							std::pair<int, std::shared_ptr<Baldosa>>(
							contador_ids_objetos, bald));
							break;
						}
						case CODIGO_ESPECIASUAVE:
						{
							Terreno especiasuave(CODIGO_ESPECIASUAVE, root);
							std::shared_ptr<Baldosa> bald(new 
							Baldosa(0, especiasuave, contador_ids_objetos,
							std::pair<int, int> (i*root["tamanio_terreno"].asInt(),
							 j*root["tamanio_terreno"].asInt())));
							for (int q = 0; q < root["cant_pixeles_por_baldosa"].asInt(); q++){ 
								Coordenada coord(0, especiasuave);
								fila.push_back(coord);
							}
							bald->serializar_mensaje_baldosa(
								root["tamanio_terreno"].asInt());
							fila_baldosa.push_back(*bald);
							terrenos_con_especia.emplace(
							std::pair<int, std::shared_ptr<Baldosa>>(
							contador_ids_objetos, bald));
							break;
						}
						case CODIGO_CIMA:
						{
							Terreno cima(CODIGO_CIMA, root);
							Baldosa bald(0, cima, contador_ids_objetos,
							std::pair<int, int> (i*root["tamanio_terreno"].asInt(),
							 j*root["tamanio_terreno"].asInt()));
							for (int q = 0; q < root["cant_pixeles_por_baldosa"].asInt(); q++){ 
								Coordenada coord(0, cima);
								fila.push_back(coord);
							}
							bald.serializar_mensaje_baldosa(
								root["tamanio_terreno"].asInt());
							fila_baldosa.push_back(bald);
							break;
						}
						case CODIGO_PRECIPICIO:
						{
							Terreno precipio(CODIGO_PRECIPICIO, root);
							Baldosa bald(0, precipio, contador_ids_objetos,
							std::pair<int, int> (i*root["tamanio_terreno"].asInt(),
							 j*root["tamanio_terreno"].asInt()));
							for (int q = 0; q < root["cant_pixeles_por_baldosa"].asInt(); q++){ 
								Coordenada coord(0, precipio);
								fila.push_back(coord);
							}
							bald.serializar_mensaje_baldosa(
								root["tamanio_terreno"].asInt());
							fila_baldosa.push_back(bald);
							break;
						}
						default:
						{
							Terreno arena(CODIGO_ARENA, root);							
							Baldosa bald(0, arena, contador_ids_objetos,
							std::pair<int, int> (i*root["tamanio_terreno"].asInt(),
							 j*root["tamanio_terreno"].asInt()));
							for (int q = 0; q < root["cant_pixeles_por_baldosa"].asInt(); q++){ 
								Coordenada coord(0, arena);
								fila.push_back(coord);
							}
							fila_baldosa.push_back(bald);
							break;
						}
					}
					contador_ids_objetos++;
			}
			for (int p = 0; p < root["cant_pixeles_por_baldosa"].asInt(); p++){ 
			coordenadas.push_back(fila);
		}
		baldosas.push_back(fila_baldosa);
	}
	//cant_pixeles_por_baldosa = root["cant_pixeles_por_baldosa"].asInt();
	Conversor con(root["cant_pixeles_por_baldosa"].asInt());
	conversor = std::move(con);
	Gusano gus(root);
	gusano = std::move(gus);
}


bool Mapa::esta_dentro(std::pair<int, int> pos_objeto1, std::pair<int, int>
centro_objeto2, int altura_objeto2, int base_objeto2) {
	if ((pos_objeto1.first <= (centro_objeto2.first + 
		(altura_objeto2 / 2)) && pos_objeto1.first >= 
		(centro_objeto2.first - (altura_objeto2/ 2))) && 
		((pos_objeto1.second <= centro_objeto2.second + 
		(base_objeto2 / 2)) && pos_objeto1.second >= 
		(centro_objeto2.second - (base_objeto2/ 2)))) {
		return true;
	}
	return false;
}
std::vector<ObjetoDune*> Mapa::buscar_unidades_devastador(
	UnidadMovible *unidad){
	std::vector<ObjetoDune*> unidades_alrededor;
	for (std::map<int, ObjetoDune*>::iterator it = 
	mapa_ids_objetos.begin(); it != mapa_ids_objetos.end(); ++it) {
		if (unidad->pedir_id()==(it->second)->pedir_id()){
			continue;
		}
		std::pair<int,int> cercania = pedir_cercania(unidad->pedir_id(), 
			(it->second)->pedir_id());
		if ( cercania.first < unidad->obtener_rango_ataque() ||
		 cercania.second < unidad->obtener_rango_ataque()) {
			unidades_alrededor.push_back(it->second);
		}
	}
	return unidades_alrededor;
}

std::vector<ObjetoDune*> Mapa::buscar_unidades_alrededor(std::pair<int, int>
centro_unidad, int altura, int base, bool verificar_asentamiento,
bool verificar_ataque_a_enemigo, int id_duenio, bool es_gusano) {
	std::vector<ObjetoDune*> unidades_alrededor;
	bool espacio_invalido = false;
	for (std::map<int, ObjetoDune*>::iterator it = 
	mapa_ids_objetos.begin(); it != mapa_ids_objetos.end(); ++it) {
		//veo si el centro del objeto se encuentra dentro del lugar
		//abarcado por la base y la altura
		if(esta_dentro((it->second)->obtener_centro(), centro_unidad, 
		altura, base)) {
			//si tienen el mismo centro es que es la misma unidad, la salteo
			//excpeto que sea el gusano  que puede emerger del mismo lugar
			//de donde esta la unidad
			if ((it->second)->obtener_centro() == centro_unidad && !es_gusano &&
			!verificar_asentamiento) continue;
			if (verificar_ataque_a_enemigo) {
				if (id_duenio != (it->second)->pedir_id_duenio()) {
					unidades_alrededor.push_back(it->second);
					break;
				}
			} else {
				unidades_alrededor.push_back(it->second);
				if (verificar_asentamiento) break;
			}
		}
		//en caso de querer poner un edificio por cada objeto dune
		//me fijo que no se encuentre atravezando el espacio donde
		//se establecera el edificio
		if (verificar_asentamiento) {
			if (espacio_invalido) break;
			std::vector<std::pair<int, int>> direcs_verificacion = {{0, base/2},
			{0, -(base/2)}, {altura/2,0}, {-(altura/2), 0},
			{altura/2, -(base/2)},{-(altura/2), base/2}, 
			{-(altura/2), -(base/2)}, {altura/2, base/2}};
			for (std::vector<std::pair<int, int>>::iterator it_direc = 
			direcs_verificacion.begin(); it_direc != direcs_verificacion.end();
			++it_direc) {
				std::pair<int, int> pos_a_verificar(((it->second)->
				obtener_centro().first) + (*it_direc).first, ((it->second)->
				obtener_centro().second) + (*it_direc).second);
				if(esta_dentro(pos_a_verificar, centro_unidad, altura, base)) {
					unidades_alrededor.push_back(it->second);
					espacio_invalido = true;
					break;
				}
			}
		}
	}
	return unidades_alrededor;
}

bool Mapa::verificar_terreno_alrededor(std::pair<int, int> centro, 
int altura, int base, int terreno) {
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

void Mapa::marcar_estado_baldosas_alrededor(std::pair<int, int> pos_central, 
int altura, int base, bool ocupar) {
	std::pair<int, int> inicio((pos_central.first + altura/2) - (altura - 1), 
	(pos_central.second + base/2) - (base- 1));
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < base; j++) {
			//ignoro el centro ya que ya le agregue el objeto antes
			if (inicio.first == pos_central.first && inicio.second == 
			pos_central.second) {
				inicio.second++;
				continue;
			}
			if (ocupar){

				baldosas[inicio.first][inicio.second].
				marcar_como_ocupada_edificio();
				// "esta ocupada " << inicio.first << " " << inicio.second << std::endl;
			} else {
				baldosas[inicio.first][inicio.second].
				marcar_como_desocupada();
			}
			inicio.second++;
		}
		inicio.second -= base;
		inicio.first++;
	}
}

void Mapa::agregar_objeto(ObjetoDune* objeto, int id_objeto, 
std::pair<int, int> &centro, bool edif) {
	int base_objeto = objeto->obtener_base();
	int altura_objeto = objeto->obtener_altura();
	coordenadas[centro.first][centro.second].poner_objeto(objeto);
	std::pair <int,int> bald(conversor.de_pixel_a_baldosa(centro));
	if (edif){
		baldosas[bald.first][bald.second].poner_edificio(objeto);
	} else {
		baldosas[bald.first][bald.second].poner_unidad(objeto);
	}
	mapa_ids_objetos.emplace(std::pair<int, 
	ObjetoDune*>(id_objeto, objeto));
	marcar_estado_baldosas_alrededor(bald,
	 altura_objeto/cant_pixeles_por_baldosa,
	  base_objeto/cant_pixeles_por_baldosa,
	true);
}

void Mapa::eliminar_objeto(int id_objeto) {
	std::pair<int, int> centro_objeto = (mapa_ids_objetos.at(id_objeto))->
	obtener_centro();
	std::pair <int,int> bald(conversor.de_pixel_a_baldosa(centro_objeto));
	int altura_objeto = (mapa_ids_objetos.at(id_objeto))->
	obtener_altura();
	int base_objeto = (mapa_ids_objetos.at(id_objeto))->
	obtener_base();
	marcar_estado_baldosas_alrededor(bald,
	 altura_objeto/cant_pixeles_por_baldosa,
	  base_objeto/cant_pixeles_por_baldosa,
	false);
	mapa_ids_objetos.erase(id_objeto);
	coordenadas[centro_objeto.first][centro_objeto.second].
	sacar_objeto();
	baldosas[bald.first][bald.second].sacar_objeto();
	if (refinerias.count(id_objeto) > 0) {
		refinerias.erase(id_objeto);
	}
}

void Mapa::desenterrar_gusano() {
	int fila_random;
	int columna_random;
	bool espacio_valido = false;
	std::vector<ObjetoDune*> objetivos;
	int limite_salida = 0;
	while(!espacio_valido) {
		if (limite_salida == LIMITE_ITERACIONES_GUSANO) break;
		fila_random = rand() % coordenadas.size();
		columna_random = rand() % coordenadas.size();
		std::pair<int, int> posicion_centro(fila_random, columna_random);
		bool es_arena = verificar_terreno_alrededor(posicion_centro,
		gusano.obtener_dimesion_alto(), 
		gusano.obtener_dimesion_ancho(), CODIGO_ARENA);
		if (es_arena) {
			gusano.asignar_centro(posicion_centro);
			objetivos = buscar_unidades_alrededor(posicion_centro, 
			gusano.obtener_dimesion_alto(),
			gusano.obtener_dimesion_ancho(), false, 
			false, -1, true);
			espacio_valido = true;
			break;
		}
		limite_salida++;
	}
	for (std::vector<ObjetoDune*>::iterator it = objetivos.begin();
	it != objetivos.end(); ++it) {
		(*it)->matar();
	}
}

unsigned int Mapa::pedir_limite_filas() {
	return coordenadas.size();
}

unsigned int Mapa::pedir_limite_columnas() {
	return (coordenadas[coordenadas.size() - 1]).size();
}

int Mapa::pedir_terreno_coordenada(std::pair<int, int> posicion) {
	return coordenadas[posicion.first][posicion.second].obtener_terreno();
}

unsigned int Mapa::pedir_limite_filas_baldosa() {
	return baldosas.size();
}

unsigned int Mapa::pedir_limite_columnas_baldosa() {
	return (baldosas[baldosas.size() - 1]).size();
}

int Mapa::pedir_terreno_baldosa(std::pair<int, int> posicion) {
	return baldosas[posicion.first][posicion.second].obtener_terreno();
}

bool Mapa::agregado_edificio(ObjetoDune* objeto) {
	std::pair<int, int> posicion_central = objeto->obtener_centro();
	bool terreno_valido;
	std::vector<ObjetoDune*> unidades_alrededor; 
	terreno_valido = verificar_terreno_alrededor(posicion_central, 
	objeto->obtener_altura(), objeto->obtener_base(), CODIGO_ROCA);
	//verifico que no haya ninguna unidad o edificio dentro del espacio
	//donde se quiere poner el objeto
	if (terreno_valido) {
		unidades_alrededor = buscar_unidades_alrededor(posicion_central, 
		objeto->obtener_altura(), objeto->obtener_base(), true, false, -1, 
		false);
	} else {
		return false;
	}
	if(unidades_alrededor.empty()) {
		return true;
	}
	return false;
}

std::pair<int,int> Mapa::pedir_cercania(int id, int id_objetivo) {
	std::pair<int, int> centro_unidad = (mapa_ids_objetos.at(id))->
	obtener_centro();
	std::pair<int, int> centro_objetivo;
	if (mapa_ids_objetos.count(id_objetivo) > 0) {
		centro_objetivo = (mapa_ids_objetos.at(
		id_objetivo)->obtener_esquina());
	} else {
		centro_objetivo = (terrenos_con_especia.at(
		id_objetivo)->obtener_centro());
	}
	return std::pair<int, int> (abs(centro_unidad.first - 
	centro_objetivo.first), abs(centro_unidad.second - 
	centro_objetivo.second));
}

void Mapa::cambiar_equipo(int id_unidad_a_cambiar, int id_nuevo_duenio) {
	(mapa_ids_objetos.at(id_unidad_a_cambiar))->asignar_duenio(id_nuevo_duenio);
}

bool Mapa::esta_ocupada_coordenada(std::pair<int, int> posicion) {
	return coordenadas[posicion.first][posicion.second].esta_ocupada();
}

bool Mapa::esta_ocupada_baldosa(std::pair<int, int> posicion) {
	return baldosas[posicion.first][posicion.second].esta_ocupada_edificio();
}

std::pair<int, int> Mapa::de_baldosa_a_pixel(std::pair<int, int> baldosa) {
	return conversor.de_baldosa_a_pixel(baldosa);
}

std::pair<int, int> Mapa::de_pixel_a_baldosa(std::pair<int, int> pixel) {
	return conversor.de_pixel_a_baldosa(pixel);
}

bool Mapa::esta_dentro_limites(std::pair<int, int> &centro){
	if (0 <= centro.first && centro.first < (int)pedir_limite_filas() &&
	 0 <= centro.second && centro.second < (int)pedir_limite_columnas()) {
		return true;
	}
	return false;
}

bool Mapa::recorrer_horizontal(std::pair<int, int> &pos_inicial, int rango, 
std::shared_ptr<UnidadMovible> unidad) {
	std::pair<int, int> pos_return(pos_inicial);
	for (; pos_return.second <= pos_inicial.second + rango;){
		if (esta_dentro_limites(pos_return) && 
			!esta_ocupada_coordenada(pos_return) && 
			unidad->es_terreno_valido(pedir_terreno_coordenada(pos_return))){
			pos_inicial = pos_return;
			return true;
		}
		pos_return.second+=unidad->obtener_base();
	}
	return false;
}

bool Mapa::recorrer_vertical(std::pair<int, int> &pos_inicial, int rango, 
std::shared_ptr<UnidadMovible> unidad) {
	std::pair<int, int> pos_return(pos_inicial);
	for (; pos_return.first >= pos_inicial.first - rango;){
		if (esta_dentro_limites(pos_return) && 
			!esta_ocupada_coordenada(pos_return) && 
			unidad->es_terreno_valido(pedir_terreno_coordenada(pos_return))){
			pos_inicial = pos_return;
			return true;
		}
		pos_return.first-=unidad->obtener_altura();
	}
	return false;
}

bool Mapa::ubicar_unidad(int id_edificio, std::pair<int, int> &centro_unidad,
	std::shared_ptr<UnidadMovible> unidad) {
	std::pair<int, int> pos_edificio = (mapa_ids_objetos.at(id_edificio))->
	obtener_centro();
	int rango_x = (mapa_ids_objetos.at(id_edificio))->obtener_base();
	int rango_y = (mapa_ids_objetos.at(id_edificio))->obtener_altura();
	std::pair<int, int> pos_inicial;

	pos_inicial.first = pos_edificio.first + (rango_y/2) +
	(unidad->obtener_altura()/2) + 1;
	pos_inicial.second = pos_edificio.second - (rango_x/2) -
	(unidad->obtener_base()/2); 
	if (recorrer_horizontal(pos_inicial,rango_y,unidad)){
		centro_unidad = pos_inicial;
		return true;
	}

	pos_inicial.first-=unidad->obtener_altura();

	if (recorrer_vertical(pos_inicial,rango_x,unidad)){
		centro_unidad = pos_inicial;
		return true;
	}
	
	pos_inicial.first-= rango_y;
	pos_inicial.second+=unidad->obtener_base();

	if (recorrer_horizontal(pos_inicial,rango_y,unidad)){
		centro_unidad = pos_inicial;
		return true;
	}
	
	pos_inicial.second+= rango_x;
	pos_inicial.first+= rango_y + unidad->obtener_altura(); 

	if (recorrer_vertical(pos_inicial,rango_x,unidad)){
		centro_unidad = pos_inicial;
		return true;
	}
	
	return false;
}

void Mapa::mover_unidad(int id_unidad, 
std::pair<int, int> pos_destino) {
	std::pair<int, int> centro_unidad = mapa_ids_objetos.at(id_unidad)->
	obtener_centro();
	coordenadas[centro_unidad.first][centro_unidad.second].sacar_objeto();
	coordenadas[pos_destino.first][pos_destino.second].poner_objeto(
	mapa_ids_objetos.at(id_unidad));
	mapa_ids_objetos.at(id_unidad)->set_centro(pos_destino);
}

std::list<std::pair<int, int>> Mapa::obtener_camino_misma_baldosa(
std::pair<int, int> inicio, std::pair<int, int> final, UnidadMovible *unidad){
	std::list<std::pair<int, int>> dentro_baldosa;
	std::pair<int, int> pixel(inicio);
	int diff_first = final.first - inicio.first;
	int diff_second = final.second - inicio.second;
    int neg_sec = 1;
    int neg_first = 1;
	if (diff_first < 0){
		diff_first*=-1;
		neg_first = -1;
	}
	if (diff_second < 0){
		diff_second*=-1;
		neg_sec = -1;
	}
	for (int i = 0; i <= diff_second; i++){
		for (int j = 0; j <= diff_first; j++){
			dentro_baldosa.push_back(pixel);
			if (pixel.first == final.first){
				break;
			}
			pixel.first+=neg_first;
		}
		pixel.second+=neg_sec;
		if (pixel.second == final.second){
			break;
		}
	}
	return dentro_baldosa;
}

std::list<std::pair<int, int>> Mapa::obtener_camino(std::pair<int, int> inicio,
std::pair<int, int> final, UnidadMovible *unidad) {
	std::pair<int, int> inicio_baldosa = conversor.de_pixel_a_baldosa(inicio);
	std::pair<int, int> final_baldosa = conversor.de_pixel_a_baldosa(final);

/*	std::cout << "Quiero ir desde " << inicio.first << '-' << inicio.second << std::endl;
	std::cout << "Quiero ir hacia " << final.first << '-' << final.second << std::endl;

	std::cout << "Quiero ir desde " << inicio_baldosa.first << '-' << inicio_baldosa.second << std::endl;
	std::cout << "Quiero ir hacia " << final_baldosa.first << '-' << final_baldosa.second << std::endl;*/

	//si quiere ir hacia una baldosa invalida directamente la unidad no se mueve
	if(!unidad->es_terreno_valido(baldosas[final_baldosa.first]
			[final_baldosa.second].obtener_terreno())){
		std::list<std::pair<int, int>> mismo_lugar;
		std::pair<int, int> pixel_actual(inicio);
		mismo_lugar.push_back(pixel_actual);
		return mismo_lugar;
	}

	if (inicio_baldosa == final_baldosa){
		std::list<std::pair<int, int>> misma_baldosa = obtener_camino_misma_baldosa(inicio, final, unidad);
		return misma_baldosa;
	}
	std::list<std::pair<int, int>> lista_camino = 
	buscador_mejor_camino.buscar_mejor_camino(*this, inicio_baldosa,
	 final_baldosa, unidad);

	std::list<std::pair<int, int>> primer_baldosa;
	primer_baldosa.merge(obtener_camino_misma_baldosa(inicio, conversor.de_baldosa_a_pixel(inicio_baldosa), unidad));

	//primer_baldosa.splice(lista_camino.begin(), obtener_camino_misma_baldosa(inicio, conversor.de_baldosa_a_pixel(inicio_baldosa), unidad));

  	for (std::list<std::pair<int, int>>::iterator it=lista_camino.begin();
  	 it != lista_camino.end(); ++it){
  		//obtengo diff para sacar camino en pixeles entre nodos
  		int diff_first = it->first - inicio_baldosa.first;
  		int diff_second = it->second - inicio_baldosa.second;
  		inicio_baldosa.first = it->first;
		inicio_baldosa.second = it->second;
    	*it = conversor.de_baldosa_a_pixel(*it);

    	int neg_sec = 0;
    	int neg_first = 0;
    	if (diff_first == -1){
    		neg_first = 1;
    	}
    	if (diff_second == -1){
    		neg_sec = 1;
    	}

    	for(int i = cant_pixeles_por_baldosa ; i > 0 ; i--){
    		std::pair<int,int> sig(((it->first+=diff_first) + (i*neg_first)),
    			(it->second+=diff_second) + (i*neg_sec));
    		lista_camino.insert(it,sig);
	    	if (neg_first == 1){
	    		it->first-=diff_first;
	    	}
	    	if (neg_sec == 1){
				it->second-=diff_second;
	    	}

	    	if (inicio_baldosa == final_baldosa){
				std::list<std::pair<int, int>> dentro_baldosa = 
				obtener_camino_misma_baldosa(sig, final, unidad);
				lista_camino.splice(lista_camino.end(), dentro_baldosa);
				primer_baldosa.splice(primer_baldosa.end(), lista_camino);
				return primer_baldosa;
				break;
	    	}
		}
    	if (inicio_baldosa == final_baldosa){
    		break;
    	}
  	}
	return primer_baldosa;
}

bool Mapa::actualizar_salida_gusano(int tiempo_transcurrido,
std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes) {
	int salio = gusano.actualizar_salida(tiempo_transcurrido);
	if (salio) {
		desenterrar_gusano();
		MensajeProtocolo mensaje = gusano.
		serializar_mensaje_salida();
		guardar_mensaje_en_colas(colas_mensajes, mensaje);
		gusano.limpiar_mensaje();
	}
	return salio;
}

ObjetoDune* Mapa::obtener_objeto(int id_objeto) {
	ObjetoDune *objeto = mapa_ids_objetos.at(id_objeto);
	return objeto;
}

void Mapa::agregar_refineria(Refineria *refineria) {
	refinerias.emplace(std::pair<int, Refineria*>(refineria->pedir_id(),
	refineria));
}

Refineria* Mapa::obtener_refineria_mas_cercana(Cosechadora* cosechadora) {
	Refineria* refineria_objetivo = NULL;
	int distancia_a_ref_mas_cercana = -1;
	for (std::map<int, Refineria*>::iterator it = 
	refinerias.begin(); it != refinerias.end(); ++it) {
		if (it->second->pedir_id_duenio() != cosechadora->pedir_id_duenio()) {
			continue;
		}
		int distancia_a_refineria = calcular_distancia(
		cosechadora->obtener_centro(), it->second->obtener_centro());
		if (distancia_a_ref_mas_cercana == -1) {
			refineria_objetivo = it->second;
			distancia_a_ref_mas_cercana = distancia_a_refineria;
		} else {
			if (distancia_a_refineria < distancia_a_ref_mas_cercana) {
				distancia_a_ref_mas_cercana = distancia_a_refineria;
				refineria_objetivo = it->second;
			}
		}
	}
	return refineria_objetivo;
}

int Mapa::calcular_distancia(std::pair<int, int> p1, std::pair<int, int> p2) {
	return sqrt((p2.first - p1.first) * (p2.first - p1.first)  + 
	(p2.second - p1.second) * (p2.second - p1.second));
}

std::shared_ptr<Baldosa> Mapa::obtener_especia_cercana(UnidadMovible* unidad){
//	// "Mapa::obtener_especia_cercana" << std::endl;
	for (std::map<int, std::shared_ptr<Baldosa>>::iterator it_baldosas = 
		terrenos_con_especia.begin(); it_baldosas!=terrenos_con_especia.end();
		 ++it_baldosas){
		std::pair <int,int> dist = pedir_cercania(unidad->pedir_id(),
			it_baldosas->second->pedir_id());
		if (dist.first < (cant_pixeles_por_baldosa*5) &&
			dist.second < (cant_pixeles_por_baldosa*5)){
	//		// "Mapa::obtener_especia_cercana encontre especia menor a "<< cant_pixeles_por_baldosa*5 <<" pixeles dist" << std::endl;
			std::shared_ptr<Baldosa> nueva_especia = it_baldosas->second;
			return nueva_especia;
		}
	}
//
//	// "Mapa::obtener_especia_cercana no hay especia cerca perro" << std::endl;
	return NULL;
}


std::shared_ptr<Baldosa> Mapa::obtener_baldosa_con_especia(
int id_objeto) {
	return terrenos_con_especia.at(id_objeto);
}

std::vector<MensajeProtocolo> Mapa::obtener_mensajes_terrenos_sin_especia() {
	std::vector<MensajeProtocolo> mensajes_terrenos_sin_especia;
	for (std::map<int, std::shared_ptr<Baldosa>>::iterator it = 
	terrenos_con_especia.begin(); it != terrenos_con_especia.end(); ++it) {
		std::vector<MensajeProtocolo> mensajes = it->second->
		obtener_mensajes_para_mandar();
		for (std::vector<MensajeProtocolo>::iterator it_mensajes = 
		mensajes.begin(); it_mensajes != mensajes.end(); ++it_mensajes) {
			mensajes_terrenos_sin_especia.push_back(*it_mensajes);
		}
		it->second->limpiar_lista_mensajes();
	}
	return mensajes_terrenos_sin_especia;
}

std::map<int, Refineria*> Mapa::pedir_refinerias() {
	return refinerias;
}

void Mapa::terreno_inicial(std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes){
	for (unsigned int i = 0 ; i < baldosas.size() ; i++){
		for (unsigned int j = 0 ; j < baldosas[0].size() ; j++){
			std::vector<MensajeProtocolo> mensajes = baldosas[i][j].obtener_mensajes_para_mandar();
			// << baldosas[i][j].cantidad_mensajes() << std::endl;
			for (std::vector<MensajeProtocolo>::iterator it_mensajes = 
			mensajes.begin(); it_mensajes != mensajes.end(); ++it_mensajes) {
				std::vector<int> v = (*it_mensajes).pedir_parametros();

				//std::cout << "Mensaje de accion " << (*it_mensajes).pedir_accion() << v[4] << v[5] << std::endl;
				guardar_mensaje_en_colas(colas_mensajes, *it_mensajes);
			}
			baldosas[i][j].limpiar_lista_mensajes();
		}
	}
	/*MensajeProtocolo mensaje;
	mensaje.asignar_accion('h');
	mensaje.agregar_parametro(0);
	mensaje.agregar_parametro(0);
	mensaje.agregar_parametro(3500);
	mensaje.agregar_parametro(5000);
	guardar_mensaje_en_colas(colas_mensajes, mensaje);*/
}

void Mapa::guardar_mensaje_en_colas(
std::map<int, std::shared_ptr<ColaBloqueante>> colas,
MensajeProtocolo mensaje) {
	for (std::map<int, std::shared_ptr<ColaBloqueante>>::iterator
	it = colas.begin(); it != colas.end(); ++it) {
		(it->second)->push(std::move(mensaje));
	} 
}

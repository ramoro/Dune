#include "mapa.h"
#include "Terrenos/no_especia.h"
#include "Terrenos/especia.h"
#include "Edificios/refineria.h"
#include "UnidadesMovibles/cosechadora.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>


#define LIMITE_ITERACIONES_GUSANO 100
#define PIX 10

Mapa::Mapa() {}

Mapa::Mapa(Config &root,int &contador_ids_objetos) {
	for (unsigned int i = 0; i < root["terreno"].size(); i++) {
		std::vector<Baldosa> fila_baldosa;
			std::vector<Coordenada> fila;
			for (unsigned int j = 0; j < root["terreno"][0].size(); j++) {
					switch (root["terreno"][i][j].asInt()){
						case 30:
						{
							NoEspecia roca("roca");
							Baldosa bald(0, roca, contador_ids_objetos,
							std::pair<int, int> (i, j));
							for (unsigned int q = 0; q < PIX; q++){ 
								Coordenada coord(0, roca);
								fila.push_back(coord);
							}
							fila_baldosa.push_back(bald);
							break;
						}
						case 31:
						{
							NoEspecia duna("duna");
							Baldosa bald(0, duna, contador_ids_objetos,
							std::pair<int, int> (i, j));
							for (unsigned int q = 0; q < PIX; q++){ 
								Coordenada coord(0, duna);
								fila.push_back(coord);
							}
							fila_baldosa.push_back(bald);
							break;
						}
						case 32:
						{
							Especia especiafuerte("especia fuerte", root);
							std::shared_ptr<Baldosa> bald(new 
							Baldosa(0, especiafuerte, contador_ids_objetos,
							std::pair<int, int> (i, j)));
							for (unsigned int q = 0; q < PIX; q++){ 
								Coordenada coord(0, especiafuerte);
								fila.push_back(coord);
							}
							fila_baldosa.push_back(*bald);
							terrenos_con_especia.emplace(
							std::pair<int, std::shared_ptr<Baldosa>>(
							contador_ids_objetos, bald));
							std::cout << "ID ESFUER " << contador_ids_objetos << "con pos x " << i << " pos y " << j<<std::endl;
							break;
						}
						case 33:
						{
							Especia especiasuave("especia suave", root);
							std::shared_ptr<Baldosa> bald(new 
							Baldosa(0, especiasuave, contador_ids_objetos,
							std::pair<int, int> (i, j)));
							for (unsigned int q = 0; q < PIX; q++){ 
								Coordenada coord(0, especiasuave);
								fila.push_back(coord);
							}
							fila_baldosa.push_back(*bald);
							terrenos_con_especia.emplace(
							std::pair<int, std::shared_ptr<Baldosa>>(
							contador_ids_objetos, bald));
							break;
						}
						case 34:
						{
							NoEspecia cima("cima");
							Baldosa bald(0, cima, contador_ids_objetos,
							std::pair<int, int> (i, j));
							for (unsigned int q = 0; q < PIX; q++){ 
								Coordenada coord(0, cima);
								fila.push_back(coord);
							}
							fila_baldosa.push_back(bald);
							break;
						}
						case 35:
						{
							NoEspecia precipio("precipicio");
							Baldosa bald(0, precipio, contador_ids_objetos,
							std::pair<int, int> (i, j));
							for (unsigned int q = 0; q < PIX; q++){ 
								Coordenada coord(0, precipio);
								fila.push_back(coord);
							}
							fila_baldosa.push_back(bald);
							break;
						}
						default:
						{
							NoEspecia arena("arena");							
							Baldosa bald(0, arena, contador_ids_objetos,
							std::pair<int, int> (i, j));
							for (unsigned int q = 0; q < PIX; q++){ 
								Coordenada coord(0, arena);
								fila.push_back(coord);
							}
							fila_baldosa.push_back(bald);
							break;
						}
					}
					contador_ids_objetos++;
			}
			for (unsigned int p = 0; p < PIX; p++){ 
			coordenadas.push_back(fila);
		}
		baldosas.push_back(fila_baldosa);
	}
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

void Mapa::marcar_estado_coordenadas_alrededor(std::pair<int, int> pos_central, 
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
			
			//esto del if dsp se podria reemplazar con un metodo de la coord
			//que le invierta el estado nomas
			if (ocupar){
				//coordenadas[inicio.first][inicio.second].
				//marcar_como_ocupada();
				//std::cout << "esta ocupada " << inicio.first << " " << inicio.second << std::endl;
			} else {
				coordenadas[inicio.first][inicio.second].
				marcar_como_desocupada();
			}
			inicio.second++;
		}

		inicio.second -= base;
		inicio.first++;
	}
}

void Mapa::agregar_objeto(ObjetoDune* objeto, int id_objeto, 
std::pair<int, int> &centro) {
	int base_objeto1 = objeto->obtener_base();
	int altura_objeto1 = objeto->obtener_altura();
	coordenadas[centro.first][centro.second].poner_objeto(objeto);
	mapa_ids_objetos.emplace(std::pair<int, 
	ObjetoDune*>(id_objeto, objeto));
	marcar_estado_coordenadas_alrededor(centro, altura_objeto1, base_objeto1, 
	true);
}

void Mapa::eliminar_objeto(int id_objeto) {
	std::pair<int, int> centro_objeto = (mapa_ids_objetos.at(id_objeto))->
	obtener_centro();
	int altura_objeto = (mapa_ids_objetos.at(id_objeto))->
	obtener_altura();
	int base_objeto = (mapa_ids_objetos.at(id_objeto))->
	obtener_base();
	marcar_estado_coordenadas_alrededor(centro_objeto, altura_objeto,
	base_objeto, false);
	mapa_ids_objetos.erase(id_objeto);
	coordenadas[centro_objeto.first][centro_objeto.second].
	sacar_objeto();
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
		//fila_random = 19;
		//columna_random = 23;

		std::pair<int, int> posicion_centro(fila_random, columna_random);
		bool es_arena = verificar_terreno_alrededor(posicion_centro,
		gusano.obtener_dimesion_alto(), 
		gusano.obtener_dimesion_ancho(), "arena");
		if (es_arena) {
			objetivos = buscar_unidades_alrededor(posicion_centro, 
			gusano.obtener_dimesion_alto(),
			gusano.obtener_dimesion_ancho(), false, 
			false, -1, true);
			if (!objetivos.empty()) {
				gusano.asignar_centro(posicion_centro);
				espacio_valido = true;
				break;
			}
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

std::string Mapa::pedir_terreno_coordenada(std::pair<int, int> posicion) {
	return coordenadas[posicion.first][posicion.second].obtener_terreno();
}

unsigned int Mapa::pedir_limite_filas_baldosa() {
	return baldosas.size();
}

unsigned int Mapa::pedir_limite_columnas_baldosa() {
	return (baldosas[baldosas.size() - 1]).size();
}

std::string Mapa::pedir_terreno_baldosa(std::pair<int, int> posicion) {
	return baldosas[posicion.first][posicion.second].obtener_terreno();
}

bool Mapa::agregado_edificio(ObjetoDune* objeto) {
	std::pair<int, int> posicion_central = objeto->obtener_centro();
	bool terreno_valido;
	std::vector<ObjetoDune*> unidades_alrededor; 
	terreno_valido = verificar_terreno_alrededor(posicion_central, 
	objeto->obtener_altura(), objeto->obtener_base(), "roca");
	std::cout << "Terreno valido:" << terreno_valido << " para edificio de tipo " << objeto->pedir_id_tipo() << std::endl;
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
		std::cout << "Terreno vacio para edificio de tipo " << objeto->pedir_id_tipo() << std::endl;
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
		id_objetivo)->obtener_centro());
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
	return baldosas[posicion.first][posicion.second].esta_ocupada();
}

bool Mapa::esta_dentro_limites(std::pair<int, int> &centro){
	if (0 <= centro.first && centro.first < (int)pedir_limite_filas() &&
	 0 <= centro.second && centro.second < (int)pedir_limite_columnas()) {
		return true;
	}
	std::cout << centro.first << " centro fuera " << centro.second << std::endl;
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
std::pair<int, int> &pos_destino) {
	std::pair<int, int> centro_unidad = mapa_ids_objetos.at(id_unidad)->
	obtener_centro();
	marcar_estado_coordenadas_alrededor(centro_unidad, 
	mapa_ids_objetos.at(id_unidad)->obtener_altura(), 
	mapa_ids_objetos.at(id_unidad)->obtener_base(), false);
	coordenadas[centro_unidad.first][centro_unidad.second].sacar_objeto();
	coordenadas[pos_destino.first][pos_destino.second].poner_objeto(
	mapa_ids_objetos.at(id_unidad));
	marcar_estado_coordenadas_alrededor(pos_destino, 
	mapa_ids_objetos.at(id_unidad)->obtener_altura(), 
	mapa_ids_objetos.at(id_unidad)->obtener_base(), true);
	mapa_ids_objetos.at(id_unidad)->set_centro(pos_destino);
	/*coordenadas[camino[camino.size() / 3].first][camino[camino.size() / 3].
	second].poner_objeto(&(mapa_ids_objetos.at(id_unidad)));
	marcar_estado_coordenadas_alrededor(pos_destino, 
	objeto.obtener_altura(), objeto.obtener_base(), true);
	std::vector<std::pair<int, int>> sub_camino(&camino[0], 
	&camino[camino.size() / 3]);
	return sub_camino;*/
}

std::list<std::pair<int, int>> Mapa::obtener_camino(std::pair<int, int> inicio,
std::pair<int, int> final) {
	std::pair<int, int> inicio_baldosa = conversor.de_pixel_a_baldosa(inicio);
	std::pair<int, int> final_baldosa = conversor.de_pixel_a_baldosa(final);

#ifdef NACHO 
    std::cout << "Quiero ir de  " << inicio_baldosa.first << " " << inicio_baldosa.second << std::endl;

    std::cout << "Hacia  " << final_baldosa.first << " " << final_baldosa.second << std::endl;
#endif

	std::list<std::pair<int, int>> lista_camino = buscador_mejor_camino.buscar_mejor_camino(*this, inicio_baldosa, final_baldosa);

#ifdef NACHO 
  	std::cout << "lista_camino contains:";
#endif

  	for (std::list<std::pair<int, int>>::iterator it=lista_camino.begin(); it != lista_camino.end(); ++it){
  		//obtengo diff para sacar camino en pixeles entre nodos
#ifdef NACHO
		std::cout << " inicio_baldosa " << inicio_baldosa.first << " " << inicio_baldosa.second << std::endl; 
#endif
		
  		int diff_first = it->first - inicio_baldosa.first;
  		int diff_second = it->second - inicio_baldosa.second;

  		inicio_baldosa.first = it->first;
		inicio_baldosa.second = it->second;

#ifdef NACHO 
		std::cout << " Cambio inicio para iteracion posterior" << inicio_baldosa.first << " " << inicio_baldosa.second << std::endl; 
    	std::cout << ' ' << it->first << ' ' << it->second;
#endif

    	*it = conversor.de_baldosa_a_pixel(*it);

#ifdef NACHO 
    	std::cout << " Lo transformo a " << it->first << ' ' << it->second << std::endl; 
#endif

    	int neg_sec = 0;
    	int neg_first = 0;

    	if (diff_first == -1){
    		neg_first = 1;
    	}

    	if (diff_second == -1){
    		neg_sec = 1;
    	}

    	for(int i = PIX ; i > 0 ; i--){
    		std::pair<int,int> sig(((it->first+=diff_first) + (i*neg_first)),(it->second+=diff_second) + (i*neg_sec));

#ifdef NACHO 
    		std::cout << " Nuevo first " << sig.first << " " << sig.second << std::endl; 
#endif

    		lista_camino.insert(it,sig);
	    	if (neg_first == 1){
	    		it->first-=diff_first;
	    	}

	    	if (neg_sec == 1){
				it->second-=diff_second;
	    	}
		}


  	}

	return lista_camino;
}

void Mapa::actualizar_salida_gusano(double tiempo_transcurrido) {
	int salio = gusano.actualizar_salida(tiempo_transcurrido);
	if (salio) {
		desenterrar_gusano();
		gusano.serializar_mensaje_salida();
	}
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
	return sqrt(pow(2, p2.first - p1.first) + pow(2, p2.second - p1.second));
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
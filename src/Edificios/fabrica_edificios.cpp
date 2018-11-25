#include "fabrica_edificios.h"
#include "centro_construccion.h"
#include "trampa_aire.h"
#include "refineria.h"
#include "silo.h"
#include "fabrica_ligera.h"
#include "fabrica_pesada.h"
#include "cuartel.h"
#include "palacio.h"

#define CENTRO_CONSTRUCCION 0
#define TRAMPA_AIRE 1
#define REFINERIA 2
#define SILO 3
#define FABRICA_LIGERA 4
#define FABRICA_PESADA 5
#define CUARTELATREIDES 6
#define CUARTELHARKONNEN 7
#define CUARTELORDOS 8
#define PALACIO 9

std::shared_ptr<Edificio> FabricaEdificios::crear_edificio(
int id_tipo_edificio, int id, int id_duenio, 
std::pair<int, int> centro,Config &config) {
	if(id_tipo_edificio == CENTRO_CONSTRUCCION) {
		std::shared_ptr<CentroConstruccion> centro_construccion(new 
		CentroConstruccion(id, id_duenio, centro, config));
		return centro_construccion;
	} else if (id_tipo_edificio == TRAMPA_AIRE) {
		std::shared_ptr<TrampaAire> trampa_aire(new 
		TrampaAire(id, id_duenio, centro, config));
		return trampa_aire;
	} else if (id_tipo_edificio == REFINERIA) {
		std::shared_ptr<Refineria> refineria(new 
		Refineria(id, id_duenio, centro, config));
		return refineria;
	} else if (id_tipo_edificio == SILO) {
		std::shared_ptr<Silo> silo(new 
		Silo(id, id_duenio, centro, config));
		return silo;
	} else if (id_tipo_edificio == FABRICA_LIGERA) {
		std::shared_ptr<FabricaLigera> fabrica_ligera(new 
		FabricaLigera(id, id_duenio, centro, config));
		return fabrica_ligera;
	} else if (id_tipo_edificio == FABRICA_PESADA) {
		std::shared_ptr<FabricaPesada> fabrica_pesada(new 
		FabricaPesada(id, id_duenio, centro, config));
		return fabrica_pesada;
	} else if (id_tipo_edificio == CUARTELATREIDES || id_tipo_edificio == CUARTELHARKONNEN || id_tipo_edificio == CUARTELORDOS) {
		std::shared_ptr<Cuartel> cuartel(new 
		Cuartel(id, id_duenio, centro, config,id_tipo_edificio));
		return cuartel;
	} else {
		std::shared_ptr<Palacio> palacio(new 
		Palacio(id, id_duenio, centro, config));
		return palacio;
	}
}
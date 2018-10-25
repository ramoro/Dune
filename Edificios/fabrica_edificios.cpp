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
#define CUARTEL 6
#define PALACIO 7

Edificio&& FabricaEdificios::crear_edificio(int id_tipo_edificio) {
	if(id_tipo_edificio == CENTRO_CONSTRUCCION) {
		CentroConstruccion centro_construccion;
		return std::move(centro_construccion);
	} else if (id_tipo_edificio == TRAMPA_AIRE) {
		TrampaAire trampa_aire;
		return std::move(trampa_aire);
	} else if (id_tipo_edificio == REFINERIA) {
		Refineria refineria;
		return std::move(refineria);
	} else if (id_tipo_edificio == SILO) {
		Silo silo;
		return std::move(silo);
	} else if (id_tipo_edificio == FABRICA_LIGERA) {
		FabricaLigera fabrica_ligera;
		return std::move(fabrica_ligera);
	} else if (id_tipo_edificio == FABRICA_PESADA) {
		FabricaPesada fabrica_pesada;
		return std::move(fabrica_pesada);
	} else if (id_tipo_edificio == CUARTEL) {
		Cuartel cuartel;
		return std::move(cuartel);
	} else {
		Palacio palacio;
		return std::move(palacio);
	}
}
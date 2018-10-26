#include "fabrica_unidades_movibles.h"
#include "infanteria_ligera.h"
#include "infanteria_pesada.h"
#include "fremen.h"
#include "sardaukar.h"
#include "trike.h"
#include "raider.h"
#include "tanque.h"
#include "tanque_sonico.h"
#include "desviador.h"
#include "devastador.h"
#include "cosechadora.h"

#define INFANTERIA_LIGERA 0
#define INFANTERIA_PESADA 1
#define FREMEN 2
#define SARDAUKAR 3
#define TRIKE 4
#define RAIDER 5
#define TANQUE 6
#define TANQUE_SONICO 7
#define DESVIADOR 8
#define DEVASTADOR 9
#define COSECHADORA 10

UnidadMovible&& FabricaUnidadesMovibles::crear_unidad_movible
(int id_tipo_unidad_movible) {
	if(id_tipo_unidad_movible == INFANTERIA_LIGERA) {
		InfanteriaLigera infanteria_ligera;
		return std::move(infanteria_ligera);
	} else if (id_tipo_unidad_movible == INFANTERIA_PESADA) {
		InfanteriaPesada infanteria_pesada;
		return std::move(infanteria_pesada);
	} else if (id_tipo_unidad_movible == FREMEN) {
		Fremen fremen;
		return std::move(fremen);
	} else if (id_tipo_unidad_movible == SARDAUKAR) {
		Sardaukar sardaukar;
		return std::move(sardaukar);
	} else if (id_tipo_unidad_movible == TRIKE) {
		Trike trike;
		return std::move(trike);
	} else if (id_tipo_unidad_movible == RAIDER) {
		Raider raider;
		return std::move(raider);
	} else if (id_tipo_unidad_movible == TANQUE) {
		Tanque tanque;
		return std::move(tanque);
	} else if (id_tipo_unidad_movible == TANQUE_SONICO) {
		TanqueSonico tanque_sonico;
		return std::move(tanque_sonico);
	} else if (id_tipo_unidad_movible == DESVIADOR) {
		Desviador desviador;
		return std::move(desviador);
	} else if (id_tipo_unidad_movible == DEVASTADOR) {
		Devastador devastador;
		return std::move(devastador);
	} else {
		Cosechadora cosechadora;
		return std::move(cosechadora);
	}
}
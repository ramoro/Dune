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

#define INFANTERIA_LIGERA 10
#define INFANTERIA_PESADA 11
#define FREMEN 12
#define SARDAUKAR 13
#define TRIKE 14
#define RAIDER 15
#define TANQUE 16
#define TANQUE_SONICO 17
#define DESVIADOR 18
#define DEVASTADOR 19
#define COSECHADORA 20

std::shared_ptr<UnidadMovible> FabricaUnidadesMovibles::
crear_unidad_movible(int id_tipo_unidad_movible, int id, 
int id_duenio, std::pair<int, int> centro, Root &root) {
	if(id_tipo_unidad_movible == INFANTERIA_LIGERA) {
		std::shared_ptr<InfanteriaLigera> infanteria_ligera(
		new InfanteriaLigera(id, id_duenio, centro, root));
		return infanteria_ligera;
	} else if (id_tipo_unidad_movible == INFANTERIA_PESADA) {
		std::shared_ptr<InfanteriaPesada> infanteria_pesada(
		new InfanteriaPesada(id, id_duenio, centro, root));
		return infanteria_pesada;
	} else if (id_tipo_unidad_movible == FREMEN) {
		std::shared_ptr<Fremen> fremen(
		new Fremen(id, id_duenio, centro, root));
		return fremen;
	} else if (id_tipo_unidad_movible == SARDAUKAR) {
		std::shared_ptr<Sardaukar> sardaukar(new 
		Sardaukar(id, id_duenio, centro, root));
		return sardaukar;
	} else if (id_tipo_unidad_movible == TRIKE) {
		std::shared_ptr<Trike> trike(
		new Trike(id, id_duenio, centro, root));
		return trike;
	} else if (id_tipo_unidad_movible == RAIDER) {
		std::shared_ptr<Raider> raider(
		new Raider(id, id_duenio, centro, root));
		return raider;
	} else if (id_tipo_unidad_movible == TANQUE) {
		std::shared_ptr<Tanque> tanque(
		new Tanque(id, id_duenio, centro, root));
		return tanque;
	} else if (id_tipo_unidad_movible == TANQUE_SONICO) {
		std::shared_ptr<TanqueSonico> tanque_sonico(
		new TanqueSonico(id, id_duenio, centro, root));
		return tanque_sonico;
	} else if (id_tipo_unidad_movible == DESVIADOR) {
		std::shared_ptr<Desviador> desviador(
		new Desviador(id, id_duenio, centro, root));
		return desviador;
	} else if (id_tipo_unidad_movible == DEVASTADOR) {
		std::shared_ptr<Devastador> devastador(
		new Devastador(id, id_duenio, centro, root));
		return devastador;
	} else {
		std::shared_ptr<Cosechadora> cosechadora(
		new Cosechadora(id, id_duenio, centro, root));
		return cosechadora;
	}
}
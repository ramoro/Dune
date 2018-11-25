#include "estado.h"
#include "movimiento.h"
#include "movimiento_para_atacar.h"
#include "ataque.h"
#include "muerte.h"
#include "inactividad.h"
#include "movimiento_para_depositar.h"

std::shared_ptr<Estado> Estado::actualizar(UnidadMovible *unidad, 
Mapa &mapa, int tiempo_transcurrido) {
	return NULL;
}

std::shared_ptr<Estado> Estado::cambiar_a_movimiento() {
	std::shared_ptr<Movimiento> movimiento(new Movimiento());
	return movimiento;
}

std::shared_ptr<Estado> Estado::cambiar_a_movimiento_para_atacar(
std::shared_ptr<ObjetoDune> objetivo) {
	std::shared_ptr<MovimientoParaAtacar> movimiento_ataque(new 
	MovimientoParaAtacar(objetivo));
	return movimiento_ataque;
}

std::shared_ptr<Estado> Estado::cambiar_a_ataque(
std::shared_ptr<ObjetoDune> objetivo) {
	std::shared_ptr<Ataque> ataque(new Ataque(objetivo));
	return ataque;
}

std::shared_ptr<Estado> Estado::cambiar_a_muerte() {
	std::shared_ptr<Muerte> muerte(new Muerte());
	return muerte;
}

std::shared_ptr<Estado> Estado::cambiar_a_inactividad() {
	std::shared_ptr<Inactividad> inactividad(new Inactividad());
	return inactividad;
}

std::shared_ptr<Estado> Estado::cambiar_a_movimiento_para_depositar(
Refineria* objetivo, std::shared_ptr<ObjetoDune> terreno) {
	std::shared_ptr<MovimientoParaDepositar> movimiento_deposito(new
	MovimientoParaDepositar(objetivo, terreno));
	return movimiento_deposito;
}

std::string Estado::pedir_nombre() {
	return nombre;
}

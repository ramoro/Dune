#include "tanque_sonico.h"
#include "../Armas/onda_sonido.h"

#define ID_TANQUE_SONICO 7 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
TanqueSonico::TanqueSonico(int id, int id_duenio, std::pair<int, int> centro) : 
	UnidadMovible(4, 12, 2, 300, 300, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_TANQUE_SONICO;
		OndaSonido arma_ondas_sonidos;
		armas.push_back(OndaSonido(arma_ondas_sonidos));
	}
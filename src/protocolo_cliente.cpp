#include "protocolo_cliente.h"

ProtocoloCliente::ProtocoloCliente(Socket skt_clt) : 
socket_cliente(std::move(skt_clt)) {
  this->jugando = false;
}

void ProtocoloCliente::agregar_colas(ColaBloqueante *cola_env,
ColaBloqueante *cola_rec) {
	this->cola_envio = cola_env;
	this->cola_recepcion = cola_rec;
}
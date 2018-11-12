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

void ProtocoloCliente::inicializar() {
	this->jugando = true;
  	this->t_envios = std::thread(&ProtocoloCliente::enviar_mensajes, this);
	this->t_recibos = std::thread(&ProtocoloCliente::recibir_mensajes, this);
}

void ProtocoloCliente::enviar_mensajes() {
	while (this->jugando) {
		std::string mensaje = this->cola_envio->pop();
		/* ver si perdio cliente
		*/
		/*ver si gano tambien*/
		this->socket_cliente.send_int(mensaje.size());
		this->socket_cliente.send_string(mensaje, mensaje.size());
	}
}

void ProtocoloCliente::recibir_mensajes() {
	while (this->jugando) {
		int tam_msje = this->socket_cliente.recv_int();
		std::string mensaje; 
		this->socket_cliente.recv_string(tam_msje, mensaje);
		this->cola_recepcion->push(mensaje);
	}
}

void ProtocoloCliente::finalizar() {
	this->jugando = false;
}

ProtocoloCliente::~ProtocoloCliente() {
	this->t_envios.join();
	this->t_recibos.join();
}
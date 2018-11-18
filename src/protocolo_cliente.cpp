#include "protocolo_cliente.h"
#include "socket_error.h"
#include <iostream>

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
	try {
		while (this->jugando) {
			std::string mensaje = this->cola_envio->pop();
			/* ver si perdio cliente
			*/
			/*ver si gano tambien*/
			this->socket_cliente.send_int(mensaje.size());
			this->socket_cliente.send_string(mensaje);
		}
	} catch (std::exception &e){
		std::cerr << e.what() << " En ProtocoloCliente::enviar_mensajes" << std::endl;
	}
}

void ProtocoloCliente::recibir_mensajes() {
	try {
		while (this->jugando) {
			int tam_msje = this->socket_cliente.recv_int();
			std::string mensaje; 
			this->socket_cliente.recv_string(tam_msje, mensaje);
			this->cola_recepcion->push(mensaje);
		}
	} catch(SocketError &e){
		if (this->jugando) {
			std::cerr << e.what() << " En ProtocoloCliente::recibir_mensajes" << std::endl;	
		}
	} catch (std::exception &e){
		std::cerr << e.what() << " En ProtocoloCliente::recibir_mensajes" << std::endl;
	} catch (...) {
		std::cout << "Error desconocido en ProtocoloCliente::recibir_mensajes" << std::endl;
	}
}

void ProtocoloCliente::finalizar() {
	this->jugando = false;
	this->t_envios.join();
	this->t_recibos.join();
}
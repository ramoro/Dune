#include "protocolo_cliente.h"
#include "socket_error.h"
#include "mensaje_protocolo.h"
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
			MensajeProtocolo mensaje = this->cola_envio->pop();
			/* ver si perdio cliente
			*/
			/*ver si gano tambien*/
			unsigned char accion = mensaje.pedir_accion();
			this->socket_cliente.send_msj(&accion, 1);
			std::vector<int> parametros = mensaje.pedir_parametros();
			for (std::vector<int>::iterator it = parametros.begin(); 
			it != parametros.end(); ++it) {
				this->socket_cliente.send_int(*it);
			}
		}
	} catch (std::exception &e){
		std::cerr << e.what() << " En ProtocoloCliente::enviar_mensajes" << std::endl;
	}
}

void ProtocoloCliente::recibir_mensajes() {
	try {
		while (this->jugando) {
			MensajeProtocolo mensaje;
			unsigned char accion;
			this->socket_cliente.recv_msj(&accion, 1);
			mensaje.asignar_accion(accion);
			int cantidad_ints_a_recibir;
			if (accion == 'm' || accion == 'u') {
				cantidad_ints_a_recibir = 3;
			} else if (accion == 'a') {
				cantidad_ints_a_recibir = 2;
			} else if (accion == 'e') {
				cantidad_ints_a_recibir = 4;
			}

			for (int i = 0; i < cantidad_ints_a_recibir; ++i) {
				mensaje.agregar_parametro(this->socket_cliente.recv_int());
			}
			
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
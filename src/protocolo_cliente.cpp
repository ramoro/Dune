#include "protocolo_cliente.h"
#include "socket_error.h"
#include "mensaje_protocolo.h"
#include "cola_cerrada_error.h"
#include <iostream>
#include <list>

ProtocoloCliente::ProtocoloCliente(){}

ProtocoloCliente::ProtocoloCliente(Socket skt_clt) : 
socket_cliente(std::move(skt_clt)) {
  this->jugando = false;
}

void ProtocoloCliente::agregar_colas(std::shared_ptr<ColaBloqueante> cola_env,
ColaSegura *cola_rec) {
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
			//std::cout << "en envio mensaje" << std::endl;
			MensajeProtocolo mensaje = this->cola_envio->pop();
			/* ver si perdio cliente
			*/
			/*ver si gano tambien*/
			unsigned char accion = mensaje.pedir_accion();
			std::cout << "Accion a enviar en protocolo cliente por socket: " << accion << " " << "con parametros:"<<std::endl;
			this->socket_cliente.send_msj(&accion, 1);
			std::vector<int> parametros = mensaje.pedir_parametros();
			for (std::vector<int>::iterator it = parametros.begin(); 
			it != parametros.end(); ++it) {
				std::cout << *it << std::endl;
				this->socket_cliente.send_int(*it);
			}
		}
	} catch(SocketError &e){
		if (this->jugando) {
			std::cerr << e.what() << " En ProtocoloCliente::enviar_mensajes" << std::endl;	
		}
	} catch (ColaCerradaError &e) {
		std::cerr << e.what() << "ClienteDesconectado" << std::endl;
	} catch (std::exception &e){
		std::cerr << e.what() << " En ProtocoloCliente::enviar_mensajes" << std::endl;
	} catch (...) {
		std::cout << "Error desconocido en ProtocoloCliente::enviar_mensajes" << std::endl;
	}
}

void ProtocoloCliente::recibir_mensajes() {
	try {
		/*MensajeProtocolo mensaje1;
		mensaje1.asignar_accion('e');
		mensaje1.agregar_parametro(0);
		mensaje1.agregar_parametro(6);
		mensaje1.agregar_parametro(15);
		mensaje1.agregar_parametro(7);
		MensajeProtocolo mensaje2;
		mensaje2.asignar_accion('e');
		mensaje2.agregar_parametro(1);
		mensaje2.agregar_parametro(6);
		mensaje2.agregar_parametro(5);
		mensaje2.agregar_parametro(6);

		MensajeProtocolo mensaje3;
		mensaje3.asignar_accion('u');
		mensaje3.agregar_parametro(11);
		mensaje3.agregar_parametro(366);
		mensaje3.agregar_parametro(0);

		MensajeProtocolo mensaje4;
		mensaje4.asignar_accion('u');
		mensaje4.agregar_parametro(11);
		mensaje4.agregar_parametro(367);
		mensaje4.agregar_parametro(1);
		std::list<MensajeProtocolo> list_mensajes;
		list_mensajes.emplace_back(mensaje1);
		list_mensajes.emplace_back(mensaje2);
		list_mensajes.emplace_back(mensaje3);
		list_mensajes.emplace_back(mensaje4);

		MensajeProtocolo mensaje5;
		mensaje5.asignar_accion('s');
		list_mensajes.emplace_back(mensaje5);*/
		
 		while (this->jugando) {
			MensajeProtocolo mensaje;
			unsigned char accion;
			this->socket_cliente.recv_msj(&accion, 1);
			std::cout << accion << std::endl;
			mensaje.asignar_accion(accion);
			int cantidad_ints_a_recibir = 0;
			if (accion == 'm' || accion == 'u') {
				cantidad_ints_a_recibir = 3;
			} else if (accion == 'a') {
				cantidad_ints_a_recibir = 2;
			} else if (accion == 'e') {
				cantidad_ints_a_recibir = 4;
			} else if (accion == 'v' || accion == 's') {
				cantidad_ints_a_recibir = 1;
			}

			for (int i = 0; i < cantidad_ints_a_recibir; ++i) {
				mensaje.agregar_parametro(this->socket_cliente.recv_int());
			}
			/*if (!list_mensajes.empty()) {
				MensajeProtocolo msj = list_mensajes.front();
				list_mensajes.pop_front();
				this->cola_recepcion->push(msj);
			}*/
			//std::cout << accion << std::endl;

			this->cola_recepcion->push(mensaje);

			//std::cout << accion << std::endl;
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
	std::cout<< "entro a finalizar" << std::endl;
	this->t_envios.join();
	std::cout << "joineo cola envios" << std::endl;
	this->t_recibos.join();
	std::cout << "joineo cola recibo" << std::endl;
}
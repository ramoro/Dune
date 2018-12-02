#include "protocolo_cliente.h"
#include "socket_error.h"
#include "mensaje_protocolo.h"
#include "cola_cerrada_error.h"
#include <iostream>
#include <list>

//ProtocoloCliente::ProtocoloCliente() : organizador() {}

ProtocoloCliente::ProtocoloCliente(Socket skt_clt, int id,
OrganizadorJuegos &organizador) : 
socket_cliente(std::move(skt_clt)), id(id), organizador(organizador) {
  this->jugando = false;
  this->esperando_en_sala = false;
  this->id_juego_asociado = -1;
}

void ProtocoloCliente::agregar_colas(std::shared_ptr<ColaBloqueante> cola_env,
ColaSegura *cola_rec) {
	this->cola_envio = cola_env;
	this->cola_recepcion = cola_rec;
}

void ProtocoloCliente::inicializar() {
  	this->t_envios = std::thread(&ProtocoloCliente::enviar_mensajes, this);
}

void ProtocoloCliente::enviar_mensajes() {
	try {
		while (this->jugando) {
			//// << "en envio mensaje" << std::endl;
			MensajeProtocolo mensaje = this->cola_envio->pop();
			/* ver si perdio cliente
			*/
			/*ver si gano tambien*/
			unsigned char accion = mensaje.pedir_accion();
			//std::cout << "Accion a enviar en protocolo cliente por socket: " << accion << " " << "con parametros:"<<std::endl;
			this->socket_cliente.send_msj(&accion, 1);
			std::vector<int> parametros = mensaje.pedir_parametros();
			for (std::vector<int>::iterator it = parametros.begin(); 
			it != parametros.end(); ++it) {
				// << *it << std::endl;
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
		// << "Error desconocido en ProtocoloCliente::enviar_mensajes" << std::endl;
	}
}

void ProtocoloCliente::iniciar_protocolo() {
	try {
		while (this->esperando_en_sala) {
			// << "esperando en sala" << std::endl;
			unsigned char accion;
			if(!this->esperando_en_sala) break;
			this->socket_cliente.recv_msj(&accion, 1);
			std::vector<int> parametros_recibidos;
			std::cout << "accion en esperando sala " << accion << " de cliente " << this->id << std::endl;
			if (accion == 'p') {
				std::string nombre("yeahh");
				accion = 'm';
				this->socket_cliente.send_msj(&accion, 1);
				this->socket_cliente.send_int(nombre.size());
				this->socket_cliente.send_string(nombre);
				this->socket_cliente.send_int(5);
				accion = 'f';
				this->socket_cliente.send_msj(&accion, 1);
				// << "se enviaron mapas" << std::endl;
				
				//mandar mapas
				//mandar finalizacion envio mapas
				//recibo m con id, max_cant_jugadores, e id partida?
			} else if (accion == 'm') {
				this->socket_cliente.recv_int(); //recibo id mapa elegido
				this->socket_cliente.recv_int(); //recibo maxs jugadores
				id_juego_asociado = organizador.crear_juego();
				accion = 'o';
				this->socket_cliente.send_msj(&accion, 1);
			} else if (accion == 'n') {
				unsigned char acc = 'm';
				std::string nombre_mapa("yeahh");
				this->socket_cliente.send_msj(&acc, 1);
				this->socket_cliente.send_int(nombre_mapa.size());
				this->socket_cliente.send_string(nombre_mapa);
				this->socket_cliente.send_int(0);
				accion = 'f';
				this->socket_cliente.send_msj(&accion, 1);
				//mando lista de partidas
			} else if (accion == 'j') {
				std::cout << "entro a join " << std::endl;
				id_juego_asociado = this->socket_cliente.recv_int();
				std::cout << "recibio id partida" << std::endl;
				accion = 'o';
				this->socket_cliente.send_msj(&accion, 1);
				//recibo id mapa,
			} else if (accion == 'i') {
				//parametros_recibidos = recibir_ints(1);
				// << "entro a iniciar juego en inciar_protocolo" << std::endl;
				organizador.iniciar_juego(0);
				int casa = this->socket_cliente.recv_int();//recibo el id de la casa
				std::cout << "recibio casa owner : " << casa <<  std::endl;
				break;
			} else if(accion == 'l') {
				int casa = this->socket_cliente.recv_int();//recibo el id de la casa
				std::cout << "recibio casa no owner: " << casa <<  std::endl;

				break;
			}
		}

 		while (this->jugando) {
			MensajeProtocolo mensaje;
			unsigned char accion;
			this->socket_cliente.recv_msj(&accion, 1);
			std::cout << "entro en jugando cliente de id "<< this->id << std::endl;
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
			//// << accion << std::endl;

			this->cola_recepcion->push(mensaje);

		}
	} catch(SocketError &e){
		if (this->jugando || this->esperando_en_sala) {
			std::cerr << e.what() << " En ProtocoloCliente::recibir_mensajes" << std::endl;	
		}
	} catch (std::exception &e){
		std::cerr << e.what() << " En ProtocoloCliente::recibir_mensajes" << std::endl;
	} catch (...) {
		// << "Error desconocido en ProtocoloCliente::recibir_mensajes" << std::endl;
	}
}

std::vector<int> ProtocoloCliente::recibir_ints(int cantidad_ints_a_recibir) {
	std::vector<int> parametros_recibidos;
	for (int i = 0; i < cantidad_ints_a_recibir; ++i) {
		parametros_recibidos.push_back(this->socket_cliente.recv_int());
	}
	return parametros_recibidos;
}

void ProtocoloCliente::finalizar() {
	this->jugando = false;
	//<< "entro a finalizar" << std::endl;
	this->t_envios.join();
	// << "joineo cola envios" << std::endl;
	this->t_recibos.join();
	// << "joineo cola recibo" << std::endl;
}

int ProtocoloCliente::pedir_id() {
	return id;
}

int ProtocoloCliente::pedir_id_juego_asociado() {
	return id_juego_asociado;
}

void ProtocoloCliente::iniciar_protocolo_en_salas() {
	this->esperando_en_sala = true;
	this->t_recibos = std::thread(&ProtocoloCliente::iniciar_protocolo, this);
}

void ProtocoloCliente::cambiar_a_modo_juego() {
	this->esperando_en_sala = false;
	this->jugando = true;

	unsigned char accion = 'r';
	this->socket_cliente.send_msj(&accion, 1);
}

void ProtocoloCliente::mensaje_casa() {
	//this->socket_cliente.recv_msj(&accion, 1);// recibo t de team
	int casa = this->socket_cliente.recv_int();//recibo el id de la casa
	std::cout << "recibio casa: " << casa <<  std::endl;

	//this->socket_cliente.send_int(0);
	//this->socket_cliente.send_int(0);
	//this->socket_cliente.send_int(5000);
	//this->socket_cliente.send_int(3000);
	// << "mando caracs mapa" << std::endl;
}
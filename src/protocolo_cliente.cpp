#include "protocolo_cliente.h"
#include "socket_error.h"
#include "mensaje_protocolo.h"
#include "cola_cerrada_error.h"
#include "organizador_juegos.h"
#include <iostream>
#include <list>
#include <fstream>

#define CODIGO_ASIGNAR_CASA 'h'
#define CODIGO_PETICION_LISTA_MAPAS 'p'
#define CODIGO_FIN_LISTA 'f'
#define CODIGO_OKEY 'o'
#define CODIGO_CREACION_SALA 'm'
#define CODIGO_LISTA_SALAS 'n'
#define CODIGO_UNION_SALA 'j'
#define CODIGO_INICIO_JUEGO 'i'
#define CODIGO_ASIGNAR_CASA_INVITADO 'l'
#define CODIGO_GUARDAR_MAPA 'g'
#define CODIGO_SALIR 's'
#define CODIGO_MOVIMIENTO 'm'
#define CODIGO_CREACION_UNIDAD 'u'
#define CODIGO_ATACAR 'a'
#define CODIGO_CREACION_EDIFICIO 'e'
#define CODIGO_VENDER 'v'
#define CODIGO_ENVIO_MAPA_O_SALA 'm'
#define CODIGO_JUEGO_LISTO 'r'
#define CODIGO_AVISO_SALA_ELIMINADA 'd'

ProtocoloCliente::ProtocoloCliente(Socket skt_clt, int id,
OrganizadorJuegos &organizador) : 
socket_cliente(std::move(skt_clt)), id(id), organizador(organizador) {
  this->jugando = false;
  this->esperando_en_sala = false;
  this->id_sala_asociada = -1;
  this->casa = -1;
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

			MensajeProtocolo mensaje = this->cola_envio->pop();
			unsigned char accion = mensaje.pedir_accion();

			this->socket_cliente.send_msj(&accion, 1);
			std::vector<int> parametros = mensaje.pedir_parametros();
			for (std::vector<int>::iterator it = parametros.begin(); 
			it != parametros.end(); ++it) {

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

void ProtocoloCliente::iniciar_protocolo() {
	try {
		while (this->esperando_en_sala) {
			unsigned char accion;
			if(!this->esperando_en_sala) break;
			this->socket_cliente.recv_msj(&accion, 1);
			std::vector<int> parametros_recibidos;

			if (accion == CODIGO_PETICION_LISTA_MAPAS) {
				organizador.recorrer_mapas_para_enviar(this->id);
				accion = CODIGO_FIN_LISTA;
				this->socket_cliente.send_msj(&accion, 1);
			
			} else if (accion == CODIGO_CREACION_SALA) {
				int id_mapa = this->socket_cliente.recv_int();
				int max_jugadores = this->socket_cliente.recv_int();
				id_sala_asociada = organizador.crear_sala(id_mapa, 
				max_jugadores, this->id);
				accion = CODIGO_OKEY;
				this->socket_cliente.send_msj(&accion, 1);
			} else if (accion == CODIGO_LISTA_SALAS) {
				organizador.recorrer_salas_para_enviar(this->id);
				accion = CODIGO_FIN_LISTA;
				this->socket_cliente.send_msj(&accion, 1);
			} else if (accion == CODIGO_UNION_SALA) {
		
				id_sala_asociada = this->socket_cliente.recv_int();
				
				organizador.agregar_cliente_a_sala(id_sala_asociada);
				accion = CODIGO_OKEY;
				this->socket_cliente.send_msj(&accion, 1);
			} else if (accion == CODIGO_INICIO_JUEGO) {
				organizador.iniciar_juego(id_sala_asociada);
				this->casa = this->socket_cliente.recv_int();//recibo el id de la casa
				
				break;
			} else if(accion == CODIGO_ASIGNAR_CASA_INVITADO) {
				this->casa = this->socket_cliente.recv_int();//recibo el id de la casa
				
				break;
			} else if (accion == CODIGO_GUARDAR_MAPA) {
				guardar_mapa();
				continue;
			} else if (accion == CODIGO_SALIR) {
				this->jugando = false;
				organizador.desconectar_cliente(this->id);
				break;
			}
		}

		if (this->jugando) {
			MensajeProtocolo msg;
 			msg.asignar_accion(CODIGO_ASIGNAR_CASA);
 			msg.agregar_parametro(casa);
 			msg.agregar_parametro(this->id);
 			this->cola_recepcion->push(msg);
 		}

 		while (this->jugando) {
			MensajeProtocolo mensaje;
			unsigned char accion;
			this->socket_cliente.recv_msj(&accion, 1);

			mensaje.asignar_accion(accion);
			int cantidad_ints_a_recibir = 0;
			if (accion == CODIGO_MOVIMIENTO || accion == CODIGO_CREACION_UNIDAD) {
				cantidad_ints_a_recibir = 3;
			} else if (accion ==  CODIGO_ATACAR) {
				cantidad_ints_a_recibir = 2;
			} else if (accion == CODIGO_CREACION_EDIFICIO) {
				cantidad_ints_a_recibir = 4;
			} else if (accion == CODIGO_VENDER || accion == CODIGO_SALIR) {
				cantidad_ints_a_recibir = 1;
			}

			for (int i = 0; i < cantidad_ints_a_recibir; ++i) {
				mensaje.agregar_parametro(this->socket_cliente.recv_int());
			}

			this->cola_recepcion->push(mensaje);

		}
	} catch(SocketError &e){
		if (this->jugando || this->esperando_en_sala) {
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

void ProtocoloCliente::guardar_mapa() {
	std::string nombre_mapa = "mapa_" + 
	std::to_string(id_sala_asociada) + '-' + std::to_string(id) +".json";
	std::ofstream archivo_a_escribir;
	archivo_a_escribir.open("../mapas/" + nombre_mapa);
	int cant_lineas = this->socket_cliente.recv_int();
	for (int i = 0 ; i < cant_lineas ; i++){
		int linea_size = this->socket_cliente.recv_int();		
		std::string linea;
		this->socket_cliente.recv_string(linea_size, linea);	
		archivo_a_escribir << linea << std::endl;
	}
	archivo_a_escribir.close();
}

int ProtocoloCliente::pedir_id() {
	return id;
}

int ProtocoloCliente::pedir_id_sala_asociada() {
	return id_sala_asociada;
}

void ProtocoloCliente::iniciar_protocolo_en_salas() {
	this->esperando_en_sala = true;
	this->t_recibos = std::thread(&ProtocoloCliente::iniciar_protocolo, this);
}

void ProtocoloCliente::cambiar_a_modo_juego() {
	this->esperando_en_sala = false;
	this->jugando = true;

	unsigned char accion = CODIGO_JUEGO_LISTO;
	this->socket_cliente.send_msj(&accion, 1);
}

void ProtocoloCliente::enviar_mapa_o_sala(std::string nombre, int id) {
	unsigned char accion = CODIGO_ENVIO_MAPA_O_SALA;
	this->socket_cliente.send_msj(&accion, 1);
	this->socket_cliente.send_int(nombre.size());
	this->socket_cliente.send_string(nombre);
	this->socket_cliente.send_int(id);
}

int ProtocoloCliente::pedir_casa() {
	return this->casa;
}

void ProtocoloCliente::joinear_hilo_espera_a_jugar() {
	this->esperando_en_sala = false;
	this->t_recibos.join();

}

bool ProtocoloCliente::esta_esperando_para_jugar() {
	return this->esperando_en_sala;
}

void ProtocoloCliente::enviar_sala_eliminada() {
	id_sala_asociada = -1;
	unsigned char accion = CODIGO_AVISO_SALA_ELIMINADA;
	this->socket_cliente.send_msj(&accion, 1);
}
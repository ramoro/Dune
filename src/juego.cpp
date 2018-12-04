#include "juego.h"
#include "conversor.h"
#include "protocolo_cliente.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std::chrono;

#define TAM_COLA 600
#define SEGUNDOS_POR_FRAME 1.f/20
#define MILISEGUNDOS_POR_FRAME (1.f/20 * 1000)
#define CODIGO_DIMESIONES_MAPA 'h'
#define CODIGO_JUEGO_LISTO 'x'
#define CODIGO_CREACION_EDIFICIO 'e'
#define CODIGO_CREACION_UNIDAD 'u'
#define CODIGO_MOVIMIENTO 'm'
#define CODIGO_ATAQUE 'a'
#define CODIGO_VENTA 'v'
#define CODIGO_ASIGNAR_CASA 'h'
#define CODIGO_SALIR 's'

Juego::Juego(std::shared_ptr<Partida> part): 
cola_recepcion(TAM_COLA), partida(part) {}

//aca nose si pasar la cola xq la uso antes o no usarla y q se creen aca
void Juego::agregar_jugador(std::shared_ptr<ProtocoloCliente> cliente_jugador) {
  int id_cliente = cliente_jugador->pedir_id();
  // << "id_cliente " << id_cliente << " siendo agregado al juego"<< std::endl;
  this->clientes.emplace(
  std::pair<int, std::shared_ptr<ProtocoloCliente>>(id_cliente,
  cliente_jugador));
  std::shared_ptr<ColaBloqueante> cola_bloq(new ColaBloqueante(TAM_COLA));
  this->colas_envio_clientes.emplace(
  std::pair<int, std::shared_ptr<ColaBloqueante>>(id_cliente, cola_bloq));
  cliente_jugador->agregar_colas(cola_bloq, &(this->cola_recepcion));
  partida->agregar_jugador(id_cliente, this->colas_envio_clientes);
}


void Juego::hacer_ajustes_iniciales() {
  for (std::map<int, std::shared_ptr<ProtocoloCliente>>::iterator 
  it = this->clientes.begin(); it != this->clientes.end(); ++it) {
    (it->second)->inicializar();
  }

  mutex.lock();
  this->partida->terreno_inicial(this->colas_envio_clientes);
  this->partida->actualizar_modelo(0, this->colas_envio_clientes);
  mutex.unlock();
  MensajeProtocolo mensaje;
  mensaje.asignar_accion(CODIGO_DIMESIONES_MAPA);
  mensaje.agregar_parametro(0);
  mensaje.agregar_parametro(0);
  mensaje.agregar_parametro(partida->obtener_limite_mapa_fila());
  mensaje.agregar_parametro(partida->obtener_limite_mapa_columna());
  MensajeProtocolo msj;
  msj.asignar_accion(CODIGO_JUEGO_LISTO);
  for (std::map<int, std::shared_ptr<ColaBloqueante>>::iterator it =
  this->colas_envio_clientes.begin(); it != 
  this->colas_envio_clientes.end(); ++it) {
    // << "Se encolo la x de inicio de juego" << std::endl;
    (it->second)->push(mensaje);
    (it->second)->push(msj);
  }
}

void Juego::run() {
  hacer_ajustes_iniciales();
  this->terminado = false;
  Conversor conversor;
  while(!this->terminado) {
    high_resolution_clock::time_point tiempo_inicial = high_resolution_clock::now();
    if (!cola_recepcion.vacia()) {
      MensajeProtocolo mensaje = cola_recepcion.pop();
      char accion = mensaje.pedir_accion();
      std::vector<int> v = mensaje.pedir_parametros();

      if (accion == CODIGO_CREACION_EDIFICIO) {
        mutex.lock();
        this->partida->agregar_edificio(v[0],std::pair<int, int> (v[2], v[3]),
        v[1], this->colas_envio_clientes);
        mutex.unlock();
      } else if (accion == CODIGO_CREACION_UNIDAD) {
        mutex.lock();
        this->partida->iniciar_entrenamiento_unidad_movible(v[0], v[1], v[2], 
        this->colas_envio_clientes);
        mutex.unlock(); 
      } else if (accion == CODIGO_MOVIMIENTO) {
        mutex.lock();
        this->partida->comenzar_movimiento_unidad(v[0],
        std::pair<int, int> (v[1], v[2]));
        mutex.unlock();
      } else if (accion == CODIGO_ATAQUE) {
        mutex.lock();
        this->partida->atacar_objeto(v[0], v[1]);
        mutex.unlock();
      } else if (accion == CODIGO_VENTA) {
        mutex.lock();
        this->partida->vender_edificio(v[0], this->colas_envio_clientes);
        mutex.unlock();
      } else if (accion == CODIGO_ASIGNAR_CASA) {
        mutex.lock();
        this->partida->asignar_casa_a_jugador(v[0], v[1]);
        mutex.unlock();
      } else if (accion == CODIGO_SALIR) {
        mutex.lock();
        this->partida->eliminar_jugador(v[0], this->colas_envio_clientes);
        mutex.unlock();
        this->colas_envio_clientes.at(v[0])->cerrar();
        this->clientes.at(v[0])->finalizar();
        this->colas_envio_clientes.erase(v[0]);
        this->clientes.erase(v[0]);
      }
    }
    if (this->clientes.empty()) {
      break;
    }

    mutex.lock();
    this->partida->actualizar_modelo(MILISEGUNDOS_POR_FRAME, this->colas_envio_clientes);
    mutex.unlock();
    high_resolution_clock::time_point tiempo_final = 
  	high_resolution_clock::now();
  	duration<int, std::milli> tiempo_transcurrido = 
  	duration_cast<duration<int>>(tiempo_final - tiempo_inicial);
  	int tiempo_sleep = MILISEGUNDOS_POR_FRAME - tiempo_transcurrido.count();

  	std::this_thread::sleep_for(std::chrono::milliseconds(tiempo_sleep));
  }
}
Juego::~Juego() {}

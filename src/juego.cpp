#include "juego.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <ratio>
#include "conversor.h"

using namespace std::chrono;

#define TAM_COLA 100
#define SEGUNDOS_POR_FRAME 1.f/40

/*Juego::Juego(Partida *partida): 
cola_recepcion(TAM_COLA), partida(partida) {
  std::cout << "Constructor juego sin socket" << std::endl;
  //this->clientes.push_back(new ProtocoloCliente());
}*/

Juego::Juego(Partida *partida): 
cola_recepcion(TAM_COLA), partida(partida) {
  //std::shared_ptr<ProtocoloCliente> cliente(new 
  //ProtocoloCliente(std::move(skt_cliente)));
  //this->clientes.push_back(cliente);
 // partida->agregar_jugador("harkonnen", this->colas_envio_clientes);
}

void Juego::agregar_jugador(Socket skt_cliente, std::string casa) {
  partida->agregar_jugador(casa, this->colas_envio_clientes);
  std::shared_ptr<ProtocoloCliente> cliente(new 
  ProtocoloCliente(std::move(skt_cliente)));
  this->clientes.push_back(cliente);
  std::shared_ptr<ColaBloqueante> cola_bloq(new ColaBloqueante(TAM_COLA));
  this->colas_envio_clientes.push_back(cola_bloq);
}


void Juego::hacer_ajustes_iniciales() {
  for (std::vector<std::shared_ptr<ProtocoloCliente>>::iterator it = 
  this->clientes.begin(); it != this->clientes.end(); ++it) {
    std::shared_ptr<ColaBloqueante> cola_bloq(new ColaBloqueante(TAM_COLA));
    this->colas_envio_clientes.push_back(cola_bloq);
    (*it)->agregar_colas(cola_bloq, &(this->cola_recepcion));
    (*it)->inicializar();
  }
  //(this->clientes[0])->agregar_colas(&(this->cola_envio), 
  //&(this->cola_recepcion));
  //(this->clientes[0])->inicializar();
  mutex.lock();
  this->partida->actualizar_modelo(SEGUNDOS_POR_FRAME, this->colas_envio_clientes);
  mutex.unlock();
  MensajeProtocolo msj;
  msj.asignar_accion('x');
  for (std::vector<std::shared_ptr<ColaBloqueante>>::iterator it = 
  this->colas_envio_clientes.begin(); it != 
  this->colas_envio_clientes.end(); ++it) {
    std::cout << "Se encolo la x de inicio de juego" << std::endl;
    (*it)->push(msj);
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
      std::cout << "Accion desencolada en juego: " << accion << std::endl;
      std::vector<int> v = mensaje.pedir_parametros();

      if (accion == 'e') {
        mutex.lock();
        this->partida->agregar_edificio(v[0],std::pair<int, int> (v[2], v[3]),
        v[1], this->colas_envio_clientes);
        mutex.unlock();
      } else if (accion == 'u') {
         std::cout << "Parametros inicio entrenamiento unidad: " << v[0] << " "<< v[1] << " "<< v[2] << std::endl;
        this->partida->iniciar_entrenamiento_unidad_movible(v[0], v[1], v[2], 
        this->colas_envio_clientes); 
      } else if (accion == 'm') {
        this->partida->comenzar_movimiento_unidad(v[0],
        std::pair<int, int> (v[1], v[2]));
      } else if (accion == 'a') {
        this->partida->atacar_objeto(v[0], v[1]);
      } else if (accion == 's') {
        std::cout << "entro a accion salida" << std::endl;
        //this->cola_recepcion.cerrar();
        for (std::vector<std::shared_ptr<ColaBloqueante>>::iterator it = 
        this->colas_envio_clientes.begin(); it != 
        this->colas_envio_clientes.end(); ++it) {
          (*it)->cerrar();
        }
        for (std::vector<std::shared_ptr<ProtocoloCliente>>::iterator it = 
        this->clientes.begin(); it != this->clientes.end(); 
        ++it) {
          (*it)->finalizar();
        } 

        break;
      }
    }
    //ver si juego termino*/
    mutex.lock();
    this->partida->actualizar_modelo(SEGUNDOS_POR_FRAME, this->colas_envio_clientes);
    mutex.unlock();
    high_resolution_clock::time_point tiempo_final = 
  	high_resolution_clock::now();
  	duration<int, std::milli> tiempo_transcurrido = 
  	duration_cast<duration<int>>(tiempo_final - tiempo_inicial);
  	int tiempo_sleep = (SEGUNDOS_POR_FRAME * 1000) - tiempo_transcurrido.count();

  	std::this_thread::sleep_for(std::chrono::milliseconds(tiempo_sleep));
  }
  std::cout << "Salio del game loop!" << std::endl;
}

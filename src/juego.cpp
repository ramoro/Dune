#include "juego.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std::chrono;

#define TAM_COLA 100
#define SEGUNDOS_POR_FRAME 1/40

Juego::Juego(Partida *partida): cola_envio(TAM_COLA), 
cola_recepcion(TAM_COLA), partida(partida) {
  std::cout << "constr" << std::endl;
  this->clientes.push_back(new ProtocoloCliente());
}

Juego::Juego(Socket skt_cliente, Partida *partida): cola_envio(TAM_COLA), 
cola_recepcion(TAM_COLA), partida(partida) {
 this->clientes.push_back(new ProtocoloCliente(std::move(skt_cliente)));
}


void Juego::hacer_ajustes_iniciales() {
  (this->clientes[0])->agregar_colas(&(this->cola_envio), 
  &(this->cola_recepcion));
  (this->clientes[0])->inicializar();
  this->partida->actualizar_modelo(SEGUNDOS_POR_FRAME, &(this->cola_envio));
  MensajeProtocolo msj;
  msj.asignar_accion('x');
  this->cola_envio.push(msj);
}

void Juego::run() {
  hacer_ajustes_iniciales();
  this->terminado = false;
  while(!this->terminado) {
    MensajeProtocolo mensaje = cola_recepcion.pop();
    char accion = mensaje.pedir_accion();
    std::cout << "accion en juego: " << accion << std::endl;
    //std::cout << mensaje << std::endl;
    //cola_envio.push(mensaje);
    std::vector<int> v = mensaje.pedir_parametros();
    if (accion == 'e') {
      //despues se pasaria la cola bloqueante de envio para agregar
      //el mensaje de si se puso o no y donde en caso de ponerse
      this->partida->agregar_edificio(v[0], std::pair<int, int> (v[2], v[3]),
      v[1], &(this->cola_envio));
    } else if (accion == 'u') {
      //aca paso la cola bloqueante y mando un si si se envio y cambio estado
      //o un no si no
      this->partida->iniciar_entrenamiento_unidad_movible(v[0], v[1], v[2], 
      &(this->cola_envio)); 
    } else if (accion == 'm') {
      this->partida->comenzar_movimiento_unidad(v[0],
      std::pair<int, int> (v[1], v[2]));
    } else if (accion == 'a') {
      this->partida->atacar_objeto(v[0], v[1]);
    } else if (accion == 's') {
        //this->clientes[0]->finalizar();

      this->cola_recepcion.cerrar();
      this->cola_envio.cerrar();
      this->clientes[0]->finalizar();

      break;
    }
  
    //ver si juego termino*/
   
    high_resolution_clock::time_point tiempo_inicial = high_resolution_clock::now();

    this->partida->actualizar_modelo(SEGUNDOS_POR_FRAME, &(this->cola_envio));
    /*MensajeProtocolo msaje;
    msaje.asignar_accion('x');
    this->cola_envio.push(std::move(msaje));

*/  	high_resolution_clock::time_point tiempo_final = 
  	high_resolution_clock::now();
  	duration<int, std::milli> tiempo_transcurrido = 
  	duration_cast<duration<int>>(tiempo_final - tiempo_inicial);
  	int tiempo_sleep = (1/40 * 1000) - tiempo_transcurrido.count();

  	std::this_thread::sleep_for(std::chrono::milliseconds(tiempo_sleep));

    //break;
  }
  std::cout << "salio!" << std::endl;
  //delete this->clientes[0];
  //this->clientes[0]->finalizar();
}

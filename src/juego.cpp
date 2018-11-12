#include "juego.h"
#include <iostream>

#define TAM_COLA 100

Juego::Juego(): cola_envio(TAM_COLA), 
cola_recepcion(TAM_COLA) {
  std::cout << "constr" << std::endl;
}

Juego::Juego(Socket skt_cliente, Partida *partida): cola_envio(TAM_COLA), 
cola_recepcion(TAM_COLA), partida(partida) {
 this->clientes.push_back(new ProtocoloCliente(std::move(skt_cliente)));
}


void Juego::hacer_ajustes_iniciales() {
  /*(this->clientes[0])->agregar_colas(&(this->cola_envio), 
  &(this->cola_recepcion));
  (this->clientes[0])->inicializar();*/

}

void Juego::run() {
  hacer_ajustes_iniciales();
  //clock_t tiempo_pasado_game_loop = 0;
  this->terminado = false;
  while(!this->terminado) {
    clock_t tiempo_inicial = clock();
    //this->partida->actualizar_modelo(tiempo_pasado_game_loop);
    //tiempo_pasado_game_loop = 40;
    /*ver si juego termino*/
    clock_t tiempo_final = clock();
    double tiempo_transcurrido = tiempo_final - tiempo_inicial;
     std::cout << tiempo_transcurrido << std::endl;
    double tiempo_sleep_segundos = (1/(40 - tiempo_transcurrido));
    std::cout << "SLEEPS" << tiempo_sleep_segundos << std::endl;
    int tiempo_sleep_ms = tiempo_sleep_segundos * 1000;
    std::cout << "SLEEP" << tiempo_sleep_ms << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(tiempo_sleep_ms));
    /*std::string mensaje = cola_recepcion.pop();
    std::cout << mensaje << std::endl;
    cola_envio.push(mensaje);
    this->clientes[0]->finalizar();
    break;*/
  }
}

#include "juego.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std::chrono;

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
  (this->clientes[0])->agregar_colas(&(this->cola_envio), 
  &(this->cola_recepcion));
  (this->clientes[0])->inicializar();

}

void Juego::split(const std::string& s, char c,
std::vector<int>& v) {
   std::string::size_type i = 0;
   std::string::size_type j = s.find(c);

   while (j != std::string::npos) {
      v.push_back(atoi((s.substr(i, j-i)).c_str()));
      i = ++j;
      j = s.find(c, j);

      if (j == std::string::npos)
        v.push_back(atoi((s.substr(i, s.length())).c_str()));
   }
}

void Juego::run() {
  //hacer_ajustes_iniciales();
  this->terminado = false;
  while(!this->terminado) {
    //std::string mensaje = cola_recepcion.pop();
    //std::cout << mensaje << std::endl;
    //cola_envio.push(mensaje);
    /*
    std::vector<int> v;
    std::string accion = comando.substr(0,1);
    std::string data = comando.substr(comando.find('|') + 1);
    split(data, '|', v);

    for (unsigned int i = 0; i < v.size(); ++i) {
      std::cout << v[i] << '\n';
    }
    if (accion == "e") {
      //despues se pasaria la cola bloqueante de envio para agregar
      //el mensaje de si se puso o no y donde en caso de ponerse
      agregar_edificio(v[0], std::pair<int, int> (v[2], v[3]),
      v[1]);
    } else if (accion == "u") {
      //aca paso la cola bloqueante y mando un si si se envio y cambio estado
      //o un no si no
      se_puede_agregar_unidad_movible(v[0], v[1]);
    } else if (accion == "m") {
      mover_unidad(v[0],std::pair<int, int> (v[1], v[2]));
    } else if (accion == "a") {
      atacar_objeto(v[0], v[1]);
    }
    this->partida->actualizar_modelo(TIEMPO_GAME_LOOP);
    //ver si juego termino*/
   
    high_resolution_clock::time_point tiempo_inicial = high_resolution_clock::now();


  	high_resolution_clock::time_point tiempo_final = 
  	high_resolution_clock::now();
  	duration<int, std::milli> tiempo_transcurrido = 
  	duration_cast<duration<int>>(tiempo_final - tiempo_inicial);
  	int tiempo_sleep = (1/40 * 1000) - tiempo_transcurrido.count();

  	std::this_thread::sleep_for(std::chrono::milliseconds(tiempo_sleep));

    break;
  }
  //this->clientes[0]->finalizar();
}

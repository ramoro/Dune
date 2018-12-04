#include "partida.h"
#include "mapa.h"
#include "buscador_mejor_camino.h"
#include <iostream>
#include "nodo.h"
#include <vector>
#include <stack>
#include <cmath>
#include <iostream>
#include "cola_bloqueante.h"
#include "server.h"
#include "juego.h"
#include "cola_bloqueante.h"
#include "organizador_juegos.h"
#include "conversor.h"
#include "socket_error.h"

#define POSICION_INHABILITADA 1
#define PARAMETROS_ESPERADOS 2
#define OK 0
#define ERROR_CANT_PARAMETROS -1
#define ERROR_EN_SOCKETS -2
#define ERROR_EN_SERVIDOR -3
#define CANT_MAX_ESCUCHA_CLIENTES 30
#define CODIGO_SALIDA "cerrar"

int main(int argc, char* argv[]) {
  if (argc != PARAMETROS_ESPERADOS) {
    return ERROR_CANT_PARAMETROS;
  }
  OrganizadorJuegos organizador;
  
  try {
    Server server(argv[1], CANT_MAX_ESCUCHA_CLIENTES, organizador);
    server.start();

    std::string mensaje_cierre;
    while (std::getline(std::cin, mensaje_cierre)){
      if (mensaje_cierre == CODIGO_SALIDA){
        server.apagar();
        break;
      }
    }
    server.join();
  } catch(SocketError &e){
      return ERROR_EN_SOCKETS; 
  } catch (...) {
    return ERROR_EN_SERVIDOR;
  }

  return OK;
}
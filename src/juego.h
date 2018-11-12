#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <vector>
#include <memory>
#include "Socket.h"
#include "cola_bloqueante.h"
#include "protocolo_cliente.h"
#include "partida.h"
#include "thread.h"

class Juego {
  /*public Thread*/
  private:
    ColaBloqueante cola_envio;
    ColaBloqueante cola_recepcion;
    Partida* partida;
    bool stopped = false;
    bool terminado = false;
    std::vector<ProtocoloCliente*> clientes;

  public:

    Juego();
    /*Constructor de la clase.*/
    Juego(Socket cliente, Partida *partida);

    //virtual 
    void run();
    //override;

    //void stop();

    /*Destructor de la clase.*/
    //virtual ~Juego();
  
  private:
    /*Prepara las colas para recibir y enviar mensajes.*/
    void hacer_ajustes_iniciales();

  };

#endif

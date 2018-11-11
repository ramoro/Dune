#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <vector>
#include "Socket.h"
#include "cola_bloqueante.h"
#include "protocolo_cliente.h"
#include "partida.h"
#include "thread.h"

class Juego: public Thread {
  private:
    Partida* partida;
    ColaBloqueante cola_envio;
    ColaBloqueante cola_recepcion;
    bool stopped = false;
    bool ran = false;
    ProtocoloCliente cliente;

  public:
    /*Constructor de la clase.*/
    Juego();

    virtual void run() override;

    void stop();

    /*Destructor de la clase.*/
    virtual ~Juego();
  
  private:
    void hacer_ajustes_iniciales();

  };

#endif

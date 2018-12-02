#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <map>
#include "Socket.h"
#include "cola_bloqueante.h"
#include "protocolo_cliente.h"
#include "cola_segura.h"
#include "partida.h"
#include "thread.h"

class ProtocoloCliente;

class Juego: public Thread {
  private:
    std::map<int, std::shared_ptr<ColaBloqueante>> colas_envio_clientes;
    ColaSegura cola_recepcion;
    std::shared_ptr<Partida> partida;
    bool stopped = false;
    bool terminado = false;
    std::map<int,std::shared_ptr<ProtocoloCliente>> clientes;
    std::mutex mutex;

  public:

   // Juego(Partida *partida);
    
    /*Constructor de la clase.*/
    Juego(std::shared_ptr<Partida> part);

    void agregar_jugador(std::shared_ptr<ProtocoloCliente> cliente_jugador,
	std::string casa);

    //virtual 
    void run();
    //override;

    //void stop();

    /*Destructor de la clase.*/
    virtual ~Juego();
  
  private:
    /*Prepara las colas para recibir y enviar mensajes.*/
    void hacer_ajustes_iniciales();

  };

#endif

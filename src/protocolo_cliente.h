#ifndef PROTOCOLO_CLIENTE_H
#define PROTOCOLO_CLIENTE_H

#include <thread>
#include "Socket.h"
#include "cola_bloqueante.h"

class ProtocoloCliente {
  private:
    Socket socket_cliente;
    bool jugando;
    ColaBloqueante *cola_envio;
    ColaBloqueante *cola_recepcion;
    std::thread t_envios;
    std::thread t_recibos;

  public:
    /*Constructor clase.*/
    ProtocoloCliente(Socket skt_clt);

    /*Recibe dos puntero a dos colas bloqueantes. Una
    para envio de mensajes y la otra para el recibo de 
    estos.*/
    void agregar_colas(ColaBloqueante *cola_env, ColaBloqueante *cola_rec);


    void start();

    void send();
    void receive();
    void stop();

    /*Destructor de la clase.*/
    ~ProtocoloCliente();
};

#endif
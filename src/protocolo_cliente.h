#ifndef PROTOCOLO_CLIENTE_H
#define PROTOCOLO_CLIENTE_H

#include <thread>
#include "Socket.h"
#include "cola_bloqueante.h"
#include "cola_segura.h"

class ProtocoloCliente {
  private:
    Socket socket_cliente;
    bool jugando;
    ColaBloqueante *cola_envio;
    ColaSegura *cola_recepcion;
    std::thread t_envios;
    std::thread t_recibos;

  public:
    ProtocoloCliente();
    /*Constructor clase.*/
    ProtocoloCliente(Socket skt_clt);

    /*Recibe dos puntero a dos colas bloqueantes. Una
    para envio de mensajes y la otra para el recibo de 
    estos.*/
    void agregar_colas(ColaBloqueante *cola_env, ColaSegura *cola_rec);

    /*Lanza el hilo para empezar a recibir mensajes y el hilo
    para mandar mensajes.*/
    void inicializar();

    /*Desencola mensajes de la cola bloqueante de envios que tiene
    apuntando como atributo y manda los mensajes por socket.*/
    void enviar_mensajes();

    /*Recibe mensajes por socket y los encola en la cola
    bloqueante de recibos que tiene apuntada como atributo.*/
    void recibir_mensajes();
    
    /*Finaliza el envio y recibo de mensajes del cliente seteando
    como false su atributo jugando.*/
    void finalizar();
};

#endif
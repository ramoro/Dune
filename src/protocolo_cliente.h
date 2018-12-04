#ifndef PROTOCOLO_CLIENTE_H
#define PROTOCOLO_CLIENTE_H

#include <thread>
#include "Socket.h"
#include "cola_bloqueante.h"
#include "cola_segura.h"
#include "organizador_juegos.h"

class OrganizadorJuegos;

class ProtocoloCliente {
  private:
    Socket socket_cliente;
    int id;
    int id_sala_asociada;
    int casa;
    OrganizadorJuegos &organizador;
    bool jugando;
    bool esperando_en_sala;
    std::shared_ptr<ColaBloqueante> cola_envio;
    ColaSegura *cola_recepcion;
    std::thread t_envios;
    std::thread t_recibos;

  public:
    /*Constructor clase.*/
    ProtocoloCliente(Socket skt_clt, int id, 
    OrganizadorJuegos &organizador);

    /*Recibe dos puntero a dos colas bloqueantes. Una
    para envio de mensajes y la otra para el recibo de 
    estos.*/
    void agregar_colas(std::shared_ptr<ColaBloqueante> cola_env, 
    ColaSegura *cola_rec);
 
    /*Lanza el hilo para mandar mensajes.*/
    void inicializar();

    /*Desencola mensajes de la cola bloqueante de envios que tiene
    apuntando como atributo y manda los mensajes por socket.*/
    void enviar_mensajes();

    /*Recibe y envia mensajes cuando el cliente esta en la zona de 
    salas. Luego cuando esta en modo juega recibe mensaes y los encola 
    en la cola bloqueante de recibos que tiene apuntada como atributo.*/
    void iniciar_protocolo();
    
    /*Finaliza el envio y recibo de mensajes del cliente seteando
    como false su atributo jugando.*/
    void finalizar();

    /*Devuelve el id del cliente.*/
    int pedir_id();

    /*Devuelve el id de la sala a la que esta asociado el cliente
    en caso de estar asociado a una. Sino devuelve -1.*/
    int pedir_id_sala_asociada();

    /*Lanza un thread para el envio y recibo de mensajes mientras
    el cliente esta en la zona de salas esperando a jugar.*/
    void iniciar_protocolo_en_salas();

    /*Setea al cliente en jugando y lo saca del estado esperando
    en sala.*/
    void cambiar_a_modo_juego();

    /*Recibe el nombre de un mapa y el id del mapa y envia esta info
    al cliente que le corresponde el socket que tiene como
    atributo la clase. Tambien puede reicibr el nombre
    de un mapa que tiene una sala y el id de esta.*/
    void enviar_mapa_o_sala(std::string nombre, int id);

    /*Si el cliente esta en juego habiendo ya elegido una casa
    devuelve el id de la misma, sino devuelve -1.*/
    int pedir_casa();

    /*Joinea el hilo de envios que se esta usando para enviar y recibir
    mensajes en la parte de espera antes de jugar.*/
    void joinear_hilo_espera_a_jugar();
};

#endif
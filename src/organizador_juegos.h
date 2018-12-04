#ifndef ORGANIZADOR_JUEGOS_H
#define ORGANIZADOR_JUEGOS_H

#include <mutex>
#include <string>
#include <map>
#include <memory>
#include <list>
#include "cola_bloqueante.h"
#include "Socket.h"
#include "partida.h"
#include "sala.h"

class ProtocoloCliente;
class Juego;
class Sala;

/*Clase monitor que se encarga de proteger las salas y los mapas
y se encarga de la creacion de salas, union de jugadores e inicio 
de partidas. Ademas de que almacena mapas nuevos.*/
class OrganizadorJuegos {
private:
    int contador_id_clientes; // da el id del proximo cliente que se conecta
    int contador_id_salas; // da el id de la proxima sala a crearr
    int contador_id_mapas;
    std::mutex mutex;
    std::map<int, std::shared_ptr<ProtocoloCliente>> clientes;
    std::map<int, std::shared_ptr<Sala>> salas;
    std::map<int, std::string> mapas;
    std::set<std::shared_ptr<ProtocoloCliente>> clientes_desconectados;

public:
    /*Constructor de la clase.*/
    OrganizadorJuegos();

    /*Recibe un socket y agrega un nuevo cliente al sistema con ese socket.*/
    void agregar_cliente(Socket sckt_cliente);

    /*Crea una nueva sala con el nombre el mapa que le corresponde
    al id recibido y con la cantidad maxima de jugadores recibida y
    crea un juego agregandolselo. Se le asigna el id del que la creo.
    Devuelve el id de la nueva sala.*/
    int crear_sala(int id_mapa, int max_jugadores, int id_creador);

    /*Recibe el id de una sala y e inicia su juego en otro hilo.*/
    void iniciar_juego(int id_sala);

    /*Recibe el id de un cliente y le manda todos los mapas con su nombre
    e id.*/
    void recorrer_mapas_para_enviar(int id_cliente);

    /*Recibe el id de un cliente y le manda todas las salas con el nombre
    del mapa en el que se jugara y su id.*/
    void recorrer_salas_para_enviar(int id_cliente);

    /*Recibe el id de una sala y le aumenta en uno la cantidad
    de clientes que tiene dentro.*/
    void agregar_cliente_a_sala(int id_sala);

    /*Recibe el id de un cliente y lo agrega al vector de clientes
    desconectados, sacandolo de la sala en la que esta
    si es que esta en alguna.*/
    void desconectar_cliente(int id_cliente);

    /*Agarra a todos los clientes que estan en la espera de jugar
    y los pone como desconectados.*/
    void apagar();

    /*Recibe el nombre de un mapa y lo agrega a la clase.*/
    void agregar_mapa(std::string nombre_mapa);

    /*Destructor de la clase.*/
    ~OrganizadorJuegos();
};


#endif
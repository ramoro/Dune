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
    std::mutex mutex;
    std::map<int, std::shared_ptr<ProtocoloCliente>> clientes;
    std::map<int, std::shared_ptr<Sala>> salas;
    std::map<int, std::string> mapas;

public:
    /*Constructor de la clase.*/
    OrganizadorJuegos();

    /*Recibe un socket y agrega un nuevo cliente al sistema con ese socket.*/
    void agregar_cliente(Socket sckt_cliente);

    /*Crea una nueva sala con el nombre el mapa que le corresponde
    al id recibido y con la cantidad maxima de jugadores recibida y
    crea un juego agregandolselo.
    Devuelve el id de la nueva sala.*/
    int crear_sala(int id_mapa, int max_jugadores);

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

    /*Destructor de la clase.*/
   	~OrganizadorJuegos();

   /* // Agrega un nuevo cliente a la lista de clientes activos
    UserProxy* addClient(Socket& socket);

    // Crea una nueva sala con el nombre especificado y el nombre de map
    // especificado. La sala se borrará unicamente cuando quede vacía.
    // Devuelve el ID de la sala creada.
    int createRoom(std::string& roomName, std::string& mapName);

    // Agrega el usuario a la sala pasada.
    // Devuelve true si lo pudo agregar exitosamente; false si no existe
    // la sala o ya se encuentra llena.
    bool userJoinRoom(int userId, int roomId);

    // Funcion que llama una partida. Le pasa el objeto PlayerProxy al sistema
    // indicandole que ese jugador dejo la partida y aun esta vigente la
    // conexion, por lo que debe tratarlo como si estuviese en el menu de salas.
    // Se crea un UserProxy, para interactuar dentro de este escenario.
    void playerLeaveRoom(PlayerProxy* player);

    // Devuelve un vector con informacion sobre las salas activas. El vector
    // es de la forma id1, info1,..., idN, infoN. 
    std::vector<std::string> roomsInfo();

    ~TDSystem(); // Destructor*/
};


#endif
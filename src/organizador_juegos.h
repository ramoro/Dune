#ifndef ORGANIZADOR_JUEGOS_H
#define ORGANIZADOR_JUEGOS_H

#include <mutex>
#include <string>
#include <map>
#include <memory>
#include <list>
//#include "protocolo_cliente.h"
#include "cola_bloqueante.h"
//#include "juego.h"
#include "Socket.h"
#include "partida.h"

class ProtocoloCliente;
class Juego;

/******************************** OrganizadorJuegos ********************************
 Clase monitor, que controla la informacion de cada una de las conexiones
 de jugadores que estan siendo llevadas a cabo, las salas activas y las
 partidas en progreso.
 *************************************************************************/
/*Clase monitor*/
class OrganizadorJuegos {
private:
    int contador_id_clientes; // da el id del proximo cliente que se conecta
    int contador_id_juegos; // da el id de la proxima sala/partida/juego a crearr
    std::mutex mutex;
    //map con el id del cliente y su cola
    std::map<int, std::shared_ptr<ProtocoloCliente>> clientes;
    std::map<int, std::shared_ptr<Juego>> juegos;
    std::map<int, std::shared_ptr<Partida>> partidas;

public:
    /*Constructor de la clase.*/
    OrganizadorJuegos();

    /*Recibe un socket y agrega un nuevo cliente al sistema con ese socket.*/
    void agregar_cliente(Socket sckt_cliente);

    /*Crea un nuevo juego agregandolo al organizador de juegos y devuelve
    el id del nuevo juego.*/
    int crear_juego();

    /*Recibe el id de un juego y lo inicia en otro hilo.*/
    void iniciar_juego(int id_juego);

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
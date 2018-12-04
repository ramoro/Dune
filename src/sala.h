#ifndef SALA_H
#define SALA_H

#include <string>
#include <memory>
#include "juego.h"
#include "partida.h"
#include "protocolo_cliente.h"

class Juego;
class ProtocoloCliente;

class Sala {
  private:
    std::shared_ptr<Juego> juego;
    std::shared_ptr<Partida> partida;
    std::string nombre_mapa;
    int cantidad_maxima_jugadores;
    int id_creador;
    int cantidad_jugadores_dentro;
    bool sala_llena;
    bool juego_empezado;

  public:
    /*Constructor de la clase.*/
    Sala(std::shared_ptr<Juego> juego, std::shared_ptr<Partida> partida,
    std::string nombre_mapa, int cantidad_maxima_jugadores, int id_creador);

    /*Larga el juego que posee como atributo en un hilo nuevo.*/
    void largar_juego();

    /*Recibe un puntero a un protocolo cliente y 
    lo agrega al juego.*/
    void agregar_jugador_a_juego(std::shared_ptr<ProtocoloCliente> jugador);

    /*Suma en uno la cantidad de clientes dentro. Si se llego
    a la cantidad maxima de jugadores sala_llena se setea en true.*/
    void agregar_cliente();

    /*Devuelve el nombre del mapa en el que se jugara.*/
    std::string pedir_nombre_mapa();

    /*Devuelve true si la sala esta llena, false
    en caso contrario.*/
    bool esta_llena();

    /*Setea a la sala como llena para imposibilitar que alguien se
    una.*/
    void cerrar_sala();

    /*Devuelve true si el juego empezo, false en caso contario.*/
    bool tiene_juego_empezado();

    /*Joinea el hilo del juego.*/
    void joinear_juego();

    /*Resta en uno la cantidad de jugadores dentro de la sala.*/
    void sacar_cliente();

    /*Devuelve el id del creador de la sala.*/
    int pedir_id_creador();

    /*Destructor de la clase.*/
    ~Sala();


};

#endif
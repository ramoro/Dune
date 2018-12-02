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
    int cantidad_maxima_jugadores;
    int cantidad_jugadores_dentro;
    std::string nombre_mapa;
    std::shared_ptr<Juego> juego;
    std::shared_ptr<Partida> partida;

  public:
    /*Constructor de la clase.*/
    Sala(std::shared_ptr<Juego> juego, std::shared_ptr<Partida> partida);

    void largar_juego();

    void agregar_jugador_a_juego(std::shared_ptr<ProtocoloCliente> jugador,
    std::string casa);

    /*Destructor de la clase.*/
    ~Sala();


};

#endif
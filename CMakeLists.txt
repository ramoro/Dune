cmake_minimum_required(VERSION 2.8)

project(modelo_dune)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -Wall -pedantic")

add_library(sdldemo STATIC
 src/Armas/arma.cpp
 src/Armas/arma.h
 src/Armas/canion.cpp
 src/Armas/canion.h
 src/Armas/canion_22mm.cpp
 src/Armas/canion_22mm.h
 src/Armas/canion_plasma.cpp
 src/Armas/canion_plasma.h
 src/Armas/lanza_misiles.cpp
 src/Armas/lanza_misiles.h
 src/Armas/onda_sonido.cpp
 src/Armas/onda_sonido.h
 src/Armas/rifle_asalto.cpp
 src/Armas/rifle_asalto.h
 src/Terrenos/terreno.cpp
 src/Terrenos/terreno.h
 src/Terrenos/especia.cpp
 src/Terrenos/especia.h
 src/Terrenos/no_especia.cpp
 src/Terrenos/especia.h
 src/UnidadesMovibles/unidad_movible.cpp
 src/UnidadesMovibles/unidad_movible.h
 src/UnidadesMovibles/fabrica_unidades_movibles.cpp
 src/UnidadesMovibles/fabrica_unidades_movibles.h
 src/UnidadesMovibles/cosechadora.cpp
 src/UnidadesMovibles/cosechadora.h
 src/UnidadesMovibles/desviador.cpp
 src/UnidadesMovibles/desviador.h
 src/UnidadesMovibles/devastador.cpp
 src/UnidadesMovibles/devastador.h
 src/UnidadesMovibles/raider.cpp
 src/UnidadesMovibles/raider.h
 src/UnidadesMovibles/tanque.cpp
 src/UnidadesMovibles/tanque.h
 src/UnidadesMovibles/tanque_sonico.cpp
 src/UnidadesMovibles/tanque_sonico.h
 src/UnidadesMovibles/trike.cpp
 src/UnidadesMovibles/trike.h
 src/UnidadesMovibles/infanteria_ligera.cpp
 src/UnidadesMovibles/infanteria_ligera.h
 src/UnidadesMovibles/infanteria_pesada.cpp
 src/UnidadesMovibles/infanteria_pesada.h
 src/UnidadesMovibles/fremen.cpp
 src/UnidadesMovibles/fremen.h
 src/UnidadesMovibles/sardaukar.cpp
 src/UnidadesMovibles/sardaukar.h
 src/UnidadesMovibles/vehiculo.cpp
 src/UnidadesMovibles/vehiculo.h
 src/UnidadesMovibles/unidad_infanteria.cpp
 src/UnidadesMovibles/unidad_infanteria.h
 src/Edificios/edificio.cpp
 src/Edificios/edificio.h
 src/Edificios/fabrica_edificios.cpp
 src/Edificios/fabrica_edificios.h
 src/Edificios/centro_construccion.cpp
 src/Edificios/centro_construccion.h
 src/Edificios/refineria.cpp
 src/Edificios/refineria.h
 src/Edificios/trampa_aire.cpp
 src/Edificios/trampa_aire.h
 src/Edificios/silo.cpp
 src/Edificios/silo.h
 src/Edificios/fabrica_ligera.cpp
 src/Edificios/fabrica_ligera.h
 src/Edificios/fabrica_pesada.cpp
 src/Edificios/fabrica_pesada.h
 src/Edificios/cuartel.cpp
 src/Edificios/cuartel.h
 src/Edificios/palacio.cpp
 src/Edificios/palacio.h
)
set(CMAKE_BUILD_TYPE Debug)
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (main
 src/main.cpp  
 src/objeto_dune.cpp
 src/objeto_dune.h
 src/coordenada.cpp
 src/coordenada.h
 src/jugador.cpp
 src/jugador.h
 src/mapa.cpp
 src/mapa.h
 src/partida.cpp
 src/partida.h
 src/buscador_mejor_camino.cpp
 src/buscador_mejor_camino.h
 src/nodo.cpp
 src/nodo.h
 src/observador.cpp
 src/observador.h
)


target_link_libraries(main sdldemo)


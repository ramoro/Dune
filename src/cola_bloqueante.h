#ifndef COLA_BLOQUEANTE_H
#define COLA_BLOQUEANTE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "mensaje_protocolo.h"

/*Clase que representa una cola que se bloquea con un 
mutex a la hora de poner o sacar cosas de ella.*/
class ColaBloqueante {
    private:
        std::queue<MensajeProtocolo> q;
        const unsigned int max_size;
        std::mutex mutex;
        std::condition_variable is_not_full;
        std::condition_variable is_not_empty;

    public:
        /*Constructor de la clase.*/
        ColaBloqueante(const unsigned int max_size);

        /*Recibe un mensaje protocolo con la data a enviar al cliente
         y lo encola en la cola, bloqueando
        el procedimiento.*/
        void push(const MensajeProtocolo& mensaje);

        /*Saca un elemento de la cola y lo devuelve. El procedimiento
        esta protegido.*/
        MensajeProtocolo pop();

    private:
        /*El objeto no se puede crear por copia.*/
        ColaBloqueante(const ColaBloqueante&) = delete;

        /*El objeto no se puede asingar por copia.*/
        ColaBloqueante& operator=(const ColaBloqueante&) = delete;
};

#endif
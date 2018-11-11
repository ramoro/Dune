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

/*Clase que representa una cola que se bloquea con un 
mutex a la hora de poner o sacar cosas de ella.*/
class ColaBloqueante {
    private:
        std::queue<std::string> q;
        const unsigned int max_size;
        std::mutex mutex;
        std::condition_variable is_not_full;
        std::condition_variable is_not_empty;

    public:
        /*Constructor de la clase.*/
        ColaBloqueante(const unsigned int max_size);

        /*Recibe un string y lo encola en la cola, bloqueando
        el procedimiento.*/
        void push(const std::string& val);

        /*Saca un elemento de la cola y lo devuelve. El procedimiento
        esta protegido.*/
        std::string pop();

    private:
        /*El objeto no se puede crear por copia.*/
        ColaBloqueante(const ColaBloqueante&) = delete;

        /*El objeto no se puede asingar por copia.*/
        ColaBloqueante& operator=(const ColaBloqueante&) = delete;
};

#endif
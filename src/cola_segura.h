#ifndef COLA_SEGURA_H
#define COLA_SEGURA_H

#include <mutex>
#include <queue>
#include "mensaje_protocolo.h"

/*Clase que representa una cola protegida
a la hora de sacar o meter cosas dentro de ella.*/
class ColaSegura {
    private:
        std::queue<MensajeProtocolo> q;
        std::mutex mutex;
        const unsigned int max_size;

    public:
        /*Constructor de la clase.*/
        ColaSegura(const unsigned int max_size);

        /*Recibe un mensaje protocolo con la data a enviar al cliente
         y lo encola protegiendo la accion.*/
        void push(const MensajeProtocolo& mensaje);

        /*Saca un elemento de la cola y lo devuelve. El procedimiento
        esta protegido.*/
        MensajeProtocolo pop();

        /*Devuelve true si cola vacia, false en caso contrario.*/
        bool vacia();

    private:
        /*El objeto no se puede crear por copia.*/
        ColaSegura(const ColaSegura&) = delete;

        /*El objeto no se puede asingar por copia.*/
        ColaSegura& operator=(const ColaSegura&) = delete;
};

#endif
#include "cola_bloqueante.h"
#include "cola_cerrada_error.h"
#include <iostream>

ColaBloqueante::ColaBloqueante(const unsigned int max_size) : 
max_size(max_size) {}
        
void ColaBloqueante::push(const MensajeProtocolo& mensaje) {
    std::unique_lock<std::mutex> lock(mutex);

    if (q.empty()) {
        is_not_empty.notify_all();
    }

	while (q.size() >= this->max_size) {
	   //cola llena se bloquea
		is_not_full.wait(lock);
	}

    q.push(mensaje);
} 

MensajeProtocolo ColaBloqueante::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while (q.empty()) {
        std::cout << " cola vacia, el pull se bloquea\n";
        is_not_empty.wait(lock);
    }

    const MensajeProtocolo mensaje = q.front();
    if (mensaje.pedir_accion() == 'n') {
        throw ColaCerradaError("cola cerrada");
    }
    q.pop();

    is_not_full.notify_all();

    return mensaje;
}

void ColaBloqueante::cerrar() {
    MensajeProtocolo mensaje;
    mensaje.asignar_accion('n');
    this->push(mensaje);
}

bool ColaBloqueante::vacia() {
    return this->q.empty();
}
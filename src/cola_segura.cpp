#include "cola_segura.h"

ColaSegura::ColaSegura(const unsigned int max_size) : 
max_size(max_size) {}

void ColaSegura::push(const MensajeProtocolo& mensaje) {
 	std::lock_guard<std::mutex> lck(mutex);
 	q.push(mensaje);
}

MensajeProtocolo ColaSegura::pop() {
 	std::lock_guard<std::mutex> lck(mutex);
 	const MensajeProtocolo mensaje = std::move(q.front());
 	q.pop();
 	return mensaje;
}

bool ColaSegura::vacia() {
	std::lock_guard<std::mutex> lck(mutex);
	return q.empty();
}
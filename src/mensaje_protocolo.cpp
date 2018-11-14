#include "mensaje_protocolo.h"

void MensajeProtocolo::asignar_accion(const char accion) {
	this->accion = accion;
}

void MensajeProtocolo::agregar_parametro(int parametro) {
	parametros.push_back(parametro);
}

char MensajeProtocolo::pedir_accion() {
	return accion;
}

std::vector<int> MensajeProtocolo::pedir_parametros() {
	return parametros;
}

void MensajeProtocolo::limpiar_mensaje() {
	accion = '0';
	parametros.clear();
}
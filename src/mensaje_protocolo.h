#ifndef MENSAJE_PROTOCOLO_H
#define MENSAJE_PROTOCOLO_H

#include <vector>

/*Clase que representa un mensaje que corresponde al protocolo
establecido. El mensaje contiene los datos que se enviaran por socket.*/
class MensajeProtocolo {
	private:
		char accion;
		std::vector<int> parametros;
	public:
		/*Recibe un char y se lo asgina al atributo accion.*/
		void asignar_accion(const char accion);

		/*Recibe un parametro de la accion a enviar como mensaje
		y lo mete en el vector de parametros.*/
		void agregar_parametro(int parametro);

		/*Devuelve la accion del mensaje.*/
		char pedir_accion();

		/*Devueleve el vector de ints con los parametros de la accion*/
		std::vector<int> pedir_parametros();

		/*Setea la accion en una accion invalida y limpia
		el vector de parametros.*/
		void limpiar_mensaje();
};

#endif 
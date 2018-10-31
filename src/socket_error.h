#ifndef SOCKET_ERROR_H
#define SOCKET_ERROR_H

#include <typeinfo>

#define BUF_LEN 70

/*Clase que representa un error en caso de haber algun problema
intentando hacer alguna operacion con un socket.*/
class SocketError : public std::exception {
	private:
		char msg_error[BUF_LEN];
	public:
		/*Constructor de la excepcion.*/
		SocketError(const char* fmt, ...) noexcept;

		/*Devuelve el mensaje de error que emite la excepcion.*/
		virtual const char* what() const noexcept;


		/*Destructor de la excepcion.*/
		virtual ~SocketError() noexcept {}
};

#endif

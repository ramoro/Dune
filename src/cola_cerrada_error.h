#ifndef COLA_CERRADA_ERROR_H
#define COLA_CERRADA_ERROR_H

#include <typeinfo>

#define BUF_LONG 20

/*Clase que representa una excepcion que salta
cuando se cierra una cola bloqueante.*/
class ColaCerradaError: public std::exception {
	private:
		char msg_error[BUF_LONG];
	public:
		/*Constructor de la excepcion.*/
		ColaCerradaError(const char* fmt, ...) noexcept;

		/*Devuelve el mensaje de error que emite la excepcion.*/
		virtual const char* what() const noexcept;


		/*Destructor de la excepcion.*/
		virtual ~ColaCerradaError() noexcept {}
};

#endif

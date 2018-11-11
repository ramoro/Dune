#ifndef THREAD_H_
#define THREAD_H_

#include <thread>

/*Clase abstracta que representa un thread.*/
class Thread {
	private:
		std::thread thread;

	public:
		/*Constructor de la clase.*/
		Thread();
		
		/*Lanza el thread.*/
		void start();

		/*Espera a que thread termine y lo joinea.*/
		void join();

		/*Metodo virtual puro donde se ejecutara lo que se quiere
		hacer en un hilo aparte.*/
		virtual void run() = 0;

		/*Thread sin constructor por copia.*/
		Thread(const Thread&) = delete;

		/*Thread sin asignacion por copia.*/
		Thread& operator=(const Thread&) = delete;
		
		/*Constructor de la clase por movimiento.*/
		Thread(Thread&& other);

		/*Asignacion por movimiento de la clase.*/
		Thread& operator=(Thread&& other);

		/*Destructor de la clase.*/
		virtual ~Thread();
};

#endif

#ifndef CONVERSOR_H
#define CONVERSOR_H
#include "../src/config.h"
#include <stdio.h>
/*Clase que convierte la baldosa en el pixel indicado a pasar para el client.
Funciona de manera inversa, convirtiendo el pixel recibido por el cliente a 
la baldosa correcta*/
class Conversor {
	private:
		int cant_pixel_ancho;
		int cant_pixel_alto;
		
	public:
		/*Constructor de la clase*/
		Conversor(Config &config);
		std::pair<int,int> de_pixel_a_baldosa(std::pair<int,int> pixel);
		std::pair<int,int> de_baldosa_a_pixel(std::pair<int,int> baldosa);
};
#endif

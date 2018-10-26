#ifndef OBJETO_DUNE_H
#define OBJETO_DUNE_H


/*Clase abstracta que representa a un objeto del mundo dune que puede
ser tanto un edificio como una unidad movible (vehiculos y 
unidades de ataque).*/
class ObjetoDune {
	private:
		int vida;
		int costo_dinero;

	protected:
		int id_tipo;

	public:
		/*Constructor de la clase.*/
		ObjetoDune(int vida, int costo);

		/*Recibe el danio a disminuirle a la vida del objeto y devuelve
		la vida restante que le queda. En caso de devolver 0 o un numero
		negativo significa que la unidad murio/fallecio/se destruyo/caput.*/
		int reducir_vida(int danio);

		/*Devuelve el costo en dinero que conlleva obtener el objeto
		(puede ser el costo que trae construir un edificio o un vehiculo
		o el costo que trae entrenar a una unidad de ataque).*/
		int obtener_costo();

		/*Devuelve el id segun el tipo al que corresponde el objeto.
		Por ejemplo dentro de los edificios todas las Refinerias se 
		identifican con un id.*/
		int pedir_id_tipo();
};

#endif

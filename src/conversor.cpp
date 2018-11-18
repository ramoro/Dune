#include "conversor.h"
#include <math.h>
Conversor::Conversor(Root &root){
	cant_pixel_ancho = root["Conversor"].get("cant_pixel_ancho", 0).asInt();
	cant_pixel_alto = root["Conversor"].get("cant_pixel_alto", 0).asInt();
}
std::pair<int,int> Conversor::de_baldosa_a_pixel(std::pair<int,int> baldosa){
	std::pair<int,int> pixel;
	pixel.first = round((cant_pixel_ancho * baldosa.first) - (cant_pixel_ancho/2));
	pixel.second = round((cant_pixel_alto * baldosa.second) - (cant_pixel_alto/2));
	return pixel;
}
std::pair<int,int> Conversor::de_pixel_a_baldosa(std::pair<int,int> pixel){
	std::pair<int,int> baldosa;
	baldosa.first = round((pixel.first + (cant_pixel_ancho/2))/cant_pixel_ancho);
	baldosa.second = round((pixel.second + (cant_pixel_alto/2))/cant_pixel_alto);
	return baldosa;
}

#include "cilindro.h"
#include <iostream>
#include <iomanip>
#define PI 3.141592

Cilindro crearCilindro(float _radio, float _altura, string _color) {
	Cilindro cili = new struct EstructuraCilindro;
	cili->altura = _altura;
	cili->radio = _radio;
	cili->color = _color;
	/*El area del cilindro es la del cuerpo MÁS la suma de las areas de ambas bases*/
	cili->area = (2 * PI * _radio * _altura) + ((PI * _radio * _radio) * 2);
	return cili;
}

void destruirCilindro(Cilindro cili) {
	delete(cili);
}

//GETTERS
float getCilindroRadio(Cilindro cili){
    return cili->radio;
}
float getCilindroAltura(Cilindro cili){
    return cili->altura;
}
float getCilindroArea(Cilindro cili) {
	return cili->area;
}
string getCilindroColor(Cilindro cili) {
	return cili->color;
}

void mostrarCilindro(Cilindro cili) {
    cout << left << (char)179 << " " << setw(10) << "cilindro";
    cout << " " << (char)179 << " ";
    cout << setw(8) << right << getCilindroArea(cili) << " cm" << (char)253;
    cout << " " << (char)179 << " ";
    cout << setw(10) << left << getCilindroColor(cili);
    cout << " " << (char)179 << " ";
    cout << setw(6) << right << getCilindroRadio(cili);
    cout << " " << (char)179 << " ";
    cout << setw(6) << getCilindroAltura(cili) << " " << (char)179 << endl;
}

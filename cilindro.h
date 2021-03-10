#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED
#include <string>
#pragma once

using namespace std;

struct EstructuraCilindro
{
	float radio;
	float altura;
	float area; // Área = 2 × π  × r × ( h + r )
	string color;
};
typedef struct EstructuraCilindro* Cilindro;

//CREADOR
Cilindro crearCilindro(float, float, string);

//DESTRUCTOR
void destruirCilindro(Cilindro);

//GETTERS
float getCilindroRadio(Cilindro);
float getCilindroAltura(Cilindro);
float getCilindroArea(Cilindro);
string getCilindroColor(Cilindro);

//No se crean SET ya que no se van a modificar datos.


//MOSTRAR
//Muestra que figura es.
void mostrarCilindro(Cilindro);

#endif // CILINDRO_H_INCLUDED

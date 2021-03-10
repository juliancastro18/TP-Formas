#include "circulo.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#define pi 3.14

Circulo crearCirculo(float r, string cr)
{
    Circulo c = new struct EstructuraCirculo;
    c->radio=r;
    c->diametro=2*r;
	c->area=pi*pow(r,2);
	c->color=cr;
	return c;
}

float getCirculoRadio(Circulo c)
{
    return c->radio;
}

float getCirculoDiametro(Circulo c)
{
    return c->diametro;
}

float getCirculoPerimetro(Circulo c)
{
    return 2*pi*c->radio;
}

float getCirculoArea(Circulo c)
{
    return c->area;
}

string getCirculoColor(Circulo c)
{
	return c->color;
}

void mostrarCirculo(Circulo c){
    cout << left << (char)179 << " " << setw(10) << "circulo";
    cout << " " << (char)179 << " ";
    cout << setw(8) << right << getCirculoArea(c) << " cm" << (char)253;
    cout << " " << (char)179 << " ";
    cout << setw(10) << left << getCirculoColor(c);
    cout << " " << (char)179 << " ";
    cout << setw(6) << right << getCirculoRadio(c);
    cout << " " << (char)179 << " ";
    cout << "...... " << (char)179 << endl;
}

void destruirCirculo(Circulo c)
{
    delete c;
}

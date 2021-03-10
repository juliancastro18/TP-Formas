#ifndef CIRCULO_H_INCLUDED
#define CIRCULO_H_INCLUDED
#include <string>

using namespace std;

struct EstructuraCirculo{
   float radio;
   float diametro;
   float area;
   string color;
};

typedef struct EstructuraCirculo * Circulo;

Circulo crearCirculo(float r, string cr);

float getCirculoRadio(Circulo c);

float getCirculoDiametro(Circulo c);

float getCirculoPerimetro(Circulo c);

float getCirculoArea(Circulo c);

string getCirculoColor(Circulo c);

void mostrarCirculo(Circulo c);

void destruirCirculo(Circulo c);

#endif // CIRCULO_H_INCLUDED

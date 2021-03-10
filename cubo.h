#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED
#include <string>

using namespace std;

struct EstructuraCubo {
    float lado;
    float area;
    string color;
};

typedef struct EstructuraCubo * Cubo;

Cubo crearCubo(float lado, string color);

float getCuboArea(Cubo x);
float getCuboLado(Cubo x);
string getCuboColor(Cubo x);

float calcularCuboArea(Cubo x);

void mostrarCubo(Cubo x);

void destruirCubo(Cubo x);


#endif // CUBO_H_INCLUDED

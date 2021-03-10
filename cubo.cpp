#include "cubo.h"
#include <iostream>
#include <iomanip>

Cubo crearCubo(float lado, string color) {
    Cubo x = new struct EstructuraCubo;

    x->lado = lado;
    x->area = calcularCuboArea(x);
    x->color = color;
    return x;
}

float getCuboArea(Cubo x) {
    return x->area;
}

float getCuboLado(Cubo x){
    return x->lado;
}

string getCuboColor(Cubo x) {

    return x->color;
}

float calcularCuboArea(Cubo x) {
    float area;
    area = (x->lado * x->lado) * 6;
    return area;
}

void mostrarCubo(Cubo x) {
    cout << left <<  (char)179 << " " << setw(10) << "cubo";
    cout << " " << (char)179 << " ";
    cout << setw(8) << right << getCuboArea(x) << " cm" << (char)253;
    cout << " " << (char)179 << " ";
    cout << setw(10) << left << getCuboColor(x);
    cout << " " << (char)179 << " ";
    cout << setw(6) << right << getCuboLado(x);
    cout << " " << (char)179 << " ";
    cout << "...... " << (char)179 << endl;
}

void destruirCubo(Cubo x) {
    delete x;
}

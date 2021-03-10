#include "triangulo.h"
#include <iostream>
#include <iomanip>

Triangulo crearTriangulo(float catetoA, float catetoB, string color){
    Triangulo t = new struct EstructuraTriangulo;
    t->catetoA = catetoA;
    t->catetoB = catetoB;
    t->area = calcularTrianguloArea(t);
    t->color = color;
    return t;
}

float getTrianguloArea(Triangulo t){
    return t->area;
}

string getTrianguloColor(Triangulo t){
    return t->color;
}

float calcularTrianguloArea(Triangulo t){
    float area;
    area = (t->catetoA * t->catetoB) / 2;
    return area;
}

float getTrianguloCatA(Triangulo t){
    return t->catetoA;
}

float getTrianguloCatB(Triangulo t){
    return t->catetoB;
}

void mostrarTriangulo(Triangulo t){
    cout << left << (char)179 << " " << setw(10) << "triangulo";
    cout << " " << (char)179 << " ";
    cout << setw(8) << right << getTrianguloArea(t) << " cm" << (char)253;
    cout << " " << (char)179 << " ";
    cout << setw(10) << left << getTrianguloColor(t);
    cout << " " << (char)179 << " ";
    cout << setw(6) << right << getTrianguloCatA(t);
    cout << " " << (char)179 << " ";
    cout << setw(6) << getTrianguloCatB(t) << " " << (char)179 << endl;
}

void destruirTriangulo(Triangulo t){
    delete t;
}

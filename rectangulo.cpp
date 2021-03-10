#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "Rectangulo.h"

//CONSTRUCTORES

Rectangulo crearRectangulo(float b, float a, string c){
    Rectangulo r = new struct EstructuraRectangulo;
    r->altura = a;
    r->base = b;
    r->area = b * a;
    r->color = c;
    return r;
}


//GETTERS

float getRecBase(Rectangulo r){
    return r->base;
}

float getRecAltura(Rectangulo r){
    return r->altura;
}

float getRecArea(Rectangulo r){
    return r->area;
}

string getRecColor(Rectangulo r){
    return r->color;
}


//SETTERS

void setRecBase(Rectangulo r, float nB){
    r->base=nB;
    r->area=(r->base) * (r->altura);
}

void setRecAltura(Rectangulo r, float nA){
    r->altura=nA;
    r->area=(r->base) * (r->altura);
}


//FUNCIONES

void mostrarRectangulo(Rectangulo r){
    cout << left << (char)179 << " " << setw(10) << "rectangulo";
    cout << " " << (char)179 << " ";
    cout << setw(8) << right << getRecArea(r) << " cm" << (char)253;
    cout << " " << (char)179 << " ";
    cout << setw(10) << left << getRecColor(r);
    cout << " " << (char)179 << " ";
    cout << setw(6) << right << getRecBase(r);
    cout << " " << (char)179 << " ";
    cout << setw(6) << getRecAltura(r) << " " << (char)179 << endl;
}


//DESTRUCTOR

void destruirRectangulo(Rectangulo r){
    delete r;
}

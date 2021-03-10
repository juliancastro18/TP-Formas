#ifndef TRIANGULO_H_INCLUDED
#define TRIANGULO_H_INCLUDED
#include <string>

using namespace std;

struct EstructuraTriangulo{
    float catetoA;
    float catetoB;
    float area;
    string color;
}; //AXIOMAS: todos los triangulos son rectangulos, son formados por dos numeros decimales que corresponden a catetos,
   //tiene un area que también es un numero decimal y un color formato string
typedef struct EstructuraTriangulo * Triangulo;


//----------CONSTRUCTOR----------

//PRE: necesita dos numeros que pueden ser decimales, y una cadena de texto que indica color
//POST: devuelve un triangulo creado con los datos ingresados por parametro
Triangulo crearTriangulo(float catetoA, float catetoB, string color);


//----------GETS----------

//PRE: necesita un triangulo creado
//POST: devuelve el area del triangulo
float getTrianguloArea(Triangulo t);

//PRE: necesita un triangulo creado
//POST: devuelve el color del triangulo formato texto
string getTrianguloColor(Triangulo t);

//PRE: necesita un triangulo creado
//POST: devuelve el cateto A/B del triangulo
float getTrianguloCatA(Triangulo t);
float getTrianguloCatB(Triangulo t);


//----------MISC----------

//PRE: necesita un triangulo creado con catetos ingresados
//POST: devuelve el area del triangulo
float calcularTrianguloArea(Triangulo t);

//PRE: necesita un triangulo creado
//POST: muestra por pantalla sus datos
void mostrarTriangulo(Triangulo t);


//----------DESTRUCTOR----------

//PRE: necesita un triangulo creado
//POST: libera la memoria que ocupaba
void destruirTriangulo(Triangulo t);


#endif // TRIANGULO_H_INCLUDED

#ifndef RECTANGULO_H_INCLUDED
#define RECTANGULO_H_INCLUDED
#include <string>

using namespace std;

struct EstructuraRectangulo{
    float   base;
    float   altura;
    float   area;
    string  color;
};
typedef struct EstructuraRectangulo *Rectangulo;

//AXIOMAS: Los datos ingresados de base y altura deben ser mayores a 0.

/*CONSTRUCTORES
PRE: Necesita que el tipo de dato Rectangulo haya sido declarado.
POST:Devuelve el dato Rectangulo con sus atributos cargados
*/

Rectangulo crearRectangulo(float b, float a, string c);

/*GETTERS
PRE: Necesita que se haya creado una variable tipo Rectanculo.
POST: Devuelve el parametro requerido de la variable Rectangulo ingresada (base, altura o area).
*/

float getRecBase(Rectangulo r);
float getRecAltura(Rectangulo r);
float getRecArea(Rectangulo r);
string getRecColor(Rectangulo r);

/*SETTERS
PRE: Necesita que se haya creado una variable tipo Rectanculo y el nuevo dato a modificar (Base o altura).
POST: Se modifica el dato nuevo ingresado (Base o  altura), y tambien el area que depende de ellos.
*/

void setRecBase(Rectangulo r, float nB);
void setRecAltura(Rectangulo r, float nA);

//FUNCIONES

/*PRE: Necesita que se haya creado una variable tipo Rectanculo.
POST: Muestra los atributos de la variable ingresada.
*/
void mostrarRectangulo(Rectangulo r);


/*DESTRUCTOR
PRE: Necesita que se haya creado una variable tipo Rectanculo.
POST: Elimina la variable, liberando la memoria reservada.
*/

void destruirRectangulo(Rectangulo r);

#endif // RECTANGULO_H_INCLUDED

#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

using namespace std;

//        0          1        2       3         4
enum {triangulo, rectangulo, cubo, circulo, cilindro};
enum {vacio, inicio, intermedio, fin, encabezado};

struct Nodo{
    void *forma;
    int tipoForma;
    Nodo *siguiente;
};
//AXIOMAS: se compone de un puntero a cualquier tipo de dato forma, un entero tipoForma que indica
//que tipo de dato almacena el puntero void (0 triangulo, 1 rectangulo, 2 cubo, 3 circulo, 4 cilindro)
//contine un puntero nodo que apunta al elemento siguiente de la lista.

typedef struct {
    Nodo* inicio;
    int tam;
}   ListaEnc;
//AXIOMAS: contiene un puntero al primer nodo de la lista y un entero tam que almacena el tamaño de la lista


//----------CONSTRUCTORES----------

//PRE: -
//POST: devuelve una lista creada, cuyo puntero inicio apunta a NULL
ListaEnc* crearLista();

//PRE: necesita recibir un puntero a tipo de dato forma, un entero que indique la forma, y un puntero al nodo siguiente
//POST: devuelve un nodo creado con los datos ingresados por parametro
Nodo* crearNodo(void *forma, int tipoForma, Nodo *sig);


//----------INSERCIÓN----------

//PRE: necesita una lista creada, un puntero tipo de dato forma, y entero que referencie a la forma
//POST: inserta al inicio de la lista un nodo con los datos recibidos por parametros
void insertarInicio(ListaEnc* lista, void *forma, int tipoForma);

//PRE: necesita una lista creada, un puntero tipo de dato forma, y entero que referencie a la forma, y posicion a insertar nodo
//POST: inserta en la posicion indicada un nodo con los datos recibidos por parametros
void insertar(ListaEnc* lista, void *forma, int tipoForma, int pos);

//PRE: necesita una lista creada, un puntero tipo de dato forma, y entero que referencie a la forma
//POST: inserta al final de la lista un nodo con los datos recibidos por parametros
void insertarFin(ListaEnc* lista, void *forma, int tipoForma);


//----------REMOVER----------

//PRE: necesita una lista creada
//POST: elimina el primer elemento de la lista, si el booleano es verdadero libera la memoria ocupada por la forma a la que apunta el nodo
//      (debe usarse así solo al final del programa con la lista original)
void removerInicio(ListaEnc* lista, bool liberarForma);

//PRE: necesita una lista creada y la posicion del nodo a eliminar
//POST: elimina el nodo ubicado en la posicion de la lista indicada
void remover(ListaEnc* lista, int pos);

//PRE: necesita una lista creada
//POST: elimina el ultimo elemento de la lista
void removerFin(ListaEnc* lista);


//----------GETS----------

//PRE: necesita un nodo creado
//POST: devuelve un entero que hace referencia al tipo de dato al que apunta el puntero void
int getNodoTipo(Nodo* n);

//PRE: necesita un nodo creado
//POST: devuelve un puntero void que apunta a la direccion contenida en el nodo
void* getNodoForma(Nodo* n);

//PRE: necesita un nodo creado
//POST: devuelve el area de la forma a la que apunta el puntero void del nodo
float getNodoArea(Nodo* n);

//PRE: necesita un nodo creado
//POST: devuelve el color en formato string de la forma a la que apunta el puntero void del nodo
string getNodoColor(Nodo* n);

//PRE: necesita el nodo de una lista ORDENADA POR COLOR
//POST: devuelve la cantidad de ese color y el nombre del color
int getTotalColor(Nodo* &n, string *color);

//PRE: necesita una lista creada
//POST: devuelve el tamaño de la lista
int getListaTamanio(ListaEnc* lista);

//PRE: necesita una lista creada y el tipo de forma de la cual se desea saber la cantidad
//POST: devuelve la cantidad de elementos del tipoForma ingresado por parametro
int getListaCantForma(ListaEnc* lista, int tipoForma);

//PRE: necesita lista creada
//POST: devuelve el primer nodo de la lista
Nodo* getListaInicio(ListaEnc* lista);


//----------ORDENACIÓN----------

//PRE: necesita una lista creada y booleano que indique orden ascendente o descendente
//POST: ordena sus elementos por el area de las formas que contienen
void ordenarPorArea(ListaEnc* lista, bool ordenAscendente);

//PRE: necesita una lista creada, entero que haga referencia al tipo de forma que se quiere mostrar, e indicar si se quiere mostrar subtotal por color
//POST: imprime por pantalla los elementos de la lista que son del tipo de forma indicada y la suma total de sus areas (imprime subtotales por color si se lo indica)
void totalPorFigura(ListaEnc* lista, int tipoFigura, bool porColor);

//PRE: necesita una lista creada, entero que haga referencia al tipo de forma que se quiere guardar en la nueva lista
//POST: devuelve una lista que contiene solo elementos del tipo de forma indicado por parametro, a partir de la lista que recibe
ListaEnc* crearListaUnicaForma(ListaEnc* lista, int tipoForma);

//PRE: necesita una lista creada
//POST: devuelve una lista creada con los elementos de la lista original ordenados por el color de sus formas (dentro de cada color se encuentran en el orden que ingresaron)
ListaEnc* crearListaOrdenadaPorColor(ListaEnc* lista);


//----------MISC----------

//PRE: necesita dos listas creadas
//POST: copia todos los elementos de la "listaOriginal" a la "listaCopia" (si listaCopia tiene contenido, la vacía)
void copiarLista(ListaEnc* listaOriginal, ListaEnc* listaCopia);

//PRE: necesita una lista creada
//POST: imprime por pantalla todo el contenido de la lista
void imprimirLista(ListaEnc* lista);

//PRE: necesita una lista creada
//POST: ordena e imprime por pantalla todo el contenido de la lista agrupada por color
void imprimirListaAgruparColor(ListaEnc* lista);

//PRE: necesita una lista creada
//POST: imprime por pantalla area mayor, area menor, promedio area
void imprimirDetalleAreas(ListaEnc* lista);

//PRE: necesita un nodo creado
//POST: imprime por pantalla el nodo enviado por parametro
void mostrarNodo(Nodo* n);

//PRE: requiere un entero que indica tipo de divisor necesitado: 0 vacio, 1 inicio, 2 intermedio, 3 fin, 4 encabezado
//POST: imprime por pantalla linea divisoria de tabla
void imprimirTabla(int n);


//----------DESTRUCTOR----------

//PRE: necesita una lista creada
//POST: elimina/libera todos sus nodos y la lista en sí.
//si el booleano es verdadero elimina todas las formas a las que apuntan sus nodos (solo usar con lista original al final del programa)
void liberarLista(ListaEnc* lista, bool liberarFormas);

//PRE: necesita un nodo creado
//POST: elimina/libera las formas a las que apunta el nodo
void liberarNodoForma(Nodo* n);

#endif // LISTA_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include "lista.h"
#include "triangulo.h"
#include "rectangulo.h"
#include "cubo.h"
#include "circulo.h"
#include "cilindro.h"

ListaEnc* crearLista() {

    ListaEnc* lista = new ListaEnc;
    if (lista == NULL)return NULL;
    lista->inicio = NULL;
    lista->tam = 0;
    return lista;
}


Nodo* crearNodo(void *forma, int tipoForma, Nodo *sig){

    Nodo *n = new Nodo;
    if(n==NULL)return NULL;
    n->forma = forma;
    n->tipoForma = tipoForma;
    n->siguiente = sig;
    return n;
}



void insertarInicio(ListaEnc* lista, void *forma, int tipoForma){

    if(lista==NULL)return;
    Nodo *aux = crearNodo(forma, tipoForma, lista->inicio); //creo un puntero nodo aux con el nuevo dato apuntando al (hasta entonces) inicio

    lista->inicio = aux; //hago de este puntero aux el inicio de la lista
    lista->tam++; //incremento la cantidad de elementos de la lista
}


void insertar(ListaEnc* lista, void *forma, int tipoForma, int pos){

    if(lista==NULL)return;
    if((pos<0)||(pos>lista->tam)){  //si se manda por parametro una posicion que no corresponde al tamaño de la lista, return
        cout << "POSICION INVALIDA" << endl;
        system("pause");
        return;
    }
    if(pos==0){
        insertarInicio(lista, forma, tipoForma);  //si la posicion es 0, paso a insertar inicio
        return;
    }
    Nodo *auxAnt = lista->inicio;   //creo nodo auxiliar que apunta al primer elemento
    for(int i=0;i<pos-1;i++){
        auxAnt = auxAnt->siguiente; //avanzo el auxiliar hasta el elemento que antecede a la posicion que quiero ocupar
    }
    Nodo *nuevoNodo = crearNodo(forma, tipoForma, auxAnt->siguiente); //creo nuevo nodo apuntando al nodo que le sucedía al auxAnt
    auxAnt->siguiente = nuevoNodo;  //hago que el auxAnt ahora apunte a mi nuevo nodo
    lista->tam++; //incremento la cantidad de elementos de la lista
}


void insertarFin(ListaEnc* lista, void *forma, int tipoForma){

    insertar(lista, forma, tipoForma, (lista->tam));
}




void removerInicio(ListaEnc* lista, bool liberarForma){

    if(lista==NULL)return;
    if(lista->tam==0)return;
    Nodo *aux = lista->inicio;   //guardo la posicion del inicio
    lista->inicio = lista->inicio->siguiente; //hago que la lista tenga su inicio en el hasta entonces segundo elemento
    if(liberarForma)liberarNodoForma(aux); //libero la memoria ocupada por la forma a la que apunta el nodo
    delete aux;                  //elimino la posicion de inicio
    lista->tam--;
}


void remover(ListaEnc* lista, int pos){

    if(lista==NULL)return;
    if((pos<0)||(pos>=lista->tam)){ //si se manda por parametro una posicion que no corresponde al tamaño de la lista, return
        cout << "POSICION INVALIDA" << endl;
        system("pause");
        return;
    }
    if(pos==0){
        removerInicio(lista,0);
        return;
    }
    Nodo *auxAnt = lista->inicio;   //creo nodo auxiliar que apunta al primer elemento
    for(int i=0;i<pos-1;i++){         //avanzo el auxiliar hasta el elemento que antecede a la posicion que quiero ocupar
        auxAnt = auxAnt->siguiente;
    }
    Nodo *auxEli = auxAnt->siguiente;  //creo un puntero auxiliar que apunta al elemento a eliminar
    auxAnt->siguiente = auxEli->siguiente;   //hago que el elemento anterior al que elimino apunte al elemento siguiente
    delete auxEli;  //elimino elimino el nodo
    lista->tam--;
}


void removerFin(ListaEnc* lista){

    remover(lista, (lista->tam)-1);
}




int getNodoTipo(Nodo* n){

    if(n==NULL)return -1;
    return n->tipoForma;
}


void* getNodoForma(Nodo*n){

    return n->forma;
}


float getNodoArea(Nodo* n){ //leo el entero tipoForma del nodo y obtengo el area casteando la figura correspondiente

    if(n==NULL)return -1;
    float auxArea;
    int tipo = n->tipoForma;
    switch (tipo)
    {
        case triangulo:     auxArea = getTrianguloArea( (Triangulo)n->forma ); break;
        case rectangulo:    auxArea = getRecArea( (Rectangulo)n->forma ); break;
        case cubo:          auxArea = getCuboArea( (Cubo)n->forma ); break;
        case circulo:       auxArea = getCirculoArea( (Circulo)n->forma ); break;
        case cilindro:      auxArea = getCilindroArea( (Cilindro)n->forma ); break;
        default:            auxArea = -1; break;
    }

    return auxArea;
}


string getNodoColor(Nodo* n){ //leo el entero tipoForma del nodo y obtengo el color casteando la figura correspondiente

    if(n==NULL)return "Error";
    string auxColor;
    int tipo = n->tipoForma;
    switch (tipo)
    {
        case triangulo:     auxColor = getTrianguloColor( (Triangulo)n->forma ); break;
        case rectangulo:    auxColor = getRecColor( (Rectangulo)n->forma ); break;
        case cubo:          auxColor = getCuboColor( (Cubo)n->forma ); break;
        case circulo:       auxColor = getCirculoColor( (Circulo)n->forma ); break;
        case cilindro:      auxColor = getCilindroColor( (Cilindro)n->forma ); break;
        default:            return "Error"; break;
    }

    return auxColor;
}


int getTotalColor(Nodo* &n, string *color){

    int sumaColor = 0;
    bool listo = false;

    while(!listo){
        sumaColor++;
        if(getNodoColor(n)!=getNodoColor(n->siguiente)) listo= true;
        *color = getNodoColor(n);
        n = n->siguiente; //avanzo de elemento
    }
    return sumaColor;
}


int getListaTamanio(ListaEnc* lista){

    return lista->tam;
}


int getListaCantForma(ListaEnc* lista, int tipoForma){

    int contador = 0;
    Nodo* aux = lista->inicio; //auxiliar al inicio de lista original

    while(aux!=NULL){ //recorro todos los elementos de la lista
        if(getNodoTipo(aux)==tipoForma) contador++; //si coincide el tipo de forma, sumo 1
        aux = aux->siguiente; //avanzo de elemento
    }
    return contador;
}


Nodo* getListaInicio(ListaEnc* lista){
    return lista->inicio;
}




void ordenarPorArea(ListaEnc* lista, bool ordenAscendente){

    if(lista->inicio==NULL)return;
    insertarInicio(lista, NULL, NULL); //creo un nodo auxiliar al inicio, que elimino cuando termina el procedimiento (necesario para el algoritmo)

    Nodo* auxAnt = lista->inicio;
    Nodo* aux = auxAnt->siguiente;
    bool listo;

    do{//recorro la lista hasta que no haya nada que cambiar
        listo = true; //si no hay ningun cambio, este booleano queda así, condicion del while principal
        while(aux->siguiente!=NULL){
            if(ordenAscendente){
                if( getNodoArea(aux) > getNodoArea(aux->siguiente) ){ //si el nodo en el que estoy es mayor al siguiente, invierto el orden
                    auxAnt->siguiente = aux->siguiente;
                    aux->siguiente = aux->siguiente->siguiente;
                    auxAnt->siguiente->siguiente = aux;
                    listo = false;
                }
                auxAnt = auxAnt->siguiente; //avanzo de posicion los auxiliares
                aux = auxAnt->siguiente;
            }else{
                if( getNodoArea(aux) < getNodoArea(aux->siguiente) ){ //si el nodo en el que estoy es menor al siguiente, invierto el orden
                    auxAnt->siguiente = aux->siguiente;
                    aux->siguiente = aux->siguiente->siguiente;
                    auxAnt->siguiente->siguiente = aux;
                    listo = false;
                }
                auxAnt = auxAnt->siguiente; //avanzo de posicion los auxiliares
                aux = auxAnt->siguiente;
            }
        }
        auxAnt = lista->inicio; ////vuelvo a poner los auxiliares en el inicio antes de repetir
        aux = auxAnt->siguiente;
    }while(!listo);

    removerInicio(lista,0); //elimino nodo auxiliar del inicio
}


void totalPorFigura(ListaEnc* lista, int tipoFigura, bool porColor){

    float totalArea, totalAreaColor = 0; //variables donde voy almacenando los totales
    int cantColor = 0;
    bool primero=true;
    ListaEnc* listaAux = crearListaUnicaForma(lista, tipoFigura); //creo lista auxiliar con elementos del tipo que necesito, a partir de la lista original

    if(getListaTamanio(listaAux)==0){ //si no hay ningun elemento del tipo que busco, notifico y retorno
            cout << "< NO HAY ELEMENTOS PARA MOSTRAR >" << endl;
            cout << "\nNo se utilizo plastico para la figura elegida." << endl;
            return;
    }

    if(porColor){ //si debo mostrar subtotal por color, creo lista auxiliar que reemplazo por la anterior, con sus elementos ordenados por color
        ListaEnc* l = crearListaOrdenadaPorColor(listaAux);
        liberarLista(listaAux,false);
        listaAux = l;
    }

    //encabezado
    imprimirTabla(encabezado);
    Nodo* aux = listaAux->inicio;

    while(aux!=NULL){ //recorro la lista
        if(primero && porColor){
            imprimirTabla(vacio); //imprimirTabla(vacio);
            primero=false;
        }
        totalArea += getNodoArea(aux); //voy almacenando en la variable el area de todos los elementos
        totalAreaColor += getNodoArea(aux); //hago lo mismo para el subtotal
        cantColor++; //cuento para subtotal
        mostrarNodo(aux); //muestro el detalle (cada elemento)
        if(porColor && getNodoColor(aux)!=getNodoColor(aux->siguiente)){ //si me piden mostrar subtotal y el nodo siguiente es otro color, muestro subtotal y reinicio totalAreaColor y cantColor
            imprimirTabla(intermedio);
            cout << (char)179 << " SUBTOTAL   " << (char)179 << " " << setw(8) << right << totalAreaColor << " cm" << (char)253 << " " << (char)179 << " CANT: " << left << setw(4) << cantColor << " " << (char)179 << " ...... " << (char)179 << " ...... " << (char)179 << endl;
            imprimirTabla(intermedio);
            totalAreaColor = 0;
            cantColor = 0;
            primero=true;
        }
        aux = aux->siguiente; //avanzo de elemento
    }
    //al terminar de recorrer la lista muestro totales
    if(porColor) imprimirTabla(vacio); //espaciado en caso de que haya que mostrar subtotales
    imprimirTabla(intermedio);
    cout << (char)179 << " TOTAL      " << (char)179 << " " << setw(8) << right << totalArea << " cm" << (char)253 << " " << (char)179 << " CANT: " << left << setw(4) << getListaTamanio(listaAux) << " " << (char)179 << " ...... " << (char)179 << " ...... " << (char)179 << endl;
    imprimirTabla(fin);

    liberarLista(listaAux,false); //libero lista auxiliar
}


ListaEnc* crearListaUnicaForma(ListaEnc* lista, int tipoForma){

    ListaEnc* listaForma = crearLista(); //creo nueva lista
    Nodo* aux = lista->inicio; //auxiliar al inicio de lista original

    while(aux!=NULL){ //recorro todos los elementos de la lista
        if(getNodoTipo(aux)==tipoForma) insertarFin(listaForma, getNodoForma(aux), tipoForma); //si coincide la forma almacenada con el parametro tipoForma, lo copio a la nueva lista
        aux = aux->siguiente; //avanzo de elemento
    }
    return listaForma;
}


ListaEnc* crearListaOrdenadaPorColor(ListaEnc* lista){

    ListaEnc* listaOrdenada = crearLista(); //creo una lista auxiliar para ordenar
    Nodo* auxOrig = lista->inicio; //iterador de lista original
    Nodo* auxOrden = listaOrdenada->inicio; //iterador de lista ordenada
    string color;

    while(auxOrig!=NULL){ //hasta que no se termine la lista original

        color = getNodoColor(auxOrig); //tomo el color de cada nodo de mi lista

        while(1){ //loop hasta llegar a un break

            if(color < getNodoColor(listaOrdenada->inicio) || auxOrden == NULL){ //si el color del nodo actual es menor al primer nodo de la lista auxiliar o si la auxiliar esta vacía
                insertarInicio(listaOrdenada, getNodoForma(auxOrig), getNodoTipo(auxOrig)); //inserto al inicio
                break; //salgo del while
            }
            if(getNodoColor(auxOrden->siguiente) > color || auxOrden->siguiente==NULL){ //si es nodo siguiente es tiene color mayor o el siguiente es NULL, le inserto el nodo detrás
                Nodo* nuevoNodo = crearNodo(getNodoForma(auxOrig), getNodoTipo(auxOrig), auxOrden->siguiente); //creo nuevo nodo con datos del auxOrig apuntando al sig nodo
                auxOrden->siguiente = nuevoNodo; //hago apuntar el nodo en el que estaba a nuestro nuevo nodo
                listaOrdenada->tam++;
                break; //salgo del while
            }

            auxOrden = auxOrden->siguiente; //si no se entró en ningun if (es decir, si no se insertó) avanzo de posición
        }

        auxOrig = auxOrig->siguiente; //si ya se insertó el nuevo nodo, paso de elemento en la lista original
        auxOrden = listaOrdenada->inicio; //vuelvo a recorrer la lista nueva desde el inicio para comparar nuevamente

    }

    return listaOrdenada;
}




void copiarLista(ListaEnc* listaOriginal, ListaEnc* listaCopia){

    if(listaOriginal==NULL)return;
    if(listaCopia==NULL)return;

    Nodo* auxO = listaOriginal->inicio;

    //si la listaCopia no esta vacía, la vacío
    while((listaCopia->tam)>0){
        removerInicio(listaCopia,0);
    }

    //copio el contenido de la lista original a la lista copia
    while(auxO != NULL){
        insertarFin(listaCopia, auxO->forma, auxO->tipoForma);
        auxO = auxO->siguiente;
    }
}


void imprimirLista(ListaEnc* lista){
    //recorro los elementos e imprimo cada nodo
    Nodo *aux = lista->inicio;

    if(getListaTamanio(lista)>0){
        cout << (char)175 << " CANTIDAD DE ELEMENTOS: " << getListaTamanio(lista) << "\n" << endl;

        imprimirTabla(encabezado);

        for(int i=0;i<lista->tam;i++){
            mostrarNodo(aux);
            aux = aux->siguiente;
        }

        imprimirTabla(fin);
    }else{
        cout << "< NO HAY ELEMENTOS PARA MOSTRAR >" << endl;
    }
}


void imprimirListaAgruparColor(ListaEnc* lista){

    ListaEnc* auxLista = crearListaOrdenadaPorColor(lista);
    //recorro los elementos e imprimo cada nodo
    Nodo *aux = auxLista->inicio;

    if(getListaTamanio(auxLista)>0){
        cout << (char)175 << " CANTIDAD DE ELEMENTOS: " << getListaTamanio(auxLista) << "\n" << endl;

        //encabezado
        imprimirTabla(encabezado);

        for(int i=0;i<auxLista->tam;i++){
            mostrarNodo(aux);
            if(getNodoColor(aux) != getNodoColor(aux->siguiente) && aux->siguiente){
                imprimirTabla(intermedio);
            }
            aux = aux->siguiente;
        }

        imprimirTabla(fin);
    }else{
        cout << "< NO HAY ELEMENTOS PARA MOSTRAR >" << endl;
    }

    liberarLista(auxLista, false);
}


void imprimirDetalleAreas(ListaEnc* lista){
    //recorro la lista, comparo los nodos y saco menor, mayor y calculo el promedio al final
    cout << setprecision(2) << fixed;
    if(getListaTamanio(lista)==0) return;
    Nodo* aux = lista->inicio;
    float minA=getNodoArea(aux), maxA=0, totalA=0, promA, areaAux;

    while(aux!=NULL){
        areaAux = getNodoArea(aux);
        if(areaAux>maxA) maxA = areaAux;
        if(areaAux<minA) minA = areaAux;
        totalA += areaAux;
        aux = aux->siguiente;
    }
    promA = totalA / getListaTamanio(lista);
    cout << right;
    cout << "Area menor del lote:  " << setw(11) << minA << " cm" << (char)253 << endl;
    cout << "\nArea mayor del lote:  " << setw(11) << maxA << " cm" << (char)253 << endl;
    cout << "\nPromedio de areas:    " << setw(11) << promA << " cm" << (char)253 << endl;
    cout << "\nTotal plastico usado: " << setw(11) << totalA << " cm" << (char)253 << endl;
}


void mostrarNodo(Nodo* n){
    //accedo al entero tipoForma del nodo para saber con que procedimiento mostrar su contenido
    int tipo = n->tipoForma;
    switch (tipo)
    {
        case triangulo:     mostrarTriangulo((Triangulo)n->forma); break;
        case rectangulo:    mostrarRectangulo((Rectangulo)n->forma); break;
        case cubo:          mostrarCubo((Cubo)n->forma); break;
        case circulo:       mostrarCirculo((Circulo)n->forma); break;
        case cilindro:      mostrarCilindro((Cilindro)n->forma); break;
        default:            cout << "Error al mostrar la forma" << endl; break;
    }
}


void imprimirTabla(int n){

    if(n<0 || n>4) return;
    if(n==0){ //CELDAS VACIAS
        cout << (char)179 << "            " << (char)179 << "              " << (char)179 << "            " << (char)179 << "        " << (char)179 << "        " << (char)179 << endl;
    }
    else if(n==1){ //DIVISOR INICIO
        cout << (char)218; for(int i=0;i<12;i++)cout << (char)196; cout << (char)194; for(int i=0;i<14;i++)cout << (char)196; cout << (char)194; for(int i=0;i<12;i++)cout << (char)196; cout << (char)194; for(int i=0;i<8;i++)cout << (char)196; cout << (char)194; for(int i=0;i<8;i++)cout << (char)196; cout << (char)191 << endl;
    }
    else if(n==2){ //DIVISOR INTERMEDIO
        cout << (char)195; for(int i=0;i<12;i++)cout << (char)196; cout << (char)197; for(int i=0;i<14;i++)cout << (char)196; cout << (char)197; for(int i=0;i<12;i++)cout << (char)196; cout << (char)197; for(int i=0;i<8;i++)cout << (char)196; cout << (char)197; for(int i=0;i<8;i++)cout << (char)196; cout << (char)180 << endl;
    }
    else if(n==3){ //DIVISOR FINAL
        cout << (char)192; for(int i=0;i<12;i++)cout << (char)196; cout << (char)193; for(int i=0;i<14;i++)cout << (char)196; cout << (char)193; for(int i=0;i<12;i++)cout << (char)196; cout << (char)193; for(int i=0;i<8;i++)cout << (char)196; cout << (char)193; for(int i=0;i<8;i++)cout << (char)196; cout << (char)217 << endl;
    }
    else if(n==4){ //ENCABEZADO
        imprimirTabla(inicio);
        cout << (char)179 << " FORMA      " << (char)179 << " AREA         " << (char)179 << " COLOR      " << (char)179 << " PARAM1 " << (char)179 << " PARAM2 " << (char)179 << endl;
        imprimirTabla(intermedio);
    }
}




void liberarLista(ListaEnc* lista, bool liberarFormas){
    //elimino el primer elemento hasta que no haya mas elementos
    while((lista->tam)>0){
        removerInicio(lista,liberarFormas);
    }
    delete lista;
    lista = NULL;
}


void liberarNodoForma(Nodo* n){
    //leo el entero tipo para saber con que procedimiento debo destruir aquello a lo que apunta el puntero del nodo
    int tipo = n->tipoForma;
    switch(tipo){
        case triangulo:     destruirTriangulo( (Triangulo)n->forma ); break;
        case rectangulo:    destruirRectangulo( (Rectangulo)n->forma ); break;
        case cubo:          destruirCubo( (Cubo)n->forma ); break;
        case circulo:       destruirCirculo( (Circulo)n->forma ); break;
        case cilindro:      destruirCilindro( (Cilindro)n->forma ); break;
        default:            cout << "Error al liberar forma" << endl; break;
    }
}

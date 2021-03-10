#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm> //Necesario para transform (convertir string a minusculas)
#include <cstdlib>   //Necesario para atof
#include <fstream>   //Necesario para manipular archivos
#include <windows.h> //Necesario para limpiar la consola
#include <iomanip>   //Necesario para formato de decimales y tabulado
#include <conio.h>   //Necesario para pausar

#include "lista.h"
#include "triangulo.h"
#include "rectangulo.h"
#include "cubo.h"
#include "circulo.h"
#include "cilindro.h"

using namespace std;

/*PRE: -
POST: Muestra opciones del menu, devuelve entero correspondiente a la opcion elegida*/
int menu();

/*PRE: -
POST: Muestra opciones del submenu, devuelve entero correspondiente a la opcion elegida*/
int subMenu();

/*PRE: -
POST: Limpia la consola e imprime encabezado*/
void clsEncabezado();

/*PRE: Necesita una lista creada
POST: Lee el txt, separa los datos, los transforma en los atributos necearios para la lista, y los carga en la misma.*/
void leerArchivo(ListaEnc *lista);

/*PRE: Necesita una lista creada
POST: Elimina el contendo de la lista pasada por parametro*/
void vaciarLote(ListaEnc *lista);

/*PRE: Necesita una lista creada
POST: Muestra por pantalla las figuras requeridas*/
void listarFiguras(ListaEnc *lista);

/*PRE: Necesita una lista creada
POST: Muestra por pantalla los totales y subtotales por area*/
void totalesPlastico(ListaEnc *lista);

/*PRE: Necesita una lista creada
POST: Muestra por pantalla la lista con sus elementos ordenada por tamaño de area*/
void figurasPorArea(ListaEnc *lista);

/*PRE: Necesita una lista creada
POST: Muestra por pantalla detalles de totales y areas*/
void estadisticas(ListaEnc *lista);

/*PRE: -
POST: Muestra mensaje de despedida por pantalla*/
void salir();

/*PRE: Requiere dos cadenas de texto que se muestran antes y despues del input
POST: Devuelve un string con el input*/
string leerLineaAnteponerTexto(string antes, string dsps);

/*PRE: Necesita una titulo, un valor y un total sobre el cual sacar porcentaje
POST: Muestra una barra de porcentaje*/
void mostrarPorcentaje(string titulo, int valor, int total);

/*PRE: Necesita un string, y dos float por referencia para guardar los parametros.
POST: Separa los parametros y los guarda en sus respectivas variables (por eso se pide las variables por referencia).*/
void separarParametros(string s,float &p1,float &p2);

/*PRE: Recibe un string que contiene un numero que puede ser decimal escrito con ','
POST: Devuelve el mismo numero como tipo de dato float*/
float stringFloat(string s);



int main() {
    ListaEnc* listaOriginal = crearLista();
    int opcion=-1;
    cout << setprecision(2) << fixed << setfill('.'); //le doy formato a los numeros decimales y al espaciado

    while(opcion!=0){
        clsEncabezado();
        opcion = menu();
        switch(opcion){
            case 1: leerArchivo(listaOriginal); break;
            case 2: vaciarLote(listaOriginal); break;
            case 3: listarFiguras(listaOriginal); break;
            case 4: figurasPorArea(listaOriginal); break;
            case 5: totalesPlastico(listaOriginal); break;
            case 6: estadisticas(listaOriginal); break;
            case 0: salir(); break;
            default: cout << "Opcion incorrecta" << endl; _getch(); break;
        }
    }

    //libero la memoria antes de salir
    liberarLista(listaOriginal,true);
    return 0;
}



int menu(){
    cout << "  1. Cargar lote" << endl;
    cout << "  2. Vaciar lote" << endl;
    cout << "  3. Mostrar en orden de ingreso" << endl;
    cout << "  4. Mostrar ordenado por tama" << (char)164 << "o de areas" << endl;
    cout << "  5. Mostrar totales por figura" << endl;
    cout << "  6. Ver estadisticas" << endl;
    cout << "  0. Salir" << endl;
    cout << "\n     ";

    return _getch() - '0';
}

int subMenu(){
        cout << "  1. Mostrar todas las figuras" << endl;
        cout << "  2. Mostrar solo los triangulos" << endl;
        cout << "  3. Mostrar solo los rectangulos" << endl;
        cout << "  4. Mostrar solo los cubos" << endl;
        cout << "  5. Mostrar solo los circulos" << endl;
        cout << "  6. Mostrar solo los cilindros" << endl;
        cout << "  0. Volver" << endl;
        cout << "\n     ";
        return _getch() - '0';
}

void clsEncabezado(){
    system("cls");
    cout << (char)201 << (char)203 << (char)203 << (char)205 << " PlastiForm " << (char)196 << (char)196 << " articulos plasticos" << endl;
    cout << (char)204 << (char)188 << (char)204 << (char)205 << " Sistema de procesamiento de lotes" << endl;
    cout << (char)186 << " " << (char)186 << "  ";
    for(int i=0;i<33;i++)cout << (char)176;
    cout << "\n" << endl;
}

void leerArchivo(ListaEnc *lista) {
    string nomTxt;
    ifstream archivo;
    int opcion=-1;

    if(getListaTamanio(lista) != 0){
        while(opcion>2 || opcion<0){
            clsEncabezado();
            cout << "  Ya hay un lote cargado, seleccione una opcion:" << endl;
            cout << "  1. Agregar elementos al final del lote existente" << endl;
            cout << "  2. Sobreescribir lote actual" << endl;
            cout << "  0. Volver" << endl;
            cout << "\n     ";
            opcion = _getch() - '0';
            if (opcion == 2){
                liberarLista(lista,true);
                lista = crearLista();
            }
            else if(opcion == 0){
                return;
            }
        }
    }

    clsEncabezado();
    int tamLista = getListaTamanio(lista);
    cout << "Ingrese el nombre del archivo que quiere cargar" << endl;
    cout << "El archivo debera estar en formato .txt dentro de la carpeta 'lotes'\n" << endl;

    nomTxt = leerLineaAnteponerTexto(".../lotes/",".txt");

    nomTxt = "lotes\\" + nomTxt + ".txt";

    archivo.open(nomTxt.c_str());
    if(archivo.fail()){
        cout << "\nERROR: no se pudo abrir el archivo" << endl;
        _getch();
        return;
    }
    string forma,color,parametros;
    float parametro1,parametro2;

    //las siguientes lineas hacen el programa compatible con cualquier codificacion del txt
    //ya que si no es ANSI, el archivo lee simbolos asociados con la codificacion usada
    char c = '-'; //creo un caracter con valor no alfabetico
    while(!isalpha(c)){ //mientras c no sea una letra
        archivo.get(c); //pido un caracter al archivo
    }
    archivo.unget(); //devuelvo la letra detectada al stream para que pueda ser leida nuevamente

    cout << "\nProcesando lote..." << endl;
    while(!archivo.eof()) {
        getline(archivo,forma,' ');
        transform(forma.begin(), forma.end(), forma.begin(), ::tolower);

        getline(archivo,color,' ');
        transform(color.begin(), color.end(), color.begin(), ::tolower);
        //cout << "Color: " << color << endl;
        getline(archivo,parametros,'\n');
        if(parametros.find(';') == string::npos) {
            parametro1= stringFloat(parametros);
        } else {
            separarParametros(parametros, parametro1, parametro2);
        }

        if(forma == "triangulo"){
            Triangulo a = crearTriangulo(parametro1,parametro2,color);
            insertarFin(lista,a,triangulo);
        }
        else if(forma == "rectangulo"){
            Rectangulo b = crearRectangulo(parametro1,parametro2,color);
            insertarFin(lista,b,rectangulo);
        }
        else if(forma == "cubo"){
            Cubo c = crearCubo(parametro1,color);
            insertarFin(lista,c,cubo);
        }
        else if(forma == "circulo"){
            Circulo d = crearCirculo(parametro1,color);
            insertarFin(lista,d,circulo);
        }
        else if(forma == "cilindro"){
            Cilindro e = crearCilindro(parametro1,parametro2,color);
            insertarFin(lista,e,cilindro);
        }
        else{
            cout << "ERROR: se proceso una figura invalida." << endl;
        }
    }
    archivo.close();
    cout << "\nSe han cargado " << getListaTamanio(lista) - tamLista << " elementos.\nPresione cualquier tecla para volver." << endl;
    _getch();
}

void vaciarLote(ListaEnc *lista){
    clsEncabezado();
    if(getListaTamanio(lista)==0){
        cout << "El lote ya esta vacio" << endl;
    }else{
        liberarLista(lista, true);
        lista = crearLista();
        cout << "Se vacio el lote" << endl;
    }
    _getch();
}

void listarFiguras(ListaEnc *lista){
    int opcion = -1;
    char* boollut[2] = {"NO", "SI"};
    bool agruparColor=false;
    while(opcion!=0){
        clsEncabezado();
        cout << "  A. Agrupar por color: " << boollut[agruparColor] << endl;
        cout << endl;
        opcion= subMenu();


        if(opcion==0)return;
        clsEncabezado();

        if(opcion==1){
            if(agruparColor){
                imprimirListaAgruparColor(lista);
            }else{
                imprimirLista(lista);
            }
        }else if(opcion>=1 && opcion<=6){
            ListaEnc* aux = crearListaUnicaForma(lista, opcion-2);
            if(agruparColor){
                imprimirListaAgruparColor(aux);
            }else{
                imprimirLista(aux);
            }
            liberarLista(aux, false);
        }else if(opcion=='A'-'0'||opcion=='a'-'0'){
            agruparColor = !agruparColor; //cambio de estado el booleano
        }else{
            cout << "Opcion incorrecta" << endl;
        }
        if(opcion!='A'-'0'&&opcion!='a'-'0')_getch();
    }
}

void figurasPorArea(ListaEnc *lista){
    int opc = -1;
    char* orden[2] = {"DESCENDENTE", "ASCENDENTE"};
    char* boollut[2] = {"NO", "SI"};
    bool ordenAscendente=false;
    bool agruparColor=false;

    while(opc!=0){
        clsEncabezado();
        cout << "  A. Orden: " << orden[ordenAscendente] << endl;
        cout << "  S. Agrupar por color: " << boollut[agruparColor] << endl;
        cout << endl;
        opc = subMenu();

        if(opc==0)return;
        clsEncabezado();
        if(opc==1){ //si tengo que mostrar todos los elementos
            ListaEnc* aux = crearLista();
            copiarLista(lista, aux); //creo lista auxiliar copiando la original
            ordenarPorArea(aux, ordenAscendente); //la ordeno por area segun el bool ordenAscendente
            if(agruparColor){
                imprimirListaAgruparColor(aux); //si agruparColor==true, la agrupo por color y la muestro
            }else{
                imprimirLista(aux); //sino, la muestro
            }
            liberarLista(aux, false);
        }else if(opc>1&&opc<=6){ //si se elije mostrar una forma en particular
            ListaEnc* aux = crearListaUnicaForma(lista, opc-2); //creo lista auxiliar con la forma elegida
            ordenarPorArea(aux, ordenAscendente); //ordeno lista auxiliar por area segun el bool ordenAscendente
            if(agruparColor){
                imprimirListaAgruparColor(aux); //si agruparColor==true, la agrupo por color y la muestro
            }else{
                imprimirLista(aux); //sino, la muestro
            }
            liberarLista(aux, false);
        }else if(opc=='A'-'0'||opc=='a'-'0'){
            ordenAscendente = !ordenAscendente; //cambio de estado el booleano
        }else if(opc=='S'-'0'||opc=='s'-'0'){
            agruparColor = !agruparColor; //cambio de estado el booleano
        }else{
            cout << "Opcion incorrecta" << endl;
        }
        if(opc!='A'-'0'&&opc!='a'-'0'&&opc!='S'-'0'&&opc!='s'-'0')_getch();
    }
}

void totalesPlastico(ListaEnc *lista){
    int opc = -1;
    char* boollut[2] = {"NO", "SI"};
    bool agruparColor=false;

    while (opc != 0) {
            clsEncabezado();
            cout << "  A. Mostrar subtotales por color: " << boollut[agruparColor] << endl;
            cout << endl;

            opc = subMenu();
            clsEncabezado();
            if(opc==0)return;
            if (opc==1) { //si tengo que mostrar todas las figuras
                for (int i = 0; i < 5; i++) {
                    cout << endl;
                    totalPorFigura(lista, i, agruparColor); //muestro totales de cada figura, agrupo o no por color segun bool
                    cout << endl;
                    cout << i+1 << " de " << "5..." << endl;
                    if(i!=4)_getch();
                }
            }
            else if (opc > 1 && opc <= 6) { //si tengo que mostrar una figura en particular
                totalPorFigura(lista, opc - 2, agruparColor); //muestro totales de esa figura, agrupo o no por color segun bool
            }
            else if(opc=='A'-'0'||opc=='a'-'0'){
                agruparColor = !agruparColor; //cambio de estado el booleano
            }else{
                cout << "Opcion incorrecta" << endl;
            }
            if(opc!='A'-'0'&&opc!='a'-'0')_getch();

    }
}

void estadisticas(ListaEnc *lista){
    int total = getListaTamanio(lista);
    if(total == 0){
        clsEncabezado();
        cout << "El lote esta vacio" << endl;
        _getch();
        return;
    }

    clsEncabezado();
    cout << endl;
    cout << "Cantidad total de figuras: " << total << "\n" << endl;

    for(int i=0; i<38; i++) cout << (char)196; //separador
    cout << "\n" << endl;

    mostrarPorcentaje("Cantidad de triangulos", getListaCantForma(lista, triangulo), total);
    mostrarPorcentaje("Cantidad de rectangulos", getListaCantForma(lista, rectangulo), total);
    mostrarPorcentaje("Cantidad de cubos", getListaCantForma(lista, cubo), total);
    mostrarPorcentaje("Cantidad de circulos", getListaCantForma(lista, circulo), total);
    mostrarPorcentaje("Cantidad de cilindros", getListaCantForma(lista, cilindro), total);
    cout << endl;

    for(int i=0; i<38; i++) cout << (char)196; //separador
    cout << "\n" << endl;

    ListaEnc* listaAux = crearListaOrdenadaPorColor(lista); //creo una lista auxiliar con la lista original ordenada por color
    Nodo* auxN = getListaInicio(listaAux); //creo nodo auxiliar en el inicio de mi nueva lista
    string colorAux; int valorAux;

    while(auxN!=NULL){ //hasta no llegar al final de la lista
        valorAux = getTotalColor(auxN, &colorAux); //recorro la lista hasta que cambia de color, almaceno cantidad de elementos y nombre del color
        mostrarPorcentaje("Formas de color " + colorAux, valorAux, total); //muestro el color y la cantidad de figuras
    }
    cout << endl;
    liberarLista(listaAux, false);

    for(int i=0; i<38; i++) cout << (char)196; //separador
    cout << "\n" << endl;

    imprimirDetalleAreas(lista);
    cout << endl;

    _getch();
}

void salir(){
    clsEncabezado();
    cout << "Gracias por usar nuestro programa\n" << endl;
    cout << "     Abbruzzese Maximiliano\n     Blanco Juan\n     Brieva Lucas\n     Caballero Analia\n     Castro Julian\n" << endl;
    _getch();
}

string leerLineaAnteponerTexto(string antes, string dsps){
    string input; char c='\0';
    dsps.push_back(' '); //agrego espacio para no dejar rastro si se presiona retroceso

    while(isprint(c) || c == '\b' || c == '\0'){ //si es un caracter imprimible, retroceso o nulo, sigo en while
        if(c=='\b' && input.length()>0){
            input.resize(input.size() - 1); //si se presiona retroceso y el input no esta vacio, le quito el ultimo caracter
        }else{
            if(c != '\b' && c!='\0' && input.length()<60) input.push_back(c); //si no es un retroceso o nulo, ingreso el caracter al final del input
        }
        cout << "\r" << antes << input << dsps; //vuelvo el cursor al principio de la linea, imprimo todo concatenado
        for(int i=0; i<dsps.length(); i++)cout << "\b"; //retrocedo hasta despues de la barra '/'
        c = _getch(); //pido el siguiente caracter
    }
    if(!isspace(c))_getch(); //evita problemas de rebote si se presiona por ejemplo una flecha

    return input;
}

void mostrarPorcentaje(string titulo, int valor, int total){
    cout << titulo << ": " << valor << endl;
    int a = 0; float porcentaje;
    if(total==0){
        porcentaje = 0;
    }else{
         a = (valor * 30) / total;
         porcentaje = valor * 100;
         porcentaje = porcentaje / total;
    }
    for(int i=1;i<=a;i++){
        cout << (char)219;
    }
    for(int j=1;j<=(30-a);j++){
        cout << (char)176;
    }
    cout << " " << porcentaje << "%\n" << endl;

}

void separarParametros(string s,float &p1,float &p2) {
    int separador = s.find(';');
    p1=stringFloat(s.substr(0,separador));
    p2=stringFloat(s.substr(separador+1));
}

float stringFloat(string s) {
    if(s.find(',') != string::npos){
        s[s.find(',')] = '.';
    }
    return atof(s.c_str());
}

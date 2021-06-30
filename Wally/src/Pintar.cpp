/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cmath>
#include "Punto2D.h"
#include "miniwin.h"
#include "PoliReg.h"
#include "Pintar.h"
#include <string>
using namespace miniwin;
using namespace std;

/* "Color" es un tipo enumerado definido en Miniwin.h.
Una variable de tipo Color puede tomar los siguientes valores:
NEGRO, ROJO, VERDE, AZUL, AMARILLO, MAGENTA, CYAN, BLANCO

 */
void PintaPunto (const Punto2D& P, Color c) {
    color(c);
    circulo_lleno(P.getX(), P.getY(), RADIO);

}

void PintaPunto (const Punto2D& P, Color c, int radiopunto) {
    color(c);
    circulo_lleno(P.getX(), P.getY(), radiopunto);

}
void PintaLinea(const Punto2D& a, const Punto2D& b, Color c) {
    color(c);
    linea(a.getX(), a.getY(), b.getX(), b.getY());

}

void PintaPoly(const PoliReg & a){
    for(int i = 0; i < a.getNumero(); i++)
               PintaPunto(a.getVertice(i),ROJO);

    PintaLinea(a.getVertice(a.getNumero()-1), a.getVertice(0), BLANCO);
    for (int i = 0; i < a.getNumero()-1;i++)
                PintaLinea(a.getVertice(i), a.getVertice(i+1), BLANCO);
    
}

void PintaPoligono(const PoliReg & a, Color c){
    for(int i = 0; i < a.getNumero(); i++)
               PintaPunto(a.getVertice(i),c);

    PintaLinea(a.getVertice(a.getNumero()-1), a.getVertice(0), c);
    for (int i = 0; i < a.getNumero()-1;i++)
                PintaLinea(a.getVertice(i), a.getVertice(i+1), c);
    
}

void PintarTexto(int posx, int posy, int nro, Color c){
    string cadena = to_string(nro);
    color(c);
    texto(posx, posy, "Numero de puntos: " + cadena);
}

void PintarPuntos(int nro_puntos, Punto2D * basura){
    for (int k = 0; k < nro_puntos; k++){ 
        PintaPunto(basura[k], BLANCO);
    }
}
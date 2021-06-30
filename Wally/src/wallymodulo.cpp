/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <cmath>
#include "Punto2D.h"
#include "PoliReg.h"
void calculoDesplazamiento(float &dx, float&dy, const PoliReg & wally, const Punto2D & destino){
        dx = wally.getCentro().getX() - destino.getX(); //calculamos el movimiento que tendrá el poligono
        dy = wally.getCentro().getY() - destino.getY();
        float modulo = sqrt(dx*dx+dy*dy);
        dx = -dx/modulo;
        dy = -dy/modulo;
}
void GeneraPuntos(int nro_puntos, Punto2D * basura, int RADIOPOLI){
    for (int k = 0; k < nro_puntos; k++){
        basura[k].setX(RADIOPOLI + rand() % (800-2*RADIOPOLI));
        basura[k].setY(RADIOPOLI + rand() % (800-2*RADIOPOLI)); //para que el punto aleatorio se genere entre r y 800-r     
    }
}

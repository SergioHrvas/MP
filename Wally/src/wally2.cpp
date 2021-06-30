/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   wally.cpp
 * Author: sergio
 *
 * Created on 19 de mayo de 2020, 17:45
 */
#include <cmath>
#include "miniwin.h"
#include <iostream>
#include "Punto2D.h"
#include "PoliReg.h"
#include "Pintar.h"
#include "wallymodulo.h"
#include <string>
using namespace miniwin;
using namespace std;
const int RADIOPOLI = 60, CAPACIDAD = 20, DIST_MINIMA = 1;

int main(){
    vredimensiona(800, 800);
    vredimensiona(800, 800);
    srand(time(NULL));
    
    //condiciones iniciales
    int contenido = 0, nro_puntos=200, velocidad;
    Punto2D centro(400, 400);
    PoliReg wally(8, centro, RADIOPOLI); 
    string cadena1, cadena2;  
    Punto2D * basura, *aux;
    basura = new Punto2D [nro_puntos];
    Punto2D destino;
    float dx, dy;
    bool comprobacion, borrando = true;
    GeneraPuntos(nro_puntos, basura, RADIOPOLI);
    
    //Pintamos wally y los puntos
    PintaPoly(wally);
    PintarPuntos(nro_puntos, basura);
   
    while(nro_puntos>0){ 
        
        //asignamos ciertos parámetros en función de si wally está lleno o no
        if(contenido < CAPACIDAD){ 
            destino.setX(RADIOPOLI + rand() % (800-2*RADIOPOLI));
            destino.setY(RADIOPOLI + rand() % (800-2*RADIOPOLI));
            comprobacion = (wally.getCentro().Distancia(destino)>RADIOPOLI&&contenido<CAPACIDAD);
            borrando = true;
            velocidad = 6;
        }
        else {
            destino = centro;
            comprobacion = wally.getCentro().Distancia(destino)>DIST_MINIMA;
            velocidad = 1;
            borrando = false;
            
            //si la distancia al centro es menor o igual que la distancia minima
            //wally se quedará en el centro "vaciando"
            if(!comprobacion){
                 color(BLANCO);
                 texto(380,400,"VACIANDO");
                 refresca();      
                 espera(1000);
                 contenido = 0;
            }
        }
        
        calculoDesplazamiento(dx, dy, wally, destino);
        
        //mientras se cumpla la comprobacion preestablecida y el numero de puntos
        //sea mayor que cero (para que se salga cuando se eliminen todos)
        while(comprobacion&&nro_puntos>0){
            
            wally.Mover(velocidad*dx,velocidad*dy);
            borra();
            
            if (borrando){
                //borramos los puntos que vaya atrapando Wally, solo en la fase de borrado
                for (int k = nro_puntos-1; k >= 0; k--){ 
                    if(wally.EnRango(basura[k]) && contenido < CAPACIDAD && borrando){ 
                        for ( int f = k; f < nro_puntos-1; f++){
                            basura[f]=basura[f+1];
                        }
                        nro_puntos--;
                        contenido++;
                    }
                }       
            }
            
            //Pintamos todo
            PintarTexto(200, 20, nro_puntos, BLANCO);
            PintarTexto(200, 30, contenido, BLANCO);
            PintarPuntos(nro_puntos, basura);
            PintaPoligono(wally, ROJO);
            PintaPunto(destino, VERDE);
            PintaLinea(destino, wally.getCentro(), VERDE);
            refresca();
            espera(10);
                
            //Vuelvo a verificar el contenido para saber si cambio o no la comprobacion dentro del while
            if(borrando)
                comprobacion=(wally.getCentro().Distancia(destino)>RADIOPOLI&&contenido<CAPACIDAD);
            else {
                destino = centro;
                comprobacion=wally.getCentro().Distancia(destino)>DIST_MINIMA;
                calculoDesplazamiento(dx, dy, wally, destino); 
            }
      
        }
    }
    //Pinto un final para cuando se borren todos los puntos
    borra();
    refresca();
    color(AZUL);
    texto(380, 400, "BASURA ELIMINADA!");
    delete [] basura;
}
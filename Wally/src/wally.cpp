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
const int RADIOPOLI = 60, CAPACIDAD = 50, DIST_MINIMA = 1;

int main(){
    vredimensiona(800, 800);
    srand(time(NULL));
    
    //valores iniciales
    int contenido = 0, nro_puntos=400, radiopunto=0;
    Punto2D centro(400, 400);
    PoliReg wally(8, centro, RADIOPOLI);
    string cadena1, cadena2;
    Punto2D * basura, *aux;
    Punto2D PuntoCantidad(400,400);
    basura = new Punto2D [nro_puntos];
    float dx, dy;
    GeneraPuntos(nro_puntos, basura, RADIOPOLI);
    bool NoLleno = contenido < CAPACIDAD;
    bool NoToca;
    bool NoCercaCentro;
    while(nro_puntos>0&&tecla() != ESCAPE){ 
        
        if (NoLleno){
            //genero punto aleatorio y calculo el desplazamiento
            Punto2D destino(RADIOPOLI + rand() % (800-2*RADIOPOLI), RADIOPOLI + rand() % (800-2*RADIOPOLI)); //para que el punto aleatorio se genere entre r y 800-r
            calculoDesplazamiento(dx, dy, wally, destino);
            
            NoToca = wally.getCentro().Distancia(destino)>RADIOPOLI;
            while (NoToca&&NoLleno&&nro_puntos>0){ //el poligono se moverá hasta que toque con el destino
                wally.Mover(5*dx,5*dy);
                PuntoCantidad.Mover(5*dx,5*dy);
                //Borro puntos
                for (int k = nro_puntos-1; k >= 0; k--){ 
                    if(wally.EnRango(basura[k]) && NoLleno){ //borrado de puntos con los que toca con memoria dinámica

                        for ( int f = k; f < nro_puntos-1; f++){
                            basura[f]=basura[f+1];
                        }
                        nro_puntos--;
                        contenido++;
                        //le he puesto este condicional para que el radio del punto jamás se salga del polígono
                        //en caso de que la capacidad sea mayor.
                        if(radiopunto<RADIOPOLI-RADIOPOLI/10){
                        radiopunto++;
                        }
                        NoLleno = contenido < CAPACIDAD;
                        }
                }
                

                //Pinto todo el contenido
                borra();
                PintarTexto(200, 20, nro_puntos, ROJO);
                PintarTexto(200, 30, contenido, AZUL);
                color(BLANCO);
                texto(400, 20, "Pulse ESC para acabar el programa");
                PintaPunto(PuntoCantidad,AZUL,radiopunto);
                PintaPoligono(wally, ROJO);
                PintarPuntos(nro_puntos, basura);
                PintaPunto(destino, VERDE);
                PintaLinea(destino, wally.getCentro(), VERDE);
                refresca();
                espera(40);
                
                //Asigno booleanos
                NoToca = wally.getCentro().Distancia(destino)>RADIOPOLI;

            }
        }

        else{
            calculoDesplazamiento(dx, dy, wally, centro);
            NoCercaCentro = wally.getCentro().Distancia(centro)>DIST_MINIMA;
            //Muevo al centro de la pantalla mientras wally esté lejos de este
            while (NoCercaCentro){ 
                wally.Mover(dx,dy);
                PuntoCantidad.Mover(dx,dy);
                borra();
                PintarPuntos(nro_puntos, basura);
                PintaPunto(PuntoCantidad,AZUL,radiopunto);
                PintaPoligono(wally, ROJO);
                color(BLANCO);
                texto(400, 20, "Pulse ESC para acabar el programa");      
                refresca();
                espera(20);
                NoCercaCentro = wally.getCentro().Distancia(centro)>DIST_MINIMA;     
            }
            //Etapa de vaciado: pinto texto y reseteo contenido

           //Mientras el radio del punto sea mayor que cero va a ir disminiyendo
           //y se va a ver como un "vaciado" en la pantalla
            while (radiopunto>0){
                borra();
                radiopunto--;
                PintaPunto(PuntoCantidad,AZUL,radiopunto);
                PintaPoligono(wally, ROJO);
                PintarPuntos(nro_puntos, basura);
                color(BLANCO);
                texto (380,400,"VACIANDO");
                texto(400, 20, "Pulse ESC para acabar el programa");
                refresca();
                espera(50);

            }
            contenido = 0;

        }
    NoLleno = contenido < CAPACIDAD;
    }
    //Pinto un final para cuando se borren todos los puntos
    borra();
    
    if (nro_puntos==0){
    color(AZUL);
    texto(390, 400, "BASURA ELIMINADA!");
}
    else{
    color(AZUL);
    texto(390, 400, "PROGRAMA FINALIZADO!");
    }
    refresca();
    delete [] basura;
    
    return 0;
}
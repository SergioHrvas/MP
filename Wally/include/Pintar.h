/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pintar.h
 * Author: sergio
 *
 * Created on 1 de mayo de 2020, 11:22
 */

#ifndef PINTAR_H
#define PINTAR_H
#include "miniwin.h"
#include "PoliReg.h"
const int RADIO = 5;
const int MIN_X=800, MIN_Y=800;

using namespace miniwin;
void PintaPunto (const Punto2D& P, Color c);
void PintaLinea(const Punto2D& a, const Punto2D& b, Color c);
void PintaPoly(const PoliReg & a);
void PintaPoligono(const PoliReg & a, Color c);
void PintarTexto(int posx, int posy, int nro, Color c);
void PintarPuntos(int nro_puntos, Punto2D * basura);
void PintaPunto (const Punto2D& P, Color c, int radiopunto);
#endif /* PINTAR_H */


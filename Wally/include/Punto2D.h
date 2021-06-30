/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   punto.h
 * Author: sergio
 *
 * Created on 30 de abril de 2020, 20:02
 */

#ifndef PUNTO_H
#define PUNTO_H
#include <iostream>
using namespace std;

class Punto2D{
private:
    float x, y;
public:
    Punto2D();
    Punto2D(float x, float y);
    float getX () const;
    float getY() const;
    void setX(float x);   
    void setY(float y);
    float Distancia(const Punto2D & otro) const;
    void rotar(const Punto2D &centro, double rads);
    void Mover (float dx, float dy);
};

ostream& operator<<(ostream &flujo, const Punto2D & punto);
#endif /* PUNTO_H */


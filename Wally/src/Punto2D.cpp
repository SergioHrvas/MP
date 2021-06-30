/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <cmath>

using namespace std;
#include "Punto2D.h"
#include "Pintar.h"


float Punto2D::getX() const{
    return x;
};

float Punto2D::getY() const{
    return y;
};

void Punto2D::setX (float x) {
    this->x=x;
};

void Punto2D::setY(float y){
    this->y=y;
};

Punto2D::Punto2D(float x, float y){
    setX(x);
    setY(y);
}

Punto2D::Punto2D(){
    setX(rand() % MIN_X);
    setY(rand() % MIN_Y);

}

float Punto2D:: Distancia(const Punto2D & otro) const{
    float distancia = sqrt(pow((otro.getX()-this->getX()),2)+pow((otro.getY()-this->getY()),2));
    return distancia;
}

void Punto2D:: rotar(const Punto2D &centro, double rads) {
    double deltaX = this->getX() - centro.getX();
    double deltaY = this->getY() - centro.getY();
    
    this->setX(centro.getX() + deltaX * cos(rads) - deltaY * sin(rads));
    this->setY(centro.getY() + deltaX * sin(rads) + deltaY * cos(rads));

}

void Punto2D:: Mover(float dx, float dy){
    this->setX(this->getX()+dx); //muevo la coordenada x
    this->setY(this->getY()+dy); //muevo la coordenada y
}

ostream& operator<<(ostream &flujo, const Punto2D & punto){
        flujo << "(" << punto.getX() << "," << punto.getY() << ") ";
}
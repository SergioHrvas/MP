/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
using namespace std;
#include <cmath>
#include "Punto2D.h"
#include "PoliReg.h"

const float PoliReg::MAX_RADIO=150;
const float PoliReg::MIN_RADIO = 15;
const int PoliReg::MAX_VERT = 200;
const int PoliReg::MIN_VERT = 3;


void PoliReg::setRadio(float radio){
    if (radio < MIN_RADIO || radio > MAX_RADIO)
        this->radio=MIN_RADIO;  
    else
        this->radio=radio;
}

void PoliReg::setNumero(int N){
    if(N >= MIN_VERT || N <= MAX_VERT)
        this->N=N;
    else{
        this->N=MIN_VERT;
    }
}

void PoliReg::setCentro(Punto2D centro){
    this->centro=centro;
}

PoliReg::PoliReg(int N,  const Punto2D &centro, float radio){

    this->setRadio(radio);
    this->setCentro(centro);
    this->setNumero(N);
    ReservaMemoria();
    GeneraVertices();
}   

PoliReg::PoliReg(){
    this->setRadio(MIN_RADIO);
    this->setNumero(MIN_VERT);
    centro.setX(0);
    centro.setY(0);

    ReservaMemoria();
    GeneraVertices();
}

void PoliReg::AgregaVertice(){

    if(N<MAX_VERT){ //comprobacion para evitar que supere el maximo de vertices
        this->setNumero(N+1);
        ActualizarMemoria();
    
    }
}

void PoliReg::ActualizarMemoria(){
    
        LiberaMemoria(); //reconstruimos el poligono
        ReservaMemoria();
        GeneraVertices();
    
}

void PoliReg::EliminaVertice(){

    if(N>MIN_VERT){ //comprobacion para evitar que sea inferior al minimo de vertices
        this->setNumero(N-1);
        ActualizarMemoria();
    
    }
}
void PoliReg::GeneraVertices(){
    float angulo = 360/this->getNumero(); 
    angulo = angulo * M_PI / 180; //hallamos el angulo en radianes entre los vertices

    vertices[0].setX(radio+centro.getX()); //generamos el primer vertice
    vertices[0].setY(centro.getY());
    
    for (int k = 1; k < this->getNumero(); k++){ //generamos los demás vertices respecto al primero
        vertices[k] = vertices[0];
        vertices[k].rotar(centro,angulo*k);
    }
}
Punto2D PoliReg::getVertice(int nro) const{
    if(nro>=0 && nro<=N){
        return vertices[nro];
    }
}

Punto2D PoliReg::getCentro() const{
    return(centro);
}

int PoliReg::getNumero() const{
    return(N);
}

float PoliReg::getRadio() const{
    return(radio);
}

void PoliReg::ReservaMemoria(){

      vertices = new Punto2D[N];
      
}

void PoliReg::LiberaMemoria(){
          if (vertices != 0){
              delete []vertices;
              vertices=0;
          }
}

void PoliReg::Expande(int pct){
    if (pct > 0)
    CambiarRadio(pct);
}

void PoliReg::Contrae(int pct){
    if (pct > 0)
    CambiarRadio(-pct);

}

void PoliReg:: CambiarRadio(int pct){

        float extra = (this->getRadio() * pct / 100); //calculamos la medida que queramos cambiar al radio
        
        if (radio+extra<=MAX_RADIO&&radio+extra>=MIN_RADIO){
            this->setRadio(radio + extra);   //sumamos(o restamos si contrae) esa medida al radio.
            GeneraVertices();
        }

}

double PoliReg::Perimetro() const{
    double perimetro = getVertice(0).Distancia(getVertice(1))*N;
    return perimetro;
}

void PoliReg::Rotar(double rads){
    for ( int k = 0; k < N ; k++){
        vertices[k].rotar(centro, rads); //rotamos vertice a vertice llamando al metodo de la clase punto.
    }
}

bool PoliReg::Colision(const PoliReg& otro) const{
    
    bool comprobacion = false;
    
    if(this!=&otro){ //controlamos que sean distintos poligonos
        double dist_centros = this->getCentro().Distancia(otro.getCentro());
        double suma_radios = this->getRadio()+otro.getRadio();
        if(dist_centros <= suma_radios){ //comprobamos si la distancia entre los centros es menor que la suma de sus radios
                                        //para ver si colisionan o no
            comprobacion = true;
        }
    }
    return comprobacion;
    
}

PoliReg::~PoliReg(){
    LiberaMemoria();
}

void PoliReg::Mover(float dx, float dy){
    centro.Mover(dx, dy); //Movemos el centro

    for ( int k = 0; k < getNumero(); k++){
        vertices[k].Mover(dx, dy); //Movemos todos los vertices
    }
}

PoliReg::PoliReg(const PoliReg & copia){
    CopiarPoligono(copia);
    
}

void PoliReg::copiarPuntos(const PoliReg & copia){
    for (int k = 0; k < N ; k++){
        vertices[k]=copia.getVertice(k);
    }
}


void PoliReg::operator=(const PoliReg & copia){
    LiberaMemoria();
    CopiarPoligono(copia);
    
}

void PoliReg::CopiarPoligono(const PoliReg & copia){
    N=copia.getNumero();
    centro=copia.getCentro();
    radio=copia.getRadio();
    ReservaMemoria();
    copiarPuntos(copia);
}

ostream& operator<<(ostream &flujo, const PoliReg & poli){
    flujo << "Polig. de " << poli.getNumero() << " puntos. Centro: (" << poli.getCentro().getX() <<
            ", " << poli.getCentro().getY() << ")  Perim: " << poli.Perimetro() <<
            endl << "Puntos: ";
    for (int k = 0; k < poli.getNumero(); k++){
        flujo << poli.getVertice(k);
    }
    flujo << endl;
}

bool PoliReg::operator<(const PoliReg & otro) const{
    bool comprobacion = false;
    if (Perimetro()<otro.Perimetro())
        comprobacion=true;
    
    return comprobacion;
}

bool PoliReg::EnRango(const Punto2D & pto){
    bool comprobacion = false;
    float distancia = centro.Distancia(pto);
    if (distancia < radio){
        comprobacion=true;
    }
    return comprobacion;
}
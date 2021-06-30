/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PoliReg.h
 * Author: sergio
 *
 * Created on 4 de mayo de 2020, 23:54
 */

#ifndef POLIREG_H
#define POLIREG_H
#include <iostream>
using namespace std;
class PoliReg{
private:
    Punto2D *vertices;
    int N;
    Punto2D centro;
    float radio;
    static const int MAX_VERT;
    static const int MIN_VERT;
    static const float MAX_RADIO;
    static const float MIN_RADIO;
    void setRadio(float radio);
    void setNumero(int N);
    void setCentro(Punto2D centro);
    void ReservaMemoria();
    void LiberaMemoria();
    void GeneraVertices();
    void CambiarRadio(int pct);
    void copiarPuntos(const PoliReg & copia);
    void CopiarPoligono(const PoliReg & copia);
    void ActualizarMemoria();
public:
    

    PoliReg();
    PoliReg(const PoliReg & copia);
    PoliReg(int N,  const Punto2D &centro, float Radio);
    float getRadio() const;
    int getNumero() const;
    Punto2D getCentro() const;
    void AgregaVertice();
    void EliminaVertice();
    void Expande(int pct);
    Punto2D getVertice(int nro) const;
    void Contrae(int pct);
    double Perimetro() const;
    void Rotar(double rads);
    bool Colision(const PoliReg & otro) const;
    ~PoliReg();
    void Mover(float dx, float dy);
    void operator=(const PoliReg & otro);
    bool operator<(const PoliReg & otro) const;
    bool EnRango(const Punto2D & pto);
};

ostream& operator<<(ostream &flujo, const PoliReg & poli);

#endif /* POLIREG_H */


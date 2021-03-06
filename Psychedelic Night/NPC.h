/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.h
 * Author: rizado
 *
 * Created on May 1, 2017, 11:31 AM
 */

#ifndef NPC_H
#define NPC_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "SpriteGame.h"
#include "Motor2D.h"
#include "Bala.h"


using namespace std;
using namespace sf;

class NPC {
public:
    NPC(int tipo, int posX, int posY);
    NPC(const NPC& orig);
    virtual ~NPC();
    void nextSprite(int contadorVueltas);
    void posicionAleatoria();
    void movMosquito();
    void movTopo(Time tiempo, int cont_vueltas);
    void dibujarEnemigo();
    int getX();
    int getY();
    void DisparoEnemigo(Clock clockbala);
    void ActualizarDisparo();
    vector<Bala*>  GetBala();
    void pintarDisparo();
    void accionesEnemigo(Clock reloj2, Time tiempo);
    int getTipo();
    int getPosMatrix_x();
    int getPosMatrix_y();
    int getAnchoSprite();
    int getAltoSprite();
    void colisionPersonaje();
    void colisionBalasPersonaje();
    void quitarVida(int herida);
    int getVida();
    void posicionAnterior();
    
private:
    int tipo;
    int vida;
    int velocidad;
    SpriteGame **enemy;
    Sprite **enemigo;
    int num_sprites;
    int cambio_sprite;
    int numCambio;
    int contadorvueltas;
    Texture *textura1;
    
    float angle;
    int retraso;
    
    vector <Bala*>* balas;
    int dispara;
    int velx;
    float rangoDisparo ; 
    
    int posMatrix_x;
    int posMatrix_y;
    
    float ancho;
    float alto;
    
    bool colision;
    int cont_colision;
    
    int posicion_actual_x;
    int posicion_actual_y;
    int posicion_anterior_x;
    int posicion_anterior_y;
    

};

#endif /* NPC_H */


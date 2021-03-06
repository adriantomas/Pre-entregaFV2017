/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nivel.h
 * Author: drmonkey
 *
 * Created on 29 de marzo de 2017, 12:56
 */

#ifndef NIVEL_H
#define NIVEL_H
#include "Planta.h"
#include <string>
#include "Mapa.h"
#include "Coordenada.h"
#include "NPC.h"
#include "Modificador.h"
#include "Boss.h"

using namespace std;

class Nivel {
public:
    Nivel();
    Nivel(unsigned int sem);
    Nivel(const Nivel& orig); 
    virtual ~Nivel();
    void aumentanivel();
    string getSemilla();
    void imprimir();
    void dibujarNivel();
    int getNivel();
    bool **getVisitadas();
    void visitar(int i, int j);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void actualizar(sf::Clock cl, sf::Time tim);
    void colisionBalasEnemigo();
    void colisionEntreNPC();
    void colisionBalasBoss();
    int** getMatriz();
    int colisionPuertas(int x, int y);
    bool colisionHabitacion(int x, int y);
    int obtenerHab(int x , int y);
    bool enemigosVivos();
    void limpiarHab();
private:
    int n; //Nivel
    string semilla;
    int num;
    Planta *pl;
    Mapa *mapa;
    Modificador *tesoro;
    Boss *boss;
    bool **visitadas;
    void crearMapa();
    int posx; //Posicion del jugador en la matriz de mapas
    int posy;
    bool cambio;
    vector<NPC*>* vectorenemigos;
    sf::Sprite *trampilla;
    sf::Texture tex;
};

#endif /* NIVEL_H */


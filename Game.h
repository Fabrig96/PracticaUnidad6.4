#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "Crosshair.h"
#include "Objetivo.h"
#include "SistemaPuntaje.h"

using namespace sf;
using namespace std;

//Esta clase representa a Game con sus respectivos metodos
class Game {

private:

    int alto;
    int ancho;
    RenderWindow* wnd;
    Crosshair* crosshair;
    Objetivo* objetivo;
    SistemaPuntaje* sistemPuntaje;
    Time timerMax;
    Time timer;
    Clock clock;
    bool objetivoVisible;

    //Proceso de eventos
    void procesarEventos(Event& evt) {
        switch (evt.type) {
            case Event::Closed:
                wnd->close();
                break;
            case Event::MouseMoved:
                crosshair->apuntar((float)evt.mouseMove.x, (float)evt.mouseMove.y);
                break;
            case Event::MouseButtonPressed:
                if (evt.mouseButton.button == Mouse::Button::Left) {
                    disparar();
                }
        }
    }

    //Dibujar objetos del juego
    void dibujarJuego() {
      
        sistemPuntaje->dibujar(wnd);
        objetivo->dibujar(wnd);
        crosshair->dibujar(wnd);
    }

    //Actualizacion del juego
    void actualizarJuego() {

        if (!sistemPuntaje->gameOver()) {
            objetivo->actualizar();
        }
        sistemPuntaje->HUD();      
    }

    //Metodo que permite disparar a un objetivo
    void disparar() {
        Vector2f crosshairPos = crosshair->getPos();

        if (!sistemPuntaje->gameOver()) {
            if (objetivo->enLimites(crosshairPos.x, crosshairPos.y)) {
                sistemPuntaje->disparoEfectivo();
                resetTimer();
            }                      
        }
    }

    //Metodo que resetea el movimiento y posicion del objetivo aleatoriamente
    void resetTimer() {
       
        objetivo->reiniciarMovimiento();
        objetivo->posicionAleatoria();       
    }

public:

    Game(String titulo) {
        ancho = 1024;
        alto = 768;
        wnd = new RenderWindow(VideoMode(ancho, alto, 32), titulo);
        wnd->setMouseCursorVisible(false);
        wnd->setFramerateLimit(60);
        crosshair = new Crosshair();
        objetivo = new Objetivo();
        sistemPuntaje = new SistemaPuntaje();
        srand(static_cast<unsigned>(time(nullptr)));
        resetTimer();
    }

    ~Game() {
        delete wnd;  
        delete crosshair;
        delete objetivo;
        delete sistemPuntaje;
    }
    
    //Ejecucion del juego
    void ejecutar() {
        Event evt;

        while (wnd->isOpen()) {
            while (wnd->pollEvent(evt))
                procesarEventos(evt);

            actualizarJuego();
            wnd->clear();
            dibujarJuego();
            wnd->display();
        }
    }

};
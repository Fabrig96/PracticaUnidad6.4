#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

class Objetivo {
private:

    Sprite sprite;
    Texture texture;
    Clock clock;
    bool vivo;
    bool salida;
    float velocidad;
    float aceleracion;
    Vector2f velocidadInicial;
    Vector2f posicionInicial;

public:

    Objetivo() {
        texture.loadFromFile("Assets/obj-ball.png");
        sprite.setTexture(texture);
        sprite.setScale(0.15f, 0.15f);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

        velocidadInicial = Vector2f(400.0f, 0.0f);
        velocidad = velocidadInicial.x;
        aceleracion = 250.0f;
        posicionInicial = Vector2f(0.0f, 300.0f);
        sprite.setPosition(posicionInicial);
        vivo = true;
        salida = false;
    }
    
    //Dibuja el objetivo
    void dibujar(RenderWindow* wnd) {
        wnd->draw(sprite);
    }

    //Posiciona aletoriamente el sprite en el eje X de la ventana
    //Tambien osiciona aleatoriamente de lado izquierdo o derecho del  la ventana
   void posicionAleatoria() {
        
       int posicion = rand()  % (500 - 50  +1 ) + 50 ;
        
       bool init = rand() % 2 == 0;
       if (init) {

          sprite.setPosition(0, (float)posicion);
          salida = true;
       }
       else {
          sprite.setPosition(1024, (float)posicion);
          salida = false;
       }

    }

   //Actualiza el objetivo
   //Setea una nueva posición izquierda o derecha de la ventana
   //Implementación de movimiento MRU y MRUV 
    void actualizar() {
       
        float deltaTime = clock.restart().asSeconds();
        cout << velocidadInicial.x << endl;
        Vector2f nuevaPosicion;

        if (salida) {
            nuevaPosicion = sprite.getPosition() + velocidadInicial * deltaTime;
        }
        else {
             nuevaPosicion = sprite.getPosition() - velocidadInicial * deltaTime;
        }
        velocidad += aceleracion * deltaTime;
        velocidadInicial.x = velocidad;
        sprite.setPosition(nuevaPosicion);
        velocidadInicial.x = velocidad;

        if (sprite.getPosition().x > 1024.0f || sprite.getPosition().x < 0.0f) {
            reiniciarMovimiento();
            posicionAleatoria();
        }
    }

    //Reinicia velocidad inicial y velocidad con velocidadInicial
    void reiniciarMovimiento() {
        velocidadInicial.x = 400;
        velocidad = velocidadInicial.x;
    }

    //Determina si coordenadas X/Y se encuentran dentro de los límites del sprite
    bool enLimites(float x, float y) {
        FloatRect limits = sprite.getGlobalBounds();
        return limits.contains(x, y);
    }

};

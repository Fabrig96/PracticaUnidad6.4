#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//Clase que representa a Crosshair del juego
class Crosshair {

	Texture crossh_tex;
	Sprite crossh_sprite;

public:

	Crosshair() {

		crossh_tex.loadFromFile("Assets/crosshair.png");
		crossh_sprite.setTexture(crossh_tex);
		crossh_sprite.setScale(0.35f, 0.35f);
		crossh_sprite.setOrigin(crossh_tex.getSize().x / 2.0f, crossh_tex.getSize().y / 2.0f);

	}

	//Apuntar la mira sobre una coordenada
	void apuntar(float x, float y) {
		crossh_sprite.setPosition(x, y);
	}

	//Dibujar mira
	void dibujar(RenderWindow* wnd) {
		wnd->draw(crossh_sprite);
	}

	//Obtener posicion actual de la mira
	Vector2f getPos() {
		return crossh_sprite.getPosition();
	}

};
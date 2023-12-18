#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

//Clase que representa al Sistema de Puntaje y sus respectivos metodos
class SistemaPuntaje {

private:

	Texture logotx;
	Sprite logoSp;
	Font fuente;
	Text labelPuntaje;
	Text labelEnemigosElim;
	Text puntajeH;
	Text enemigosElim;
	Text resultadoTitle;
	int enemigosAbatidos;
	int puntaje;
	bool finished;
	Clock tiempoDisparoEnemigo;

public:

	SistemaPuntaje() {

		enemigosAbatidos = 0;
		puntaje = 0;
		finished = false;

		if (!logotx.loadFromFile("Assets/logo.png")) {
			cerr << "Error al cargar logo" << endl;
		}

		logoSp.setTexture(logotx);
		logoSp.setScale(0.45f, 0.45f);
		logoSp.setOrigin(logotx.getSize().x / 2.0f, logotx.getSize().y / 2.0f);
		
		if (!fuente.loadFromFile("Assets/RobotoCondensed-Bold.ttf")) {
			cerr << "Error al cargar la fuente" << endl;
		}

		labelPuntaje.setFont(fuente);
		labelPuntaje.setString("Completó el máximo de eliminaciones con éxito");
		labelPuntaje.setCharacterSize(40);
		labelPuntaje.setFillColor(Color::Green);
		labelPuntaje.setPosition(-100, -100);
		labelEnemigosElim.setFont(fuente);
		labelEnemigosElim.setString("Objetivos eliminados: ");
		labelEnemigosElim.setCharacterSize(40);
		labelEnemigosElim.setFillColor(Color::Green);

		puntajeH.setFont(fuente);
		puntajeH.setString(to_string(puntaje));
		puntajeH.setCharacterSize(40);
		puntajeH.setFillColor(Color::Cyan);
		puntajeH.setPosition(-100, -100);
		enemigosElim.setFont(fuente);
		enemigosElim.setString(to_string(enemigosAbatidos));
		enemigosElim.setCharacterSize(40);
		enemigosElim.setFillColor(Color::Cyan);

		resultadoTitle.setFont(fuente);
		resultadoTitle.setCharacterSize(60);
		resultadoTitle.setFillColor(Color::Magenta);
		resultadoTitle.setPosition(-100, -100);

	}

	//Setea el HUD del juego
	void HUD() {
		
		logoSp.setPosition(140, 640);
		labelEnemigosElim.setPosition(520, 600);
		enemigosElim.setPosition(885, 600);
	}

	//Aumenta puntaje y objetivos eliminados por medio de un disparo efectivo
	void disparoEfectivo() {
		enemigosAbatidos += 1;
		puntaje = enemigosAbatidos;
		puntajeH.setString(to_string(puntaje));
		enemigosElim.setString(to_string(enemigosAbatidos));
	}

	//Verificar si finaliza el juego y setear HUD game over
	bool gameOver() {
		resultadoTitle.setPosition(360, 600);
		
		if (enemigosAbatidos == 20) {
			cout << "GAME OVER" << endl;
			resultadoTitle.setString("GAME OVER!");
			labelPuntaje.setPosition(130, 670);
			puntajeH.setPosition(490, 710);
			finished = true;
		}

		return finished;
	}

	//Dibujar HUD sistema de puntaje
	void dibujar(RenderWindow* wnd) {

		if (!gameOver()) {
			wnd->draw(labelEnemigosElim);		
			wnd->draw(enemigosElim);
			wnd->draw(logoSp);
		}
		wnd->draw(resultadoTitle);
		wnd->draw(labelPuntaje);
		wnd->draw(puntajeH);
	}

};
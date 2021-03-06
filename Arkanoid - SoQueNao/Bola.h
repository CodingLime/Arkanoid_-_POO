#pragma once
#include <SFML\Graphics.hpp>
#include "Circulo.h"

using namespace sf;
using FrameTime = float;

class Bola :
	public Circulo
{
public:

	float velocidadebola = 0.4f;
	Vector2f velocidade { -getvelocidadebola(), -getvelocidadebola() };
	bool fimjogo = false;

	float getvelocidadebola();
	void setvelocidadebola(float X);
	void resetVelocidade();
	
	Bola(float mX, float mY);
	~Bola();
	
	void resetPosicao(float x, float y);
	void update(FrameTime mFT);
	float const raioBola();
};




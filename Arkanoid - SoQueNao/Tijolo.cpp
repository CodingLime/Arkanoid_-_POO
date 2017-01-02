#include "Tijolo.h"
#include <iostream>

//int pontuacao = 0;

float Tijolo::larguraTijolo()
{
	return float(round(larguraJanela - larguraJanela*0.922));
}

float Tijolo::alturaTijolo()
{
	return float (round(alturaJanela - alturaJanela*0.94));
}

int Tijolo::nTijolosX()
{
	return 11;
}

int Tijolo::nTijolosY()
{
	return 4;
}

void Tijolo::setPowerUp()
{
	Powerup = true;
}



Tijolo::Tijolo(float mX, float mY)
{
	forma_req.setPosition(mX, mY);
	forma_req.setSize({ larguraTijolo(), alturaTijolo() });
	forma_req.setFillColor(sf::Color::Black);
	forma_req.setOutlineColor(sf::Color::Magenta);
	forma_req.setOutlineThickness(2);
	forma_req.setOrigin(larguraTijolo() / 2.f, alturaTijolo() / 2.f);
}





void testeColisao(Barra & mbarra, Bola & mbola)
{
	if (!Intersecao(mbarra, mbola)) return;

	mbola.velocidade.y = -mbola.getvelocidadebola();
	if (mbola.x() < mbarra.x())
		mbola.velocidade.x = -mbola.getvelocidadebola();
	else
		mbola.velocidade.x = mbola.getvelocidadebola();
}

void testeColisao(Tijolo & mTijolo, Bola & mbola, vector<powerup>& mpowerup, Pontuacoes& G_pontuacao)
{
	if (!Intersecao(mTijolo, mbola)) return;
	G_pontuacao.adicionarpontuacao(1);
	mTijolo.destruido = true;
	// se bool powerup true alterar velocidade powerup
	
	if (mTijolo.Powerup == true)
	{		
		FloatRect tBox = FloatRect(Vector2f(mTijolo.x(), mTijolo.y()), Vector2f(mTijolo.larguraTijolo(), mTijolo.alturaTijolo()));
		// precurer vector mpowerup
		for(vector<powerup>::iterator it = mpowerup.begin(); it != mpowerup.end() ; it++)
			if (tBox.contains(Vector2f((*it).x(), (*it).y()))) {
				(*it).setVelocidadeP(0, 0.4f);
			}
	}
	float sobreporEsquerda{ mbola.direita() - mTijolo.esquerda() };
	float sobreporDireita{ mTijolo.direita() - mbola.esquerda() };
	float sobreporCima{ mbola.baixo() - mTijolo.cima() };
	float sobreporBaixo{ mTijolo.baixo() - mbola.cima() };

	bool bolaFromesquerda(abs(sobreporEsquerda) < abs(sobreporDireita));
	bool bolaFromcima(abs(sobreporCima) < abs(sobreporBaixo));

	float minsobreporX{ bolaFromesquerda ? sobreporEsquerda : sobreporDireita };
	float minsobreporY{ bolaFromcima ? sobreporCima : sobreporBaixo };

	if (abs(minsobreporX) < abs(minsobreporY))
		mbola.velocidade.x = bolaFromesquerda ? -mbola.getvelocidadebola() : mbola.getvelocidadebola();
	else
		mbola.velocidade.y = bolaFromcima ? -mbola.getvelocidadebola() : mbola.getvelocidadebola();
}

void testeColisao(Barra & mbarra, powerup & mPower, Pontuacoes& mpontos)
{
	if (!Intersecao(mPower, mbarra)) return;

	mpontos.adicionarpontuacao(mPower.getScore());
}

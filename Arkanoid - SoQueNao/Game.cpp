#include "game.h"
#include <vector>
#include <iostream>
extern int pontuacao;

Game::Game()
{
	// On construction, we initialize the window and create
	// the brick wall. On a more serious implementation, it
	// would be a good idea to have a `newGame()` method that
	// can be called at any time to restart the Jogo.

	//window.setFramerateLimit(240); // parece n�o ser necessario para funcionar, remover no fim de tudo

	font.loadFromFile("black.ttf");

	//Texto de Score
	texto.setFont(font);
	texto.setCharacterSize(35);
	texto.setFillColor(Color::White);
	texto.setPosition(float(larguraJanela) - 185, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela
	texto.setString("SCORE:");

	//valor pontuacao
	mostraPontuacao.setFont(font);
	mostraPontuacao.setFillColor(Color::White);
	mostraPontuacao.setCharacterSize(35);
	mostraPontuacao.setPosition(float(larguraJanela) - 55, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela

	//Fim do jogo
	fimdoJogo.setFont(font);
	fimdoJogo.setCharacterSize(20 * (larguraJanela * 0.001));
	fimdoJogo.setPosition(alturaJanela / 2, larguraJanela / 2);
	fimdoJogo.setFillColor(sf::Color::White);
	fimdoJogo.setString("Perdeste buahaha, carrega 'Q' para fechar");

	//Texto de VelBola
	txtBola.setFont(font);
	txtBola.setCharacterSize(35);
	txtBola.setFillColor(Color::White);
	txtBola.setPosition(5, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela
	txtBola.setString("Velocidade:");

	//valor Velocidade
	mostraVel.setFont(font);
	mostraVel.setFillColor(Color::White);
	mostraVel.setCharacterSize(35);
	mostraVel.setPosition(205, float(alturaJanela) - 50); // Posição do score fica consoante o tamanho da janela
	string vel = to_string(bola.getvelocidadebola());
	mostraVel.setString(vel);

	for (int iX{ 0 }; iX < tijolo.nTijolosX(); ++iX)
		for (int iY{ 0 }; iY < tijolo.nTijolosY(); ++iY)
			Tijolos.emplace_back((iX + 1) * (tijolo.larguraTijolo() + 3) + 22, (iY + 2) * (tijolo.alturaTijolo() + 3));
}

void Game::menu()
{
	auto timePoint1(chrono::high_resolution_clock::now());

	window.clear(Color::Black);

	Text play, bot, score, quit;
	Font font;
	font.loadFromFile("black.ttf");

	play.setFont(font);
	play.setCharacterSize(80 * (larguraJanela * 0.001));
	play.setFillColor(Color::White);
	play.setPosition(larguraJanela / 10, alturaJanela / 4 + (alturaJanela * 0.01));
	//play.setPosition(larguraJanela / 2 - (larguraJanela * 0.1), alturaJanela / 4 + (alturaJanela * 0.01));
	play.setString("[P]lay");

	bot.setFont(font);
	bot.setCharacterSize(80 * (larguraJanela * 0.001));
	bot.setFillColor(Color::White);
	bot.setPosition(larguraJanela / 10, alturaJanela / 2 - (alturaJanela * 0.1));
	//bot.setPosition(larguraJanela / 2 - (larguraJanela * 0.1), alturaJanela / 2 - (alturaJanela * 0.1));

	bot.setString("[B]ot - falta");

	score.setFont(font);
	score.setCharacterSize(80 * (larguraJanela * 0.001));
	score.setFillColor(Color::White);
	score.setPosition(larguraJanela / 10, alturaJanela - (alturaJanela * 0.46));
	//score.setPosition(larguraJanela / 2 - (larguraJanela * 0.1), alturaJanela - (alturaJanela * 0.46));

	score.setString("[S]core - falta");

	quit.setFont(font);
	quit.setCharacterSize(80 * (larguraJanela * 0.001));
	quit.setFillColor(Color::White);
	quit.setPosition(larguraJanela / 10, alturaJanela - (alturaJanela * 0.2));
	//quit.setPosition(larguraJanela / 2 - (larguraJanela * 0.1), alturaJanela - (alturaJanela * 0.2));

	quit.setString("[Q]uit");

	auto timePoint2(chrono::high_resolution_clock::now());
	auto elapsedTime(timePoint2 - timePoint1);
	FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(
		elapsedTime)
		.count() };

	lastFt = ft;

	auto ftSeconds(ft / 1000.f);
	auto fps(1.f / ftSeconds);

	window.draw(play);
	window.draw(bot);
	window.draw(score);
	window.draw(quit);
	window.display();
}

void Game::classificacao()
{
	auto timePoint1(chrono::high_resolution_clock::now());

	window.clear(Color::Black);
	vector<pair<Text, int>> Stringjogadores;
	vector<pair<Text, int>> Stringpontuacao;
	vector<Int16> inputpontuacaoJogadores;
	vector<int> pontuacaoJogadores;
	vector<Text> nomeJogadores;

	for (size_t i = 0; i < nomeJogadores.size(); i++)
	{
		if (Stringjogadores.size() <= i)
		{
			pair<Text, int> novoJogador;
			Text SnovoJogador;
			SnovoJogador.setString(nomeJogadores[i].getString());
			SnovoJogador.setCharacterSize(15);
			novoJogador.first = SnovoJogador;
			novoJogador.second = inputpontuacaoJogadores[i];
			Stringjogadores.push_back(novoJogador);

	Text titulo;

			//se nao existir placeholder
			String placeholder;
			placeholder = nomeJogadores[i].getString();
			if (placeholder.getSize() == 0)
			{
				Stringjogadores[i].first.setString("AAAA AAAAA");
			}
		}
	}

	//pontuacao
	for (size_t i = 0; i < inputpontuacaoJogadores.size(); i++)
	{
		stringstream ss;
		ss << inputpontuacaoJogadores[i];
		
		pair<Text, int> novaPontuacao;
		novaPontuacao.first.setString(ss.str());
		novaPontuacao.first.setCharacterSize(15);
		novaPontuacao.second = inputpontuacaoJogadores[i];

		if (Stringpontuacao.size() <= i)
		{
			pontuacaoJogadores.push_back(inputpontuacaoJogadores[i]);
			Stringpontuacao.push_back(novaPontuacao);
		}
		else {
			pontuacaoJogadores[i] = inputpontuacaoJogadores[i];
			Stringpontuacao[i] = novaPontuacao;
		}
		
	}
	Font font;
	font.loadFromFile("black.ttf");
}


void Game::correr()
{
	// The `run()` method is used to start the game and
	// contains the game loop.

	// Instead of using `break` to stop the game, we will
	// use a boolean variable, `running`.
	executando = true;

	while (executando)
	{
		auto timePoint1(chrono::high_resolution_clock::now());

		window.clear(Color::Black);

		// It's not a bad idea to use methods to make the
		// code more organized. In this case, I've divided
		// the game loop in "input", "update" and "draw"
		// phases. It's one of many possible ways of tidying up
		// the code :)
		inputPhase();

		if (jogo_pausado) break;

		updatePhase();

		drawPhase();

		auto timePoint2(chrono::high_resolution_clock::now());
		auto elapsedTime(timePoint2 - timePoint1);
		FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(
			elapsedTime)
			.count() };

		lastFt = ft;

		auto ftSeconds(ft / 1000.f);
		auto fps(1.f / ftSeconds);
	}
}

void Game::inputPhase()
{
	Event evento;
	while (window.pollEvent(evento))
	{
		if (evento.type == Event::Closed)
		{
			window.close();
			break;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::O)) bola.setvelocidadebola(0.005f);
	if (Keyboard::isKeyPressed(Keyboard::Key::I)) bola.setvelocidadebola(-0.005f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) executando = false;
}

void Game::updatePhase()
{
	currentSlice += lastFt;
	for (; currentSlice >= ftSlice; currentSlice -= ftSlice)
	{
		bola.update(ftStep);
		barra.update(ftStep);
		testeColisao(barra, bola);
		for (auto& Tijolo : Tijolos) testeColisao(Tijolo, bola);
		Tijolos.erase(remove_if(begin(Tijolos), end(Tijolos),
			[](const Tijolo& mTijolo)
		{
			return mTijolo.destruido;
		}),
			end(Tijolos));
	}
}

void Game::drawPhase()
{
	

	if (bola.fimjogo == true)
	{
		jogo_pausado = true;
		window.clear();
		//window.draw(fimdoJogo);

		stringstream ss;

		
		Text gameOverTxt, a, b, c;
		gameOverTxt.setFont(font);
		a.setFont(font);
		b.setFont(font);
		c.setFont(font);

		gameOverTxt.setString("You are dead");
		gameOverTxt.setPosition(0 , 200);
		gameOverTxt.setFillColor(Color::White);
		window.draw(gameOverTxt);

		ss << "Your score: " << pontuacao;
		a.setString(ss.str());
		a.setPosition(0, 300);
		a.setFillColor(Color::White);
		window.draw(a);

	
		b.setString("Try again!");
		b.setPosition(0, 400);
		b.setFillColor(Color::White);
		window.draw(b);

		c.setString("Back to main menu");
		c.setFillColor(Color::White);
		c.setPosition(0, 500);
		window.draw(c);

		window.display();

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
					
				}
			}
		}
	}

	// define valor do score
	string pont = to_string(pontuacao);
	mostraPontuacao.setString(pont);
  
	window.draw(bola.forma_bola);
	window.draw(barra.forma_req);
	window.draw(texto);
	window.draw(mostraPontuacao);
	window.draw(txtBola);
	window.draw(mostraVel);
	for (auto& Tijolo : Tijolos) window.draw(Tijolo.forma_req); // fazer ciclo for "normalmente"
																//	if (fimjogo = true)
																//	window.draw(fimdojogo);
	window.display();
}

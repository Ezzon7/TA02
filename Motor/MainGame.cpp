#include "MainGame.h"
#include "Sprite.h"
#include <chrono>
#include <thread>

MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;

}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Motor WD2M", width, height, 0);

	initShaders();

}

MainGame::~MainGame()
{


}

void MainGame::run()
{
	init();
	auto start_time = std::chrono::steady_clock::now();
	/*
	sprite.init(-1, -1, 1, 1, "images/sonic.png");
	sprite2.init(0, 0, 1, 1, "images/knuckles.png");
	sprite3.init(-1, 0, 1, 1, "images/tails.png");
	sprite4.init(0, -1, 1, 1, "images/shadow.png");
	*/
	update(start_time);
}


void MainGame::draw(Sprite& sprite)
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.02;
	sprite.draw();
	//sprite2.draw();
	//sprite3.draw();
	//sprite4.draw();


	program.unuse();
	window->swapWindow();

}

void MainGame::update(std::chrono::steady_clock::time_point start_time)
{
	sprite.init(-1, -1, 1, 1, "images/sonic.png");
	std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed_seconds = current_time - start_time;
	float elapsed_time = elapsed_seconds.count();

	while (elapsed_time < 5.0) {
		draw(sprite);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		current_time = std::chrono::steady_clock::now();
		elapsed_seconds = current_time - start_time;
		elapsed_time = elapsed_seconds.count();
	}

	sprite2.init(0, 0, 1, 1, "images/knuckles.png");
	draw(sprite2);

	start_time = std::chrono::steady_clock::now();
	current_time = std::chrono::steady_clock::now();
	elapsed_seconds = current_time - start_time;
	elapsed_time = elapsed_seconds.count();
	while (elapsed_time < 5.0) {
		draw(sprite2);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		current_time = std::chrono::steady_clock::now();
		elapsed_seconds = current_time - start_time;
		elapsed_time = elapsed_seconds.count();
	}

	sprite3.init(-1, 0, 1, 1, "images/tails.png");
	draw(sprite3);

	start_time = std::chrono::steady_clock::now();
	current_time = std::chrono::steady_clock::now();
	elapsed_seconds = current_time - start_time;
	elapsed_time = elapsed_seconds.count();
	while (elapsed_time < 5.0) {
		draw(sprite3);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		current_time = std::chrono::steady_clock::now();
		elapsed_seconds = current_time - start_time;
		elapsed_time = elapsed_seconds.count();
	}

	sprite4.init(0, -1, 1, 1, "images/shadow.png");
	draw(sprite4);

	start_time = std::chrono::steady_clock::now();
	current_time = std::chrono::steady_clock::now();
	elapsed_seconds = current_time - start_time;
	elapsed_time = elapsed_seconds.count();
	while (elapsed_time < 5.0) {
		draw(sprite4);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		current_time = std::chrono::steady_clock::now();
		elapsed_seconds = current_time - start_time;
		elapsed_time = elapsed_seconds.count();
	}

	/*
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
	*/
	processInput();
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << " Posicion en X " << event.motion.x
				<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPoistion");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();

}

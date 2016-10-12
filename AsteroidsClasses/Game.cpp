#include "Game.h"
#include <SDL.h>
#include <iostream>
#include "Player.h"
#include "AITank.h"

using namespace Game1;

Game * Game::instance = nullptr;

Game::Game(void)
{
	instance = this;
}


Game::~Game(void)
{
}

bool Game::InitialiseSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	SDL_Window *win = nullptr;
	win = SDL_CreateWindow("Goodbye Cruel World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	SDL_RenderSetLogicalSize(renderer, 640, 480);
	return true;
}

bool Game::Initialise()
{
	if (!InitialiseSDL())
	{
		return false;
	}
	shared_ptr<Player> player = make_shared<Player>();
	children.push_back(player);

	aiTank = make_shared<AITank>();
	children.push_back(aiTank);

	list<shared_ptr<GameComponent>>::iterator it = children.begin();
	while (it != children.end())
	{
		(*it)->Initialise();
		++it;
	}
}

void Game::Update(float timeDelta)
{
	list<shared_ptr<GameComponent>>::iterator it = children.begin();
	while (it != children.end())
	{
		(*it)->Update(timeDelta);
		if ((*it)->alive == false)
		{
			it = children.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Game::Draw()
{
	list<shared_ptr<GameComponent>>::iterator it = children.begin();
	while (it != children.end())
	{
		(*it)->Draw();
		++it;
	}
}

void Game::Cleanup()
{
	list<shared_ptr<GameComponent>>::iterator it = children.begin();
	while (it != children.end())
	{
		(*it)->Cleanup();
		++it;
	}
}

Game * Game::Instance()
{
	return Game::instance;
}

void Game::Start()
{
	if (!Initialise())
	{
		return;
	}
	SDL_Event event;
	long last = SDL_GetTicks();
	running = true;
	const Uint8 * keyState = SDL_GetKeyboardState(NULL);
	while (running)
	{
		SDL_RenderClear(renderer);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				continue;
			}
		}
		if (keyState[SDL_SCANCODE_ESCAPE])
		{
			running = false;
			continue;
		}

		long now = SDL_GetTicks();
		float ellapsed = ((float)(now - last)) / 1000.0f;
		Update(ellapsed);
		Draw();
		last = now;
		SDL_RenderPresent(renderer);
	}
	SDL_Quit();
}



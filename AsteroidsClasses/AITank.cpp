#include "AITank.h"
#include "Player.h"
#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Bullet.h"
#include <glm/gtc/constants.hpp>

using namespace Game1;
using namespace std;


AITank::AITank(void) :GameComponent()
{
	position = glm::vec2(10, 200);
	look = glm::vec2(0, -1);
	speed = 200.0f;
	elapsed = 1.0f;
	fireRate = 10.0f;
}

bool AITank::Initialise()
{
	SDL_Surface * temp = NULL;
	temp = SDL_LoadBMP("tank.bmp");
	if (temp == nullptr)
	{
		cout << "Could not load player texture" << endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer, temp);
	SDL_FreeSurface(temp);

	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

	center.x = rect.w / 2;
	center.y = rect.h / 2;
	return true;
}

AITank::~AITank()
{
}

void AITank::Update(float timeDelta)
{
	position += look * speed * timeDelta;

	if (position.y <= 10 && position.x <= 10 ||
		position.y <= 10 && position.x >= 606 ||
		position.y >= 448 && position.x >= 606 ||
		position.y >= 448 && position.x <= 10)
	{
		rotation += glm::radians(90.0);
	}

	elapsed += timeDelta;

	look.x = glm::sin(rotation);
	look.y = -glm::cos(rotation);

}

void AITank::Draw()
{
	rect.x = position.x;
	rect.y = position.y;

	SDL_RenderCopyEx(Game::Instance()->renderer, texture, nullptr, &rect, glm::degrees(rotation), &center, SDL_FLIP_NONE);
}

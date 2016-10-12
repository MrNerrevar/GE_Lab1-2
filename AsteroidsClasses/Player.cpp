#include "Player.h"
#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Bullet.h"
#include <glm/gtc/constants.hpp>

using namespace Game1;
using namespace std;

Player::Player(void) :GameComponent()
{
	position = glm::vec2(100, 100);
	look = glm::vec2(0, -1);
	speed = 50.0f;
	elapsed = 1.0f;
	fireRate = 10.0f;
}

bool Player::Initialise()
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


Player::~Player(void)
{

}


void Player::Update(float timeDelta)
{
	static float toPass = 1.0f / fireRate;

	const Uint8 * keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_UP])
	{
		position += look * speed * timeDelta;
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		position -= look * speed * timeDelta;
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		rotation -= timeDelta;
	}

	if (keyState[SDL_SCANCODE_RIGHT])
	{
		rotation += timeDelta;
	}


	if (keyState[SDL_SCANCODE_SPACE])
	{
		if (elapsed > toPass)
		{
			shared_ptr<Bullet> bullet = make_shared<Bullet>();
			bullet->position = position + glm::vec2(center.x, center.y) + (look * 13.0f);
			bullet->look = look;
			bullet->Initialise();
			Game::Instance()->children.push_back(bullet);
			elapsed = 0;
		}

	}
	elapsed += timeDelta;

	look.x = glm::sin(rotation);
	look.y = -glm::cos(rotation);

}

void Player::Draw()
{
	rect.x = position.x;
	rect.y = position.y;

	SDL_RenderCopyEx(Game::Instance()->renderer, texture, nullptr, &rect, glm::degrees(rotation), &center, SDL_FLIP_NONE);
}

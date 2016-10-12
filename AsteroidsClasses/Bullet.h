#pragma once
#include "GameComponent.h"
#include <SDL.h>


namespace Game1
{
	class Bullet :public GameComponent
	{
	public:
		Bullet(void);
		~Bullet(void);

		SDL_Texture * texture;


		bool Initialise();
		void Update(float timeDelta);
		void Draw();
	};
}


#pragma once
#include "GameComponent.h"
#include <SDL.h>

namespace Game1
{
	class Player :
		public GameComponent
	{
	public:
		Player(void);
		~Player(void);

		SDL_Texture * texture;
		SDL_Point center;
		SDL_Rect rect;
		float elapsed;
		float fireRate;
		void Update(float timeDelta);
		bool Initialise();
		void Update();
		void Draw();

	};
}


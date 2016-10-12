#pragma once
#include "GameComponent.h"
#include <SDL.h>

namespace Game1
{
	class AITank :
		public GameComponent
	{
	public:
		AITank(void);
		~AITank(void);

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
#include <glm.hpp>
#include <SDL.h>
#include <cstdint>
#include <random>

class Utils
{
	public:

		static glm::vec2 RndVec2(float min, float max)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dist(min, max);
			return glm::vec2(dist(gen), dist(gen));
		}

		static SDL_Color RndCol()
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(0, 255);

			SDL_Color color;
			color.r = static_cast<uint8_t>(dist(gen));
			color.g = static_cast<uint8_t>(dist(gen));
			color.b = static_cast<uint8_t>(dist(gen));
			color.a = 255;

			return color;
		}

};

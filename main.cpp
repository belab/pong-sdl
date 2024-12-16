#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <chrono>
#include <string>
#define SDL_main main

struct Vec2f{float x, y;};

void renderText(SDL_Renderer* renderer, const std::string& text, TTF_Font* font, int x, int y)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255, 255});
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void clampPaddlePosition(float& y, float height, float bottom)
{
	if(y < 0)
		y = 0.0f;
	else if((y+height) > bottom)
		y = bottom-height;
}
void reflectByRightPaddle(Vec2f& ball, float& ballSpeedX, const Vec2f& paddle)
{
	if(ball.x >= (paddle.x-20.0f))
	{
		if((ball.y >= paddle.y) && ((ball.y + 20.0f) <= (paddle.y + 50.0f)))
		{
			ball.x = paddle.x-20.0f; 
			ballSpeedX = -ballSpeedX;
		}
	}
}
void reflectByLeftPaddle(Vec2f& ball, float& ballSpeedX, const Vec2f& paddle)
{
	if(ball.x <= (paddle.x+10.0f))
	{
		if((ball.y >= paddle.y) && ((ball.y + 20.0f) <= (paddle.y + 50.0f)))
		{
			ball.x = paddle.x+10.0f; 
			ballSpeedX = -ballSpeedX;
		}
	}
}
void reflectVertical(float y, float height, float& ballSpeedY, float bottom)
{
	if (y < 0 || (y + height) > bottom)
	{
		ballSpeedY = -ballSpeedY;
	}
}
int main(int argc, char *argv[])
{
	int scorePlayer1 = 0;
	int scorePlayer2 = 0;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	Vec2f ball{100.0f, 200.0f};
	Vec2f player1{20.0f, 200.0f};
	Vec2f player2{370.0f, 200.0f};

	TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 30);
	Vec2f ballSpeed{0.05f, 0.05f};
	bool running = true;
	float dt= 0.0f;
	while (running)
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
		float p1Speed = 0.0f;
		float p2Speed = 0.0f;
		const auto state = SDL_GetKeyboardState(nullptr);
		if (state[SDL_SCANCODE_W])
		{
			p1Speed = -0.1f;
		}
		else if (state[SDL_SCANCODE_S])
		{
			p1Speed = 0.1f;
		}
		if (state[SDL_SCANCODE_UP])
		{
			p2Speed = -0.1f;
		}
		else if (state[SDL_SCANCODE_DOWN])
		{
			p2Speed = 0.1f;
		}

		// clampPaddlePosition(player2, 400.f);
		ball.x += ballSpeed.x * dt;
		ball.y += ballSpeed.y * dt;
		player1.y += p1Speed * dt;
		player2.y += p2Speed * dt;

		if (ball.x < 0.0f)
		{
			scorePlayer2++;
			ball.x = 100.0f;
			ball.y = 200.0f;
		}
		if ((ball.x + 20.0f) > 400.0f)
		{
			scorePlayer1++;
			ball.x = 100.0f;
			ball.y = 200.0f;
		}
		reflectVertical(ball.y, 20.0f, ballSpeed.y, 400.0f);
		clampPaddlePosition(player1.y, 50.0f, 400.0f);
		clampPaddlePosition(player2.y, 50.0f, 400.0f);
		reflectByLeftPaddle(ball, ballSpeed.x, player1);
		reflectByRightPaddle(ball, ballSpeed.x, player2);

		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		renderText(renderer, std::to_string(scorePlayer1), font, 100, 0);
		renderText(renderer, std::to_string(scorePlayer2), font, 290, 0);
		SDL_FRect ballShape{ball.x, ball.y, 20, 20};
		SDL_FRect p1Shape{player1.x, player1.y, 10, 50};
		SDL_FRect p2Shape{player2.x, player2.y, 10, 50};
		SDL_FRect mid{200, 0, 1, 400};
		SDL_RenderFillRectF(renderer, &mid);
		SDL_RenderFillRectF(renderer, &ballShape);
		SDL_RenderFillRectF(renderer, &p1Shape);
		SDL_RenderFillRectF(renderer, &p2Shape);
		SDL_RenderPresent(renderer);
		auto stopTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}
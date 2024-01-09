#pragma once
#include <SDL.h>

class Gradation
{
private:
	SDL_Renderer* renderer;

	const int maxColorIndex = 10;
	SDL_Color gradientColors[10];
	int nowGradientIndex;

	SDL_Rect gradientRect;
public:
	Gradation(SDL_Renderer* getRend);
	~Gradation() { SDL_DestroyRenderer(renderer); }

	void AddGradient(SDL_Color color);
	void RemoveGradient(int idx);
	void RemoveGradient(SDL_Color color);
	void SetColorIndex(int idx, SDL_Color color);
	void DrawGradation(int x, int y, int w, int h);
	void DrawGradation(SDL_Rect rct);
private:
	void Drawing();	//public의 Draw함수의 공통사용
};

class Polygon
{
private:
	SDL_Renderer* renderer;
	int poly = 3;
	int r;
};

class Mask	//창 색상 효과
{
private:
	SDL_Renderer* renderer;

	SDL_Color bgColor;
};
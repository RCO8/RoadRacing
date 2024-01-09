#include "Graphic.h"

Gradation::Gradation(SDL_Renderer* getRend) : renderer(getRend)
{
	nowGradientIndex = 2;
	gradientColors[0] = { 0,0,0,255 };
	gradientColors[1] = { 255,255,255,255 };
}

void Gradation::AddGradient(SDL_Color color)
{
	if (nowGradientIndex > maxColorIndex)
	{
		SDL_Log("Too much Gradation Index!!!");
		return;
	}
	gradientColors[nowGradientIndex] = color;
	nowGradientIndex++;
}

void Gradation::RemoveGradient(int idx)
{
	if (idx > nowGradientIndex)
	{
		SDL_Log("Overflow Gradation Index!!!");
		return;
	}
	for (int i = idx; i < nowGradientIndex - 1; i++)
		gradientColors[i] = gradientColors[i + 1];
	nowGradientIndex--;
}
void Gradation::RemoveGradient(SDL_Color color)
{
	int foundIdx, i;
	for (i = 0; i < nowGradientIndex; i++)
	{
		if (&gradientColors[i] == &color)
		{
			foundIdx = i;
			break;
		}
	}
	for (i = foundIdx; i < nowGradientIndex - 1; i++)
		gradientColors[i] = gradientColors[i + 1];
	nowGradientIndex--;
}

void Gradation::SetColorIndex(int idx, SDL_Color color)
{
	if (idx > nowGradientIndex)
	{
		SDL_Log("Overflow Gradation Index!!!");
		return;
	}
	gradientColors[idx] = color;
}

void Gradation::DrawGradation(int x, int y, int w, int h)
{
	gradientRect.x = x;
	gradientRect.y = y;
	gradientRect.w = w;
	gradientRect.h = h;

	Drawing();
}
void Gradation::DrawGradation(SDL_Rect rct)
{
	gradientRect = rct;

	Drawing();
}
void Gradation::Drawing()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	for (int i = 0; i < 256; i++)
	{
		SDL_SetRenderDrawColor(renderer,
			gradientColors[0].r, gradientColors[0].g,
			gradientColors[0].b, 10);
		SDL_RenderFillRect(renderer, &gradientRect);
	}
}
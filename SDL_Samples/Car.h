#pragma once
#include <vector>
using namespace std;

class Car
{
private:
	Sprite* carSpr;

	vector<SDL_Rect> showClip;	//일부를 표시할 속성

	int posX = 0, posY = 0;
	bool reverse = false;
public:
	Car(SDL_Renderer* renderer)
	{
		carSpr = new Sprite(renderer, "Bikes.png");

		InitClips();

		carSpr->SetColorHide(186, 254, 202);
		carSpr->SetSpriteClip(showClip[0]);
		carSpr->SetRotatePoint(carSpr->GetClipWidth() / 2, carSpr->GetClipHeight());

		posX = 320 - carSpr->GetClipWidth() / 2;
		posY = 480 - carSpr->GetClipHeight();
	}

	void SetPos(int x)
	{
		posX += x;
	}

	void SetIndex(int idx)
	{
		reverse = idx < 0 ? true : false;	//반전 설정
		int clipIdx = SDL_abs(idx);	//스프라이트 클립 지정할 속성(음수로 받으면 큰일)
		carSpr->SetSpriteClip(showClip[clipIdx]);
	}

	void DrawCar() const
	{
		carSpr->Drawing(posX, posY, 0, reverse);
	}
private:
	void InitClips()
	{
		showClip.push_back({ 8,8,21,48 });
		showClip.push_back({ 39,8,24,48 });
		showClip.push_back({ 72,8,29,48 }); 
	}
};
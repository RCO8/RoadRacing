#include <deque>
#include <ctime>
#include <stdlib.h>
#include <SDL.h>
#include "Sprite.h"
using namespace std;

class Route
{
private:
	SDL_Renderer* renderer;
	Sprite* routes;
	deque<int> routeType;	//직선이나 커브를 판정하기 위한
	int nowRoute;	//현재 오는 길
	int routeDigit;	//도로 간격 (간격 : 5)
public:
	Route(SDL_Renderer* renderer)
	{
		routes = new Sprite(renderer, "route.png");
		routes->SetColorHide(0xff, 0xff, 0xff);

		routeDigit = 0;
		nowRoute = 1;
		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			routeType.push_back(nowRoute);	//routeType에 도로 삽입  1 :직진, 2 :좌회, 3 :우회
			routeDigit++;
		}
	}

	void ShowRoute()	//화면에 도로 표시
	{
		routeType.pop_front();
		//도로 그리기
		routes->Drawing(270, 380, 0);
		setRandomCurve();
		routeType.push_back(nowRoute);
		routeDigit++;
	}
private:
	void setRandomCurve()
	{
		if (routeDigit > 5)
		{
			routeDigit = 0;
			nowRoute = rand() % 3;
		}
	}
};
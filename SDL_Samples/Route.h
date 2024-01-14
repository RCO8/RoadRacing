#include <deque>
#include <ctime>
#include <stdlib.h>
#include <SDL.h>
#include "Sprite.h"
using namespace std;

class Route
{
private:
	SDL_Renderer* rend;
	Sprite* routes;
	deque<int> routeType;	//직선이나 커브를 판정하기 위한
	int nowRoute;	//현재 오는 길
	int routeDigit;	//도로 간격 (간격 : 5)
	
	int posX, posY;
	SDL_Rect RouteCollide;
public:
	Route(SDL_Renderer* renderer)
	{
		rend = renderer;
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

		posX = 270;
		posY = 380;
		RouteCollide = { posX,posY,100,100 };
	}

	void ShowRoute()	//화면에 도로 표시
	{
		//도로 그리기
		routes->Drawing(posX, posY, 0);
		setRandomCurve(); 
		routeDigit++;
	}

	SDL_Rect GetRouteArea()
	{
		return RouteCollide;
	}
private:
	void setRandomCurve()
	{
		SDL_Log("Digit : %d", routeDigit);
		if (routeDigit > 20)
		{
			routeType.pop_front();
			routeDigit = 0;
			nowRoute = rand() % 3;
			routeType.push_back(nowRoute);
		}
		switch (nowRoute)
		{
		case 1:	//좌회
			posX--;
			break;
		case 2:	//우회
			posX++;
			break;
		default:
			posX += 0;
			break;
		}
	}
};
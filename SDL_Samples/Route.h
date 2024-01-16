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
	
	int delayType;	//도로형태가 바뀔 때 변경될 대기시간

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

		delayType = 60;
	}

	void ShowRoute(bool isStart)	//화면에 도로 표시
	{
		//도로 그리기
		routes->Drawing(posX, posY, 0);
		if (isStart)	//게임이 시작되면 도로를 움직여라
		{
			setRandomCurve();
			routeDigit++;
		}
	}

	SDL_Rect GetRouteArea()
	{
		return RouteCollide;
	}
private:
	void setRandomCurve()
	{
		//SDL_Log("Digit : %d", routeDigit);
		if (routeDigit > delayType)
		{
			routeType.pop_front();
			routeDigit = 0;
			nowRoute = rand() % 3;
			routeType.push_back(nowRoute);
		}
		int moveSpd = 2;
		switch (nowRoute)
		{
		case 1:	//좌회
			if(posX > 0)
				posX -= moveSpd;
			delayType = 20;
			break;
		case 2:	//우회
			if(posX < 540)
				posX += moveSpd;
			delayType = 20;
			break;
		default:
			posX += 0;
			delayType = 60;
			break;
		}

		RouteCollide.x = posX;
		RouteCollide.w = 100;
	}
};
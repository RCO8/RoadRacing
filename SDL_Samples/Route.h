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
	deque<int> routeType;	//�����̳� Ŀ�긦 �����ϱ� ����
	int nowRoute;	//���� ���� ��
	int routeDigit;	//���� ���� (���� : 5)
	
	int delayType;	//�������°� �ٲ� �� ����� ���ð�

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
			routeType.push_back(nowRoute);	//routeType�� ���� ����  1 :����, 2 :��ȸ, 3 :��ȸ
			routeDigit++;
		}

		posX = 270;
		posY = 380;
		RouteCollide = { posX,posY,100,100 };

		delayType = 60;
	}

	void ShowRoute(bool isStart)	//ȭ�鿡 ���� ǥ��
	{
		//���� �׸���
		routes->Drawing(posX, posY, 0);
		if (isStart)	//������ ���۵Ǹ� ���θ� ��������
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
		case 1:	//��ȸ
			if(posX > 0)
				posX -= moveSpd;
			delayType = 20;
			break;
		case 2:	//��ȸ
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
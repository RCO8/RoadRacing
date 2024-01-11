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
	deque<int> routeType;	//�����̳� Ŀ�긦 �����ϱ� ����
	int nowRoute;	//���� ���� ��
	int routeDigit;	//���� ���� (���� : 5)
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
			routeType.push_back(nowRoute);	//routeType�� ���� ����  1 :����, 2 :��ȸ, 3 :��ȸ
			routeDigit++;
		}
	}

	void ShowRoute()	//ȭ�鿡 ���� ǥ��
	{
		routeType.pop_front();
		//���� �׸���
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
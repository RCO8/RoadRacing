#include <vector>
#include <SDL.h>
#include "Sprite.h"
using namespace std;

class Route
{
private:
	SDL_Renderer* renderer;
	Sprite* routes;
	vector<int> routeType;	//�����̳� Ŀ�긦 �����ϱ� ����
};
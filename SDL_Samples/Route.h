#include <vector>
#include <SDL.h>
#include "Sprite.h"
using namespace std;

class Route
{
private:
	SDL_Renderer* renderer;
	Sprite* routes;
	vector<int> routeType;	//직선이나 커브를 판정하기 위한
};
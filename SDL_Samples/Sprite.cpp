#include "Sprite.h"

//스프라이트 불러와서 데이터에 저장
Sprite::Sprite(SDL_Renderer* getRenderer, const char* fileName) : sprRenderer(getRenderer)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	imageFile = IMG_Load(fileName);	//이미지파일 로드
	if (imageFile == NULL)
	{
		SDL_Log("SDL Load Image Error : %s\n", SDL_GetError());
		this->~Sprite();
	}
	//만약에 파일이 png, jpg, wepb라면 함수로 형태 교체
	sprTexture= SDL_CreateTextureFromSurface(sprRenderer, imageFile);	//이미지를 텍스쳐로
	if (sprTexture == NULL)
	{
		SDL_Log("SDL Texture Error : %s\n", SDL_GetError());
		this->~Sprite();
	}
	
	SetSpriteClip(0, 0, GetImageWidth(), GetImageHeight());
	SetRotatePoint(0, 0);
}
//스프라이트 제거
Sprite::~Sprite()
{
	IMG_Quit();
	SDL_FreeSurface(imageFile);
	SDL_DestroyTexture(sprTexture);
	SDL_DestroyRenderer(sprRenderer);
}
//이미지 파일의 일부를 나타낼 설정
void Sprite::SetSpriteClip(int x, int y, int w, int h)
{
	sprRct.x = x;
	sprRct.y = y;
	sprRct.w = w;
	sprRct.h = h;
}
void Sprite::SetSpriteClip(SDL_Rect rct) { sprRct = rct; }

//크기 설정
void Sprite::SetSpriteScale(float w, float h)
{
	//SDL_ScaleModeLinear	흐리게
	//SDL_ScaleModeNearest	픽셀 선명화
	SDL_SetTextureScaleMode(sprTexture, SDL_ScaleModeNearest);	//축척 모드 실수형으로 정의
	SDL_SetTextureBlendMode(sprTexture, SDL_BLENDMODE_BLEND);	//칼라 모드 알파와 같이

	scaleWidth = w;
	scaleHeight = h;
}
//중심점 지정
void Sprite::SetRotatePoint(int x, int y)
{
	rotatePoint.x = x;
	rotatePoint.y = y;
}
//투명색 설정
void Sprite::SetColorHide(SDL_Color setColor)
{
	Color = SDL_MapRGB(imageFile->format, setColor.r, setColor.g, setColor.b);	//파일의 색을 Color에 지정
	SDL_SetColorKey(imageFile, SDL_TRUE, Color);	//파일의 배경색으로 지정
	sprTexture = SDL_CreateTextureFromSurface(sprRenderer, imageFile);	//다시 파일을 Renderer로 갱신
}
void Sprite::SetColorHide(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Color = SDL_MapRGB(imageFile->format, r, g, b);
	SDL_SetColorKey(imageFile, SDL_TRUE, Color);
	sprTexture = SDL_CreateTextureFromSurface(sprRenderer, imageFile);
}
//화면에 그리기
void Sprite::Drawing(int x, int y, int dir, bool mirror)
{
	scrnRct.x = x;
	scrnRct.y = y;
	scrnRct.w = sprRct.w * scaleWidth;
	scrnRct.h = sprRct.h * scaleHeight;

	if (dir >= 360) dir -= 360;
	if (dir <= -360) dir += 360;

	SDL_RenderSetScale(sprRenderer, scaleWidth, scaleHeight);

	SDL_RenderCopyEx(sprRenderer, sprTexture, &sprRct, &scrnRct,
		dir, &rotatePoint, mirror ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
//전체화면으로 채우기
void Sprite::DrawFill() const	{ SDL_RenderCopy(sprRenderer, sprTexture, NULL, NULL); }
//스프라이트를 해당 색상으로 블렌드
void Sprite::SetColorBlend(Uint8 r, Uint8 g, Uint8 b)	{ SDL_SetTextureColorMod(sprTexture, r, g, b); }
void Sprite::SetColorBlend(SDL_Color setColor)	{ SDL_SetTextureColorMod(sprTexture, setColor.r, setColor.g, setColor.b); }
//스프라이트 투명화
void Sprite::SetImageAlpha(Uint8 a)	{ SDL_SetTextureAlphaMod(sprTexture, a); }
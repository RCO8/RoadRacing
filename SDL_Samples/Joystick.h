#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;

//Arcade ver
//Multi Device in class
class Joystick
{
private:
	SDL_Joystick* myJoystick;           //연결된 조이스틱과 통신
	char* joystickName;					//현재 조이스틱 디바이스 이름

	/* Need checking batter what joystick is wiress*/
	float checkBattery[8];

	//이 속성들은 Gaming같은 클래스에 상호작용을 하기 위해서 값으로 반환
	int AxisX[8], AxisY[8];
	int HatSwitches[8];
	bool Buttons[8][12];
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent(SDL_Event event);
	//현재 디바이스에서 동작한 값을 매겨 반환
	int GetAxisX(int idx) { return AxisX[idx]; }
	int GetAxisY(int idx) { return AxisY[idx]; }
	int GetHatSwitches(int idx) { return HatSwitches[idx]; }
	bool GetButtons(int idx, int btn) { return Buttons[idx][btn]; }
};

//Console ver
//Single Device in class
class GamePad
{
private:
	SDL_GameController* gameController;
	char* gamePadName;

	const int maxAxis = 32768;    //Controller Max Axis
	int stickDead = 10000;
	int triggerDead = 10000;
	float checkBattery;

	//반환될 축이나 입력값을 저장할 속성들
	struct StickAxis
	{
		int x, y;	//일반적인 입력값
		int deadx, deady;	//데드존 통과한 값 (넘으면 2, 넘지않은 입력은 1, 미동작은 0)
	};
	StickAxis LeftStick = { 0,0,0,0 };
	StickAxis RightStick = { 0,0,0,0 };

	struct TriggerAxis
	{
		int l, r;
		bool deadl, deadr;
	};
	TriggerAxis PadTrigger = { 0,0,0,0 };
public:
	GamePad(int index);
	~GamePad();

	char getControllerName() { return *gamePadName; }
	void CheckGamepadEvent(SDL_Event event);
	void SetAxisDead(int deadzone);
	void SetControllerWave(int ms,int level = 1);	//Game Controller Wave Level while ms
	//아날로그 스틱 받을 값
	StickAxis GetLeftAxis() const { return LeftStick; }
	StickAxis GetRightAxis() const { return RightStick; }
	//트리거 입력받을 값
	TriggerAxis GetTriggerAxis() const { return PadTrigger; }
};
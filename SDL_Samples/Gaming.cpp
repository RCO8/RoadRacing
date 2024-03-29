#include "Gaming.h"

const int windowWidth = 640;
const int windowHeight = 480;

bool Gaming::GameInit()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Racing", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        SDL_Log("Failed Init Window : %s \n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        SDL_Log("Failed Init Renderer : %s", SDL_GetError());
        return false;
    }

    //Resouce Setting
    gPad = new GamePad(0);
    mCar = new Car(renderer);
    route = new Route(renderer);
    return true;
}

void Gaming::CheckKeyPress()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: quit = true; break;
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_MINIMIZED: //SDL_Log("Window Minimize");
                break;
            case SDL_WINDOWEVENT_ENTER:     //SDL_Log("Window Inside");
                break;
            case SDL_WINDOWEVENT_LEAVE:     //SDL_Log("Window Outside");
                break;
            case SDL_WINDOWEVENT_MOVED:     //SDL_Log("Window : (%d, %d)", event.window.data1, event.window.data2 - 31);  //이동된 창을 좌표로 얻기
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:  //SDL_Log("Window Enable");
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:    //SDL_Log("Window Disable");
                break;
            case SDL_WINDOWEVENT_CLOSE: quit = true; break;
            }

            //Keyboard Check
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            default:
                break;
            }
        case SDL_KEYMAPCHANGED:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:       //SDL_Log("Up");
                break;
            case SDL_SCANCODE_DOWN:     //SDL_Log("Down");
                break;
            case SDL_SCANCODE_LEFT:     //SDL_Log("Left");
                break;
            case SDL_SCANCODE_RIGHT:    //SDL_Log("Right");
                break;
            case SDL_SCANCODE_RETURN:   //SDL_Log("Enter");
                break;
            case SDL_SCANCODE_SPACE:    //SDL_Log("Space");
                break;
            case SDL_SCANCODE_LSHIFT:   //SDL_Log("Shift");
                break;
            case SDL_SCANCODE_LCTRL:    //SDL_Log("Ctrl");
                break;
            case SDL_SCANCODE_LALT:     //SDL_Log("Alt");
                break;
            case SDL_SCANCODE_F1:       //SDL_Log("F1");
                break;
            case SDL_SCANCODE_W:        //SDL_Log("W");
                break;
            case SDL_SCANCODE_S:        //SDL_Log("S");
                break;
            case SDL_SCANCODE_A:        //SDL_Log("A");
                break;
            case SDL_SCANCODE_D:        //SDL_Log("D");
                break;
            case SDL_SCANCODE_ESCAPE:   //SDL_Log("Escape");
                break;
            default:
                break;
            }
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)  //Same to SDL_KEYDOWN
            {
            case SDL_SCANCODE_LEFT:
                break;
            default:
                break;
            }

            //Mouse Check
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case 1: //SDL_Log("Left Mouse");
                break;
            case 2: //SDL_Log("Middle Mouse");
                break;
            case 3: //SDL_Log("Right Mouse");
                break;
            }
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button) //Same to SDL_MOUSEBUTTONDOWN
            {
            case 1:
            case 2:
            case 3:
                break;
            }
        case SDL_MOUSEMOTION: //SDL_Log("Mouse : (%d, %d)", event.motion.x, event.motion.y);
            break;
        case SDL_MOUSEWHEEL:
            switch (event.wheel.y)
            {
            case 1:     //SDL_Log("Wheel Up");
                break;
            case -1:    //SDL_Log("Wheel Down");
                break;
            }

            //Controller Check (Console version)
        case SDL_CONTROLLERDEVICEADDED: //if Controller is connected
            // Joystick 생성자 호출
            break;
        }

        //추가적인 입력 디바이스가 있다면 여기로 메서드 호출
        if(gPad != NULL) gPad->CheckGamepadEvent(event);
    }
}
void Gaming::UpdateData()
{
    //게임 내 변형된 데이터를 여기에 갱신
    //만약에 이벤트에 적용을 하지 않는다면
    //mTimer.StartCount();
    //SDL_Log("%d", gPad->GetLeftAxis(0));
    if (gPad != NULL)
    {
        if (getAccel > 0)
        {
            mCar->SetIndex(gPad->GetLeftAxis().deadx);
            mCar->SetPos(gPad->GetLeftAxis().deadx);
        }
        else
            mCar->SetIndex(0);
    }

    //자동차가 도로를 벗어나면
    if (mCar->CheckCollide(*route))
    {
        //SDL_Log("벗어남");
    }

    getAccel = mCar->SetAccel(gPad->GetTriggerAxis().r);

    //엑셀을 밟을 때 속도가 올라감 즉 delay가 감소

    SDL_Log("%lf km/h", getAccel);
    SDL_Delay(100);
}
void Gaming::DrawScreen()   //Drawing Sprite or UI in this Screen
{
    SDL_SetRenderDrawColor(renderer, 0x2e, 0xab, 0xff, 255);
    SDL_RenderClear(renderer);  //Screen Clear 

    //Draw Field
    SDL_SetRenderDrawColor(renderer, 0x00, 0xab, 0x00, 255);
    SDL_Rect field = { 0,windowHeight - 100,windowWidth,100 };
    SDL_RenderFillRect(renderer, &field);

    //Draw Image
    route->ShowRoute(true, getAccel);
    mCar->DrawCar();
    //Draw UI


    SDL_RenderPresent(renderer);    //Redraw at Screen
    //카메라 뷰
}

void Gaming::GameRun()
{
    while (!quit)
    {
        CheckKeyPress();
        UpdateData();
        DrawScreen();
    }
}

void Gaming::GameOff()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
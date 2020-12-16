// ascii raytracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "vector.h"
#include "Scene.h"

using namespace std;


int WIDTH = 400;
int HEIGHT = 200;

int main()
{

    wchar_t* screen = new wchar_t[WIDTH * HEIGHT];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    SetConsoleActiveScreenBuffer(hConsole);

    DWORD dwBytesWritten = 0;


    Scene myScene(WIDTH, HEIGHT);

    
    myScene.AddSphere({ 0,5,40 }, 8, 1, 0, true);

    for (float i = 0; i < 7; i++)
    {
        myScene.AddSphere({ -35 + (i*10),5,70 }, 4, 0.8);
    }
  
    myScene.AddLight({ 10,25,60 }, 15);
    myScene.AddLight({ -15,15,40 }, 4);
    myScene.AddPlane({ 0,-3,0 }, { 0,1,0 }, 0.9);
    myScene.AddPlane({ 0,35,0 }, { 0,-1,0 }, 0.3);

    while (true)
    {
        for (int i = 0; i < 5; i++)
        {
            myScene.NextSample();

        }
        

        for (int x = 0; x < WIDTH ;x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                screen[y * WIDTH + x] = myScene.get(y * WIDTH + (WIDTH- 1 - x));
                
            }
        }

        screen[WIDTH * HEIGHT - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, WIDTH * HEIGHT, { 0,0 }, &dwBytesWritten);

    }
    
}


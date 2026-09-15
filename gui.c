#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <wingdi.h>
#include <string.h>
#include <stdlib.h>

#include "particle.h"
#include "map.h"



// extern char c;
char cstr[] = "STRING";
char cstr2[] = "ANOTHER STRING";

int counter = 0;



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    HDC hdc; //device context handler
    PAINTSTRUCT ps; //windows painter object 
    RECT rect; //rectangular coordinates of a window

    RedrawWindow(hwnd, &rect, NULL, message);

    // cstr[0] = c;
    // cstr[1] = '\0';

    switch (message){

        case WM_CREATE: //Initialize the window

            return 0;
        
        case WM_PAINT: //Draw window 

            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);

        

            DrawText(hdc, TEXT("OUPUT"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 

            EndPaint(hwnd, &ps);

            return 0;

        case WM_DESTROY: //Destry window

            PostQuitMessage(0);

            return 0;

        default:
            break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int cmdShow){
    
    static TCHAR name[] = TEXT("app");

    HWND hwnd; //Initialize the window handler
    MSG msg; //Initialize a message object

    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW; // Redraw the window vertically and horizontally if the window is resized

    wndclass.lpfnWndProc = WndProc; //Setting the windows pointer to a windows process defined with a callback
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    
    wndclass.lpszClassName = name; //Long pointer to application name, char array
    wndclass.lpszMenuName = NULL; 
    wndclass.cbClsExtra = 0; //Define extra memory for the windows class
    wndclass.cbWndExtra = 0; //Define extra memory for the window object

    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); //Load and assign the system cursor to the window class
    //wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //Load a white windows brush object **GDI32 Library linker required**
    

    if(!RegisterClass(&wndclass)){

        MessageBox(NULL, TEXT("Could not register Window Class!"), name, MB_ICONERROR);
    } //Registering the defined window class to the windows class manager

    hwnd = CreateWindow(name, TEXT("Projectile"), WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    //Create a window object with default values attached to a handle 

    ShowWindow(hwnd, cmdShow); //Passing the windows handler through an initial show and constant update 
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0) && counter < 1000){

        TranslateMessage(&msg);
        DispatchMessage(&msg);
        counter++;
    }

    return msg.wParam;


}
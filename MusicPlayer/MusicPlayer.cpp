#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include "resource.h"
#include "SongList.h"

using namespace std;

static TCHAR windowClass[] = _T("MusicPlayer");
static TCHAR windowName[] = _T("Music Player");

HINSTANCE instance;
int winWidth = 500, winHeight = 500;
SongList songList("Songs");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND createButton(HWND window, int x, int y, int width, int height, LPCSTR buttonText);
string getButtonText(HWND window, int resoruce);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){
    
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 9);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = windowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)){
        MessageBox(NULL, _T("Couldn't Register class"), _T("Error"), NULL);
        return 1;
    }

    instance = hInstance;

    HWND window = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, windowClass, windowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        winWidth, winHeight, NULL, NULL, hInstance, NULL);

    if (!window){
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Error"), NULL);
        return 1;
    }

    ShowWindow(window, nCmdShow);
    UpdateWindow(window);


    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Welcome to the music player");
    HWND leftButton, rightButton, playButton;
    string songName = "test";
    int x;

    switch (message){
        case WM_CREATE:
            //left button
            leftButton = createButton(hWnd, 25, winHeight*0.6, 100, 100, "<");
            //right button
            rightButton = createButton(hWnd, winWidth-150, winHeight*0.6, 100, 100, ">");
            //play/pause button
            playButton = createButton(hWnd, winWidth/2.65, winHeight * 0.6, 100, 100, "Play");

            break;
        case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);

            RECT rc;
            GetClientRect(hWnd, &rc);
            x = rc.right/2;

            SetTextAlign(hdc, TA_CENTER);
            songName = songList.GetCurrentSongName();
            TextOutA(hdc, x, 30, songName.c_str(), songName.length());

            EndPaint(hWnd, &ps);
            break;
        }
        case WM_COMMAND:
            if(LOWORD(wParam) == IDC_LEFT_BUTTON) {
                songList.Seek(1);
                SetDlgItemText(hWnd, IDC_PLAY_BUTTON, _T("Play"));
                InvalidateRgn(hWnd, NULL, TRUE);
            }
            else if(LOWORD(wParam) == IDC_RIGHT_BUTTON) {
                songList.Seek(0);
                SetDlgItemText(hWnd, IDC_PLAY_BUTTON, _T("Play"));
                InvalidateRgn(hWnd, NULL, TRUE);
            }
            else if (LOWORD(wParam) == IDC_PLAY_BUTTON) {
                
                string text = getButtonText(hWnd, IDC_PLAY_BUTTON);

                if (text == "Play") {
                    SetDlgItemText(hWnd, IDC_PLAY_BUTTON, _T("Pause"));
                    songList.Play();
                }  
                else {
                    SetDlgItemText(hWnd, IDC_PLAY_BUTTON, _T("Play"));
                    songList.Pause();
                }
                    
            }
            
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }

    return 0;
}

HWND createButton(HWND window, int x, int y, int width, int height, LPCSTR buttonText) {

    //for getting input from the button
    HMENU menu;
    if (buttonText == "<") {
       menu = (HMENU)IDC_LEFT_BUTTON;
    }
    else if (buttonText == ">") {
        menu = (HMENU)IDC_RIGHT_BUTTON;
    }
    else if (buttonText == "Play") {
        menu = (HMENU)IDC_PLAY_BUTTON;
    }
    else {
        menu = NULL;
    }

    HWND hwndButton = CreateWindowA("Button", buttonText, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        x, y, width, height, window, menu, (HINSTANCE)GetWindowLongPtr(window, GWLP_HINSTANCE), NULL);

    return hwndButton;
}

//gets the text from a button as a string
string getButtonText(HWND window, int resoruce) {

    TCHAR buffer[256]; //create tchar buffer
    GetDlgItemText(window, resoruce, (LPWSTR)&buffer, 256); // store item text into buffer

    wstring tchar2wstr(&buffer[0]); //convert buffer into wstring
    string wstr2str(tchar2wstr.begin(), tchar2wstr.end()); //convert to string.

    return wstr2str;
}
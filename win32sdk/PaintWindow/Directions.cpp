#include <Windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("windows GUI");
    static TCHAR szWindowCaption[] = TEXT("Directions");

    WNDCLASSEX wndEx;
    MSG msg;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HWND hWnd = NULL;

    hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    if(hBrush == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to hBrush"), TEXT("GetStockObject"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    if(hCursor == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to hCursor"), TEXT("LoadCursor"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIcon == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to hIcon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIconSm == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.hInstance = hInstance;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassEx(&wndEx)){
        MessageBox((HWND)NULL, TEXT("Failed to register class"), TEXT("RegisterClassEx"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowCaption,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    if(hWnd == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to window"), TEXT("CreateWindowEx"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, (HWND)NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    static int cxClient, cyClient;
    static int cxChar, cyChar;

    static TCHAR *Direction[] = {
        TEXT("North"),
        TEXT("WEST"),
        TEXT("EAST"),
        TEXT("SOUTH")
    };

    HDC hdc = NULL;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch(uMsg){
        case WM_CREATE:
            hdc = GetDC(hWnd);
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hWnd, hdc);
            hdc = NULL;
            break;

        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            
            SetTextAlign(hdc, TA_TOP | TA_CENTER);
            TextOut(hdc, cxClient/2, 0, Direction[0], lstrlen(Direction[0]));

            SetTextAlign(hdc, TA_LEFT | TA_CENTER);
            TextOut(hdc, 0, cyClient/2, Direction[1], lstrlen(Direction[1]));

            SetTextAlign(hdc, TA_RIGHT | TA_CENTER);
            TextOut(hdc, cxClient, cyClient/2, Direction[2], lstrlen(Direction[2]));

            SetTextAlign(hdc, TA_CENTER | TA_BOTTOM);
            TextOut(hdc, cxClient/2, cyClient, Direction[3], lstrlen(Direction[3]));

            EndPaint(hWnd, &ps);
            hdc = NULL;
            break;

        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


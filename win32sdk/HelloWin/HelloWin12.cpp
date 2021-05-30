#include <Windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("Window GUI");
    static TCHAR szWindowCaption[] = TEXT("GUI 13");

    WNDCLASSEX wndEx;
    MSG msg;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HWND hWnd = NULL;

    hBrush = (HBRUSH) GetStockObject(WHITE_BRUSH);
    if(hBrush == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to hBrush"), TEXT("GetStockObject"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    if(hCursor == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to hCursor"), TEXT("LoadCursor"), MB_ICONERROR);
        return(EXIT_FAILURE);
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

    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.lpszClassName =szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassEx(&wndEx)){
        MessageBox((HWND)NULL, TEXT("Failed to register window class"), TEXT("RegisterClassEx"), MB_ICONERROR);
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
        MessageBox((HWND)NULL, TEXT("Failed to create window handle"), TEXT("CreateWindowEx"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, (HWND)NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return EXIT_SUCCESS;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){
        case WM_DESTROY: 
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam)); 
}
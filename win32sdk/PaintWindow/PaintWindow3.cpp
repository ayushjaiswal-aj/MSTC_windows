#include <Windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("StandardWindow");
    static TCHAR szWindowCaption[] = TEXT("StandardWindow");

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hSmallIcon = NULL;
    HWND hWnd = NULL;

    WNDCLASSEX wndEx;
    MSG msg;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    if(hBrush == NULL){
        MessageBox((HWND)NULL, TEXT("Cannot get handle to brush"), TEXT("GetStockObject"), MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    if(hCursor == NULL){
        MessageBox((HWND)NULL, TEXT("Cannot get handle to cursor"), TEXT("LoadCursor"), MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIcon = NULL){
        MessageBox((HWND)NULL, TEXT("Cannnot get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    hSmallIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hSmallIcon == NULL){
        MessageBox((HWND)NULL, TEXT("Cannot get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    wndEx.hIcon = hIcon;
    wndEx.hIconSm =hSmallIcon;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.lpfnWndProc = WndProc;
    wndEx.hInstance = hInstance;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassEx(&wndEx)){
        MessageBox((HWND)NULL, TEXT("Cannot register window class"), TEXT("RegisterClassEx"), MB_ICONERROR);
        exit(EXIT_FAILURE);
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

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, (HWND)NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    exit(EXIT_SUCCESS);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    static int cxClient;
    static int cyClient;

    CHAR* lpszMsg = "Hello, World!";
    int iLenght = strlen(lpszMsg);

    HDC hdc = NULL;
    PAINTSTRUCT ps;

    switch(uMsg){
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            SetTextAlign(hdc, TA_CENTER);
            TextOutA(hdc, cxClient/2, cyClient/2, lpszMsg, iLenght);
            EndPaint(hWnd, &ps);
            hdc = NULL;
            break;
        
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
} 
#include <Windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("Gui Window");
    static TCHAR szWindowCaption[] = TEXT("GUI - 8");

    WNDCLASSEX wndEx;
    MSG msg;

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HWND hWnd = NULL;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    hBrush = (HBRUSH) GetStockObject(BLACK_BRUSH);
    if(hBrush == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to brush"), TEXT("GetStockObject"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_UPARROW);
    if(hCursor == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to cursor"), TEXT("LoadCursor"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_ASTERISK);
    if(hIcon == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_ASTERISK);
    if(hIconSm == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);  
    }

    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.style = CS_VREDRAW | CS_HREDRAW;

    if(!RegisterClassEx(&wndEx)){
        MessageBox((HWND)hWnd, TEXT("Failed to register window class"), TEXT("RegisterClassEx"), MB_ICONERROR);
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

    if(hWnd ==NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to window"), TEXT("CreateClassEx"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, (HWND)NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (EXIT_SUCCESS);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

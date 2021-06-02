#include <Windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("Window GUI");
    static TCHAR szWindowCaption[] = TEXT("Corners");

    WNDCLASSEX wndEx;
    MSG msg;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HWND hWnd = NULL;

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    if(hBrush == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to brush"), TEXT("GetStockObject"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    if(hCursor == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to cursor"), TEXT("LoadCursor"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIcon == NULL){
        MessageBox((HWND)NULL, TEXT("failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIconSm == NULL){
        MessageBox((HWND)NULL, TEXT("failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbWndExtra = 0;
    wndEx.cbClsExtra = 0;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;
    wndEx.hInstance = hInstance;

    if(!RegisterClassEx(&wndEx)){
        MessageBox((HWND)NULL, TEXT("Failed to window class"), TEXT("RegisterClassEx"), MB_ICONERROR);
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

    static TCHAR *ppszCorners[] = {
        TEXT("TOP-LEFT"),
        TEXT("TOP-RIGHT"),
        TEXT("BOTTOM-LEFT"),
        TEXT("BOTTOM-RIGHT")
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

            SetTextAlign(hdc, TA_TOP | TA_LEFT);
            TextOut(hdc, 0, 0, ppszCorners[0], lstrlen(ppszCorners[0]));

            SetTextAlign(hdc, TA_TOP | TA_RIGHT);
            TextOut(hdc, cxClient, 0, ppszCorners[1], lstrlen(ppszCorners[1]));

            SetTextAlign(hdc, TA_BOTTOM | TA_LEFT);
            TextOut(hdc, 0, cyClient, ppszCorners[2], lstrlen(ppszCorners[2]));

            SetTextAlign(hdc, TA_BOTTOM | TA_RIGHT);
            TextOut(hdc, cxClient, cyClient, ppszCorners[3], lstrlen(ppszCorners[3]));

            EndPaint(hWnd, &ps);
            hdc = NULL;
            break;
            
        case WM_DESTROY:
            PostQuitMessage(EXIT_FAILURE);
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
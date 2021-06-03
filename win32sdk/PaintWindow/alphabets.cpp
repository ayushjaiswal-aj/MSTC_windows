#include <Windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("GUI window");
    static TCHAR szWindowCaption[] = TEXT("alphabets");

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
        MessageBox((HWND)NULL, TEXT("Failed to get handle to brush"),  TEXT("GetStockObject"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    if(hCursor == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to cursor"), TEXT("LoadCursor"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIcon == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIconSm == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;
    wndEx.hInstance = hInstance;

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
        540,
        560,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    if(hWnd == NULL){
        MessageBox((HWND)NULL, TEXT("failed to get handle to window"), TEXT("CreateWindowEx"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    static int cxClient, cyClient;
    static int cxChar, cyChar;

    static TCHAR *ppAlphabets[] = {
        TEXT("A"),
        TEXT("B"),
        TEXT("C"),
        TEXT("D"),
        TEXT("E"),
        TEXT("F"),
        TEXT("G"),
        TEXT("H"),
        TEXT("I"),
        TEXT("J"),
        TEXT("K"),
        TEXT("L"),
        TEXT("M"),
        TEXT("N"),
        TEXT("O"),
        TEXT("P"),
        TEXT("Q"),
        TEXT("R"),
        TEXT("S"),
        TEXT("T"),
        TEXT("U"),
        TEXT("V"),
        TEXT("W"),
        TEXT("X"),
        TEXT("Y"),
        TEXT("Z")
    }; 

    int i, j = 0;

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

            for(i=0; i<26; i++){
                SetTextAlign(hdc, TA_TOP | TA_LEFT);
                TextOut(hdc, i*20, i*20, ppAlphabets[i], 1);
            }

            EndPaint(hWnd, &ps);
            hdc = NULL;
            
            break;

        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}
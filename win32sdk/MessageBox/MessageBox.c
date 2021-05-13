#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    MessageBox((HWND) NULL, TEXT("This is my first win32sdk code."), TEXT("Greetins"), MB_OK);
    return 0;
}
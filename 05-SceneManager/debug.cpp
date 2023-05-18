#include <Windows.h>
#include "debug.h"

HWND _hwnd = NULL;

void DebugOut(const wchar_t* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

// void DebugOutTitle(const wchar_t* fmt, ...)
// {
// 	wchar_t s[1024];
// 	VA_PRINTS(s);
// 	SetWindowText(_hwnd, s);
// }

void DebugOutTitle(const wchar_t* fmt, ...)
{
    wchar_t s[1024];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf_s(s, sizeof(s) / sizeof(wchar_t), _TRUNCATE, fmt, args);
    va_end(args);
    SetWindowText(_hwnd, s);
}

void SetDebugWindow(HWND hwnd)
{
	_hwnd = hwnd;
}
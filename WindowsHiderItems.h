STRUCT(tagWNDCLASSA, { UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance; HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground; LPCSTR lpszMenuName; LPCSTR lpszClassName; }, WNDCLASSA)
STRUCT(tagWNDCLASSW, { UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance; HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground; LPCWSTR lpszMenuName; LPCWSTR lpszClassName; }, WNDCLASSW)
ALIAS(unsigned int, UINT)
ALIAS(unsigned int, UINT_PTR)
ALIAS(char*, STR)
ALIAS(wchar_t*, WSTR)
ALIAS(void*, HANDLE)
ALIAS(HANDLE, HINSTANCE)
ALIAS(HANDLE, HWND)
ALIAS(HANDLE, HICON)
ALIAS(HANDLE, HBRUSH)
ALIAS(HICON, HCURSOR)
ALIAS(UINT_PTR, WPARAM)
ALIAS(long, LONG_PTR)
ALIAS(LONG_PTR, LPARAM)
ALIAS(LONG_PTR, LRESULT)
TYPE(LRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM), WNDPROC)
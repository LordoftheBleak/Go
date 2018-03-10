/*
!!!INSTRUCTIONS!!!
	There are 7 different X macros that can be used. This will show you what they are, how to use them, and what to use them for.
	The macros are naturally parsed from top to bottom.
	They are handled in this order:
		"MAKE_HANDLE".
		"STRUCT" aliases, but not definitions.
		"ALIAS", "TYPE", and "UTILITY".
		"STRUCT" definitions.
		"FUNCTION".
		"VALUE".
	There are also compile/run time checks to make sure everything matches up.
		"ALIAS" checks that "alias" is the same type (compile-time).
		"TYPE" checks that "alias" is the same type (compile-time).
		"STRUCT" and "MAKE_HANDLE" checks that the struct has the same size and alignment (compile-time).
		"VALUE" checks that the values are the same (run-time).
	"FUNCTION" doesn't have any checks performed, but will fail if the correct function isn't found.


ALIAS(identifier, alias)
	The Windows API has lots of aliases where it puts (L)P and/or C in front of a type to signify it is a pointer and/or constant.
	ALIAS creates all these typedefs at once.
	EX: ALIAS(int, INT)

TYPE(type, alias)
	This is for times when "ALIAS" doesn't work properly, like when making a function pointer alias. It follows a different syntax than normal.
	EX: TYPE(void(*)(), FPTR)

STRUCT(identifier, body, alias)
	Creates the struct with that body and typedefs it.
	EX: STRUCT(Foo, { int _foo; int _bar; }, Bar)

VALUE(type, identifier, value)
	Creates a constant. They are all constant expressions, however there is one problem.
	Sometimes Windows constants are macros like (void*)(-1), and this is not a compile time constant.
	When this happens, it creates an instance of a constexpr type that can be implicitly converted to the correct pointer value.
	If "type" is a pointer value, remove any casts to pointer from the "value" part. Any other casts can be left in.
	EX: VALUE(int, foo, 42)
	EX: VALUE(void*, INVALID_PTR, -1)

FUNCTION(return, convention, identifier, param_types, param_names, param_list)
	Creates a function. This function is actually a function reference to another function. None of the functions are inline.
	"convention" can be left blank for the default, but everything is probably __stdcall.
	"param_types" is a parenthetically enclosed list of the types of the params.
	"param_values" is a parenthetically enclosed list of the names of the params.
	"param_list" is a parenthetically enclosed list of the types AND names of the params. This one is repetitive, but so far there is no workaround.
	EX: FUNCTION(int, __stdcall, pow, (int, int), (base, exp), (int base, int exp))

UTILITY(anything)
	This exists for writing declarations outside of the Windows API.
	This is useful in times when you want to make an alias but not have it be checked at compile time.
	One such case is the VOID aliases. PVOID is an alias of VOID, but VOID is only a macro.
	If you were to only write ALIAS(void, VOID), it would cause an error. Instead, wrap it in UTILITY.
	EX: UTILITY(ALIAS(void, VOID))
	EX: UTILITY(typedef something SOMETHING;)

MAKE_HANDLE(identifier)
	A fair amount of Windows handle types are spawned from this one macro.
	The user facing identifier is a pointer to a struct of the name suffixed with "__", whose only member is "int unused"
	This macro does the same thing.
	EX: MAKE_HANDLE(HWND)
	EX: MAKE_HANDLE(HINSTANCE)
*/

STRUCT(tagWNDCLASSA, { UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance; HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground; LPCSTR lpszMenuName; LPCSTR lpszClassName; }, WNDCLASSA)
STRUCT(tagWNDCLASSW, { UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance; HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground; LPCWSTR lpszMenuName; LPCWSTR lpszClassName; }, WNDCLASSW)
UTILITY(ALIAS(void, VOID))
UTILITY(ALIAS(char, STR))
UTILITY(ALIAS(wchar_t, WSTR))
MAKE_HANDLE(HINSTANCE)
MAKE_HANDLE(HWND)
MAKE_HANDLE(HICON)
MAKE_HANDLE(HBRUSH)
UTILITY(typedef HICON HCURSOR;)
ALIAS(unsigned int, UINT)
ALIAS(unsigned int, UINT_PTR)
ALIAS(PVOID, HANDLE)
ALIAS(UINT_PTR, WPARAM)
ALIAS(long, LONG_PTR)
ALIAS(LONG_PTR, LPARAM)
ALIAS(LONG_PTR, LRESULT)
TYPE(LRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM), WNDPROC)

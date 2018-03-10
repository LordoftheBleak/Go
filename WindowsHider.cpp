#include <stdexcept>

#include "WindowsHider.h"

#pragma warning(push)
#pragma warning(disable : 4005)
#pragma push_macro("ALIAS")
#pragma push_macro("TYPE")
#pragma push_macro("STRUCT")
#pragma push_macro("VALUE")
#pragma push_macro("FUNCTION")

#define ALIAS(...)
#define TYPE(...)
#define STRUCT(...)
#define FUNCTION(...)

//New names for constants to avoid macro conflicts
#define VALUE(type, identifier, value) constexpr auto& detail##identifier = identifier;
namespace bleaklib
{
	namespace windows
	{
		namespace detail
		{
#include "WindowsHiderItems.h"
		}
	}
}
#define VALUE(...)

//More annoying implementation stuff
namespace bleaklib
{
	namespace windows
	{
		namespace detail
		{
			bool Ugh(...) { return true; }
			template <class T, class V>
			bool SpecialAssert(T a, V b)
			{
				if (!(a == b))
					throw std::exception();
				return true;
			}
		}
	}
}

#include <Windows.h>

//Test sizeof/alignof of structs
//Test that aliases are identical
#define STRUCT(identifier, body, alias) static_assert(sizeof(bleaklib::windows::identifier) == sizeof(identifier) && alignof(bleaklib::windows::identifier) == alignof(identifier), "Size or alignment of "#identifier" is incorrect.");
#define ALIAS(identifier, alias) static_assert(std::is_same_v<bleaklib::windows::alias, alias>, "Alias "#alias" is incorrect.");
#define TYPE(type, alias) static_assert(std::is_same_v<alias, type>, "Alias "#alias" is incorrect.");
#include "WindowsHiderItems.h"
#define STRUCT(...)
#define ALIAS(...)
#define TYPE(...)

//Test that constants are identical
#define VALUE(type, identifier, value) , bleaklib::windows::detail::SpecialAssert(bleaklib::windows::detail::detail##identifier, identifier)
bool detail = bleaklib::windows::detail::Ugh(0
#include "WindowsHiderItems.h"
);
#define VALUE(...)


namespace bleaklib
{
	namespace windows
	{
		namespace detail
		{
			template <class>
			struct GetFunctionType;
			template <class R, class... A>
			struct GetFunctionType<R(__stdcall *)(A...)>
			{
				typedef R type(A...);
			};



			template <class From, class To>
			struct Caster
			{
				To _value;
				Caster(From value)
				{
					std::memcpy(&_value, &value, sizeof(_value));
				}
				operator To&()
				{
					return _value;
				}
			};
			template <class T>
			struct Caster<T, T>
			{
				const T& _value;
				Caster(const T& value) : _value(value) {}
				operator const T&()
				{
					return _value;
				}
			};
			template <class From, class To>
			struct Caster<From*, To*>
			{
				From* _from;
				To _to;
				Caster(From* from) : _from(from)
				{
					std::memcpy(&_to, _from, sizeof(To));
				}
				~Caster()
				{
					std::memcpy(_from, &_to, sizeof(To));
				}
				operator To*()
				{
					return &_to;
				}
			};

			template <class, class>
			struct Caller;
			template <class MyR, class... MyA, class WinR, class... WinA>
			struct Caller<MyR(MyA...), WinR __stdcall (WinA...)>
			{
				template <class WinF, WinF Func>
				static MyR Call(MyA&... args)
				{
					return Caster<WinR, MyR>(Func(Caster<MyA, WinA>(args)...));
				}
			};
#define FUNCTION(ret, call, identifier, p1, p2, p3) ret call detail##identifier p3 { return Caller<ret p1, decltype(::identifier)>::Call<decltype(::identifier), ::identifier> p2;  }
#include "WindowsHiderItems.h"
		}
	}
}

#pragma pop_macro("ALIAS")
#pragma pop_macro("STRUCT")
#pragma pop_macro("VALUE")
#pragma pop_macro("FUNCTION")
#pragma warning(pop)
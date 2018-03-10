#pragma once

#include <type_traits>

#pragma warning(push)
#pragma warning(disable : 4005)
#pragma push_macro("ALIAS")
#pragma push_macro("TYPE")
#pragma push_macro("STRUCT")
#pragma push_macro("VALUE")
#pragma push_macro("FUNCTION")
#pragma push_macro("UTILITY")
#pragma push_macro("MAKE_HANDLE")

namespace bleaklib
{
	namespace windows
	{
#define ALIAS(...)
#define TYPE(...)
#define VALUE(...)
#define FUNCTION(...)
#define UTILITY(...)
#define STRUCT(...)

		//Handle types
#define MAKE_HANDLE(identifier) typedef struct identifier##__ { int unused; } *identifier;
#include "WindowsHiderItems.h"
#define MAKE_HANDLE(...)

		//Type aliases for struct names
#define STRUCT(identifier, body, alias) struct identifier; typedef identifier alias, *P##alias, *LP##alias; typedef const identifier C##alias, *PC##alias, *LPC##alias;
#include "WindowsHiderItems.h"
#define STRUCT(...)

		//Type aliases
#define ALIAS(identifier, alias) typedef identifier alias, *P##alias, *LP##alias; typedef const identifier C##alias, *PC##alias, *LPC##alias;
#define TYPE(type, alias) using alias = type;
#define UTILITY(...) __VA_ARGS__
#include "WindowsHiderItems.h"
#define ALIAS(...)
#define TYPE(...)
#define UTILITY(...)

		//Struct definitions
#define STRUCT(identifier, body, alias) struct identifier body;
#include "WindowsHiderItems.h"
#define STRUCT(...)

		namespace detail
		{
			//Function declarations
#define FUNCTION(ret, call, identifier, param_types, param_names, param_list) ret call detail##identifier param_list;
#include "WindowsHiderItems.h"
		}
		//Function reference declarations
#define FUNCTION(ret, call, identifier, param_types, param_names, param_list) constexpr ret (call &identifier) param_list = detail::detail##identifier;
#include "WindowsHiderItems.h"
#define FUNCTION(...)

		//Implementation stuff
		namespace detail
		{
			template <typename ValueType, typename PointerType>
			class PointerHack
			{
			public:
				constexpr PointerHack(const ValueType& value) : _value(value) {}
				operator PointerType() const
				{
					return reinterpret_cast<PointerType>(_value);
				}
				constexpr bool operator==(const PointerHack& other)
				{
					return _value == other._value;
				}
			private:
				const ValueType _value;
			};

			template <class T, class V>
			struct PickType
			{
				typedef std::conditional_t<std::is_pointer_v<T> && !std::is_pointer_v<V>, PointerHack<V, T>, T> type;
			};
			template <class T, class V>
			using PickType_t = typename PickType<T, V>::type;
		}

		//Constant definitons
#define VALUE(type, identifier, value) constexpr detail::PickType_t<type, decltype(value)> identifier = value;
#include "WindowsHiderItems.h"
#define VALUE(...)
	}
}

#pragma pop_macro("ALIAS")
#pragma pop_macro("TYPE")
#pragma pop_macro("STRUCT")
#pragma pop_macro("VALUE")
#pragma pop_macro("FUNCTION")
#pragma pop_macro("UTILITY")
#pragma pop_macro("MAKE_HANDLE")
#pragma warning(pop)
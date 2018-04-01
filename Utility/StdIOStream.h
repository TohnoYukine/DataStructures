#pragma once
#include <cstdio>
#include <type_traits>
#include "boost\mpl\string.hpp"

/*
	Stream adaptor for fprintf_s and fscanf_s
	Compile time format string generation

	String state is not fully implemented
*/

class IOStreamBase
{
public:
	inline IOStreamBase(FILE* s, bool _owns) : stream(s), owns(_owns) { if (!stream) throw std::runtime_error{ "Fail to open stream!" }; }
	inline ~IOStreamBase() { if (owns) fclose(stream); }

	inline operator bool() const { return (stat & (Stat::fail | Stat::bad)) == Stat::good; }
	inline bool operator!() const { return !operator bool(); }
	inline bool good() const { return stat == Stat::good; }
	inline bool eof() const { return (stat & Stat::eof) != Stat::good; }
	inline bool bad() const { return (stat & Stat::bad) != Stat::good; }
	inline bool fail() const { return (stat & (Stat::eof | Stat::fail | Stat::bad)) != Stat::good; }

protected:
	FILE * stream;
	bool owns;
	const char* format_string = nullptr;
	unsigned cnt;

	enum class Stat { good = 0, eof = 1, fail = 2, bad = 4 } stat;
	friend inline constexpr Stat operator|(Stat lhs, Stat rhs)
	{
		return static_cast<Stat>(static_cast<char>(lhs) | static_cast<char>(rhs));
	}
	friend inline constexpr Stat operator&(Stat lhs, Stat rhs)
	{
		return static_cast<Stat>(static_cast<char>(lhs) & static_cast<char>(rhs));
	}

public:

	template <bool b, size_t N>
	struct IntegerToStringHelper
	{
		using type = typename 
			boost::mpl::push_back<
			typename IntegerToStringHelper<N <= 9U, N / 10>::type,
			boost::mpl::char_<'0' + N % 10>
			>::type;
	};

	template <>
	struct IntegerToStringHelper<true, 0>
	{
		using type = boost::mpl::string<>;
	};

	template <size_t N>
	struct IntegerToString
	{
		 using type = typename IntegerToStringHelper<N <= 9U, N>::type;
	};

	template<typename T>
	inline constexpr const char* FormattingPlaceholder()
	{
		return
			std::is_same_v<T, char>			? "%c" :
			std::is_same_v<T, char*>		? "%s" :
			std::is_same_v<T, const char*>	? "%s" :
			std::is_same_v<T, int>			? "%d" :
			std::is_same_v<T, long>			? "%ld" :
			std::is_same_v<T, short>		? "%hi" :
			std::is_same_v<T, unsigned>		? "%u" :
			std::is_same_v<T, float>		? "%f" :
			std::is_same_v<T, double>		? "%lf" :
			std::is_same_v<T, long double>	? "%Lf" :
			std::is_array_v<T> ?
				std::is_same_v<typename std::decay_t<T>, char*>	? boost::mpl::c_str<boost::mpl::push_back<boost::mpl::push_front<IntegerToString<std::extent_v<T> - 1U>::type, boost::mpl::char_<'%'>>::type, boost::mpl::char_<'s'>>::type>::value : 
				throw std::runtime_error{ "Compile Time Format String Identification Failed!\n" } :
			throw std::runtime_error{ "Compile Time Format String Identification Failed!\n" };
	}

	inline void set_state(int i) { stat = i > 0 ? Stat::good : Stat::fail; }
};

class InStream : public IOStreamBase
{
public:
	inline InStream(FILE* s, bool _owns = true) : IOStreamBase(s, _owns) {}

	inline InStream& operator()(const char* fstr, unsigned n) { format_string = fstr, cnt = n; return *this; }

	//Works only on arithmetic types, such as int, double...
	template<typename Type>
	inline InStream& operator>>(Type& object)
	{
		if (format_string)
		{
			if (std::is_pointer_v<Type>)
				set_state(fscanf_s(stream, format_string, object, cnt));
			else
				set_state(fscanf_s(stream, format_string, &object, cnt));
		}
		else
			set_state(fscanf_s(stream, FormattingPlaceholder<Type>(), &object));
		format_string = nullptr;
		return *this;
	}
};

static InStream Stdin(stdin, false); 


class OutStream : public IOStreamBase
{
public:
	inline OutStream(FILE* s, bool _owns = true) : IOStreamBase(s, _owns) {}

	inline OutStream& operator()(const char* fstr, unsigned n) { format_string = fstr, cnt = n; return *this; }

	template<typename Type, typename SFINAE = typename std::enable_if_t<!std::is_same_v<typename std::decay_t<Type>, char*>>>
	inline OutStream& operator<<(const Type& object)
	{
		if (format_string)
			set_state(fprintf_s(stream, format_string, object));
		else
			set_state(fprintf_s(stream, FormattingPlaceholder<Type>(), object));
		format_string = nullptr;
		return *this;
	}
	inline OutStream& operator<<(const char* object)
	{
		if (format_string)
			set_state(fprintf_s(stream, format_string, object));
		else
			set_state(fprintf_s(stream, object));
		format_string = nullptr;
		return *this;
	}
};

static OutStream Stdout(stdout, false);
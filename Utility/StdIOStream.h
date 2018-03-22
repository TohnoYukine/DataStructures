#pragma once
#include <cstdio>
#include <type_traits>

class IOStreamBase
{
public:
	inline IOStreamBase(FILE* s, bool _owns) : stream(s), owns(_owns) {}
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

	template<typename T>
	inline constexpr const char* FormattingPlaceholder()
	{
		return
			std::is_same_v<T, char> ? "%c" :
			std::is_same_v<T, char*> ? "%s" :
			std::is_same_v<T, const char*> ? "%s" :
			std::is_same_v<typename std::decay_t<T>, char*> ? "%s" :
			std::is_same_v<typename std::decay_t<T>, const char*> ? "%s" :
			std::is_same_v<T, int> ? "%d" :
			std::is_same_v<T, long> ? "%ld" :
			std::is_same_v<T, short> ? "%hi" :
			std::is_same_v<T, unsigned> ? "%u" :
			std::is_same_v<T, float> ? "%f" :
			std::is_same_v<T, double> ? "%lf" :
			std::is_same_v<T, long double> ? "%Lf" : "Compile Time Format String Identification Failed!\n";
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
		else if (std::is_arithmetic_v<Type>)
			set_state(fscanf_s(stream, FormattingPlaceholder<Type>(), &object));
		else set_state(0);
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

	template<typename Type>
	inline OutStream& operator<<(const Type& object)
	{
		if (format_string)
			set_state(fprintf_s(stream, format_string, object));
		else
			set_state(fprintf_s(stream, FormattingPlaceholder<Type>(), object));
		format_string = nullptr;
		return *this;
	}
};

static OutStream Stdout(stdout, false);
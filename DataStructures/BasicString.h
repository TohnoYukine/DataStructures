#pragma once
#include <stdexcept>
#include <string>

#define MAX_STRING_SIZE -1U

namespace DataStructures
{
	template<typename CharT = char, typename Traits = std::char_traits<CharT>> class BasicString;
	using String = BasicString<char>;
	using WString = BasicString<wchar_t>;

	template<typename CharT, typename Traits>
	class BasicString
	{
	public:
		using traits_type = Traits;
		using value_type = CharT;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using reference = CharT&;
		using const_reference = const CharT&;
		using pointer = CharT*;
		using const_pointer = const CharT*;

		using iterator = CharT*;
		using const_iterator = const CharT*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		static const size_type npos = -1;

		//Constructor, Destructor and Assignment
		explicit BasicString() noexcept;
		explicit BasicString(size_type n, const CharT& val);
		BasicString(const BasicString& other, size_type pos, size_type n = npos);
		BasicString(const CharT* s, size_type n);
		BasicString(const CharT* s);
		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		BasicString(InputIterator first, InputIterator last);
		BasicString(std::initializer_list<CharT> init);

		BasicString(const BasicString& origin);
		BasicString(BasicString&& origin) noexcept;
		~BasicString();

		BasicString& operator=(const BasicString& origin);
		BasicString& operator=(BasicString&& origin);
		BasicString& operator=(const CharT* s);
		BasicString& operator=(CharT ch);
		BasicString& operator=(std::initializer_list<CharT> init);

		BasicString& assign(size_type n, CharT ch);
		BasicString& assign(const BasicString& origin);
		BasicString& assign(const BasicString& origin, size_type pos, size_type n = npos);
		BasicString& assign(BasicString&& origin);
		BasicString& assign(const CharT* s, size_type n);
		BasicString& assign(const CharT* s);
		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		BasicString& assign(InputIterator first, InputIterator last);
		BasicString& assign(std::initializer_list<CharT> init);

		//Element access
		reference at(size_type index);				//Check and throw out_of_range exception
		const_reference at(size_type index) const;
		reference operator[](size_type index);		//No check
		const_reference operator[](size_type index) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		CharT* data();
		const CharT* data() const;
		const CharT* c_str() const;

		//Iterators
		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		const_reverse_iterator crbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		const_reverse_iterator crend() const;

		//Capacity
		bool empty() const;
		size_type size() const;
		size_type length() const;
		size_type max_size() const;
		void reserve(size_type n = 0);
		size_type capacity() const;
		void shrink_to_fit();

		//Modifiers
		void clear() noexcept;
		BasicString& insert(size_type pos, size_type n, CharT ch);
		BasicString& insert(size_type pos, const CharT* s);
		BasicString& insert(size_type pos, const CharT* s, size_type n);
		BasicString& insert(size_type pos, const BasicString& str);
		BasicString& insert(size_type pos, const BasicString& str, size_type str_pos, size_type n);
		iterator insert(const_iterator pos, CharT ch);
		iterator insert(const_iterator pos, size_type n, CharT ch);
		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last);	//last not included
		iterator insert(const_iterator pos, std::initializer_list<CharT> init);

		BasicString& erase(size_type pos = 0, size_type n = npos);
		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);	//last not included

		void push_back(CharT val);
		void pop_back();

		BasicString& append(size_type n, CharT ch);
		BasicString& append(const BasicString& str);
		BasicString& append(const BasicString& str, size_type pos, size_type n);
		BasicString& append(const CharT* s, size_type n);
		BasicString& append(const CharT* s);
		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		BasicString& append(InputIterator first, InputIterator last);	//last not included
		BasicString& append(std::initializer_list<CharT> init);

		BasicString& operator+=(const BasicString& str);
		BasicString& operator+=(CharT ch);
		BasicString& operator+=(const CharT* s);
		BasicString& operator+=(std::initializer_list<CharT> init);

		int compare(const BasicString& str) const;
		int compare(size_type pos1, size_type count1, const BasicString& str) const;
		int compare(size_type pos1, size_type count1, const BasicString& str, size_type pos2, size_type count2 = npos) const;
		int compare(const CharT* s) const;
		int compare(size_type pos1, size_type count1, const CharT* s) const;
		int compare(size_type pos1, size_type count1, const CharT* s, size_type count2) const;

		BasicString& replace(size_type pos, size_type count, const BasicString& str);
		BasicString& replace(const_iterator first, const_iterator last, const BasicString& str);

		BasicString& replace(size_type pos, size_type count, const BasicString& str, size_type pos2, size_type count2 = npos);

		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		BasicString& replace(const_iterator first, const_iterator last, InputIterator first2, InputIterator last2);

		BasicString& replace(size_type pos, size_type count, const CharT* cstr, size_type count2);
		BasicString& replace(const_iterator first, const_iterator last, const CharT* cstr, size_type count2);

		BasicString& replace(size_type pos, size_type count, const CharT* cstr);
		BasicString& replace(const_iterator first, const_iterator last, const CharT* cstr);

		BasicString& replace(size_type pos, size_type count, size_type count2, CharT ch);
		BasicString& replace(const_iterator first, const_iterator last, size_type count2, CharT ch);

		BasicString& replace(const_iterator first, const_iterator last, std::initializer_list<CharT> init);

		BasicString substr(size_type pos = 0, size_type n = npos) const;
		size_type copy(CharT* dest, size_type n, size_type pos = 0) const;

		void resize(size_type n);					//Fill with default initialized element
		void resize(size_type n, CharT ch);			//Fill with val
		void swap(BasicString& other) noexcept;

		//Search
		size_type find(const BasicString& str, size_type pos = 0) const;
		size_type find(const CharT* s, size_type pos, size_type count) const;
		size_type find(const CharT* s, size_type pos = 0) const;
		size_type find(CharT ch, size_type pos = 0) const;

		size_type rfind(const BasicString& str, size_type pos = npos) const;
		size_type rfind(const CharT* s, size_type pos, size_type count) const;
		size_type rfind(const CharT* s, size_type pos = npos) const;
		size_type rfind(CharT ch, size_type pos = npos) const;

		size_type find_first_of(const BasicString& str, size_type pos = 0) const;
		size_type find_first_of(const CharT* s, size_type pos, size_type count) const;
		size_type find_first_of(const CharT* s, size_type pos = 0) const;
		size_type find_first_of(CharT ch, size_type pos = 0) const;

		size_type find_first_not_of(const BasicString& str, size_type pos = 0) const;
		size_type find_first_not_of(const CharT* s, size_type pos, size_type count) const;
		size_type find_first_not_of(const CharT* s, size_type pos = 0) const;
		size_type find_first_not_of(CharT ch, size_type pos = 0) const;

		size_type find_last_of(const BasicString& str, size_type pos = npos) const;
		size_type find_last_of(const CharT* s, size_type pos, size_type count) const;
		size_type find_last_of(const CharT* s, size_type pos = npos) const;
		size_type find_last_of(CharT ch, size_type pos = npos) const;

		size_type find_last_not_of(const BasicString& str, size_type pos = npos) const;
		size_type find_last_not_of(const CharT* s, size_type pos, size_type count) const;
		size_type find_last_not_of(const CharT* s, size_type pos = npos) const;
		size_type find_last_not_of(CharT ch, size_type pos = npos) const;


		//Non-Member Functions
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(const BasicString<CharT, Traits>& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(const CharT* lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(CharT lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(const BasicString<CharT, Traits>& lhs, const CharT* rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(const BasicString<CharT, Traits>& lhs, CharT rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(BasicString<CharT, Traits>&& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(const BasicString<CharT, Traits>& lhs, BasicString<CharT, Traits>&& rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(BasicString<CharT, Traits>&& lhs, BasicString<CharT, Traits>&& rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(const CharT* lhs, BasicString<CharT, Traits>&& rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(CharT lhs, BasicString<CharT, Traits>&& rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(BasicString<CharT, Traits>&& lhs, const CharT* rhs);
		template<typename CharT, typename Traits>
		friend BasicString<CharT, Traits> operator+(BasicString<CharT, Traits>&& lhs, CharT rhs);

		template<typename CharT, typename Traits> friend bool operator==(const BasicString<CharT, Traits>& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator!=(const BasicString<CharT, Traits>& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator<(const BasicString<CharT, Traits>& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator<=(const BasicString<CharT, Traits>& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator>(const BasicString<CharT, Traits>& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator>=(const BasicString<CharT, Traits>& lhs, const BasicString<CharT, Traits>& rhs);

		template<typename CharT, typename Traits> friend bool operator==(const CharT* lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator!=(const CharT* lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator<(const CharT* lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator<=(const CharT* lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator>(const CharT* lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator>=(const CharT* lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits> friend bool operator==(const BasicString<CharT, Traits>& lhs, const CharT* rhs);
		template<typename CharT, typename Traits> friend bool operator!=(const BasicString<CharT, Traits>& lhs, const CharT* rhs);
		template<typename CharT, typename Traits> friend bool operator<(const BasicString<CharT, Traits>& lhs, const CharT* rhs);
		template<typename CharT, typename Traits> friend bool operator<=(const BasicString<CharT, Traits>& lhs, const CharT* rhs);
		template<typename CharT, typename Traits> friend bool operator>(const BasicString<CharT, Traits>& lhs, const CharT* rhs);
		template<typename CharT, typename Traits> friend bool operator>=(const BasicString<CharT, Traits>& lhs, const CharT* rhs);

		template<typename CharT, typename Traits> friend void swap(BasicString<CharT, Traits>& lhs, BasicString<CharT, Traits>& rhs) noexcept;

		template <typename CharT, typename Traits> friend
		std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const BasicString<CharT, Traits>& str);
		template <typename CharT, typename Traits> friend
		std::basic_istream<CharT, Traits>& operator >> (std::basic_istream<CharT, Traits>& is, BasicString<CharT, Traits>& str);

		template<typename CharT, typename Traits> friend
		std::basic_istream<CharT, Traits>& getline(std::basic_istream<CharT, Traits>& input, BasicString<CharT, Traits>& str, CharT delim);
		template<typename CharT, typename Traits> friend
		std::basic_istream<CharT, Traits>& getline(std::basic_istream<CharT, Traits>&& input, BasicString<CharT, Traits>& str, CharT delim);
		template<typename CharT, typename Traits> friend
		std::basic_istream<CharT, Traits>& getline(std::basic_istream<CharT, Traits>& input, BasicString<CharT, Traits>& str);
		template<typename CharT, typename Traits> friend
		std::basic_istream<CharT, Traits>& getline(std::basic_istream<CharT, Traits>&& input, BasicString<CharT, Traits>& str);

		//Numeric conversions
		friend int       stoi(const String& str, std::size_t* pos, int base);
		friend int       stoi(const WString& str, std::size_t* pos, int base);
		friend long      stol(const String& str, std::size_t* pos, int base);
		friend long      stol(const WString& str, std::size_t* pos, int base);
		friend long long stoll(const String& str, std::size_t* pos, int base);
		friend long long stoll(const WString& str, std::size_t* pos, int base);

		friend unsigned long      stoul(const String& str, std::size_t* pos, int base);
		friend unsigned long      stoul(const WString& str, std::size_t* pos, int base);
		friend unsigned long long stoull(const String& str, std::size_t* pos, int base);
		friend unsigned long long stoull(const WString& str, std::size_t* pos, int base);

		friend float       stof(const String& str, std::size_t* pos);
		friend float       stof(const WString& str, std::size_t* pos);
		friend double      stod(const String& str, std::size_t* pos);
		friend double      stod(const WString& str, std::size_t* pos);
		friend long double stold(const String& str, std::size_t* pos);
		friend long double stold(const WString& str, std::size_t* pos);

		friend String to_string(int value);
		friend String to_string(long value);
		friend String to_string(long long value);
		friend String to_string(unsigned value);
		friend String to_string(unsigned long value);
		friend String to_string(unsigned long long value);
		friend String to_string(float value);
		friend String to_string(double value);
		friend String to_string(long double value);

		friend WString to_wstring(int value);
		friend WString to_wstring(long value);
		friend WString to_wstring(long long value);
		friend WString to_wstring(unsigned value);
		friend WString to_wstring(unsigned long value);
		friend WString to_wstring(unsigned long long value);
		friend WString to_wstring(float value);
		friend WString to_wstring(double value);
		friend WString to_wstring(long double value);

		//Literals
		//operator""s

		//Helper classes
		//hash(const String&)

	private:
		size_type reserved_size = 1;
		size_type string_length = 0;
		char* storage = nullptr;

		inline void _reallocate(size_type rsv_sz);
		inline void _move_storage(CharT* dest, CharT* from, size_type n);
		inline void _allocate(size_type rsv_sz);	//malloc some storage and set reserved_size to rsv_sz
		template <typename ... Args> inline void _construct(size_type pos, Args&& ... args);
		template <typename ... Args> inline void _construct(iterator iter, Args&& ... args);
		inline void _add_null_char(size_type pos);
	};

	/* Dividing Line (д├ бузе бу;)д├ (д├ бузе бу;)д├ (д├ бузе бу;)д├  */
	#define Tstorage reinterpret_cast<CharT*>(storage)
	#define Tsize sizeof(CharT)

	template<typename CharT, typename Traits>
	inline void BasicString<CharT, Traits>::_reallocate(size_type rsv_sz)
	{
		reserved_size = rsv_sz;
		storage = reinterpret_cast<char*>(realloc(storage, (reserved_size + 1) * Tsize));
	}

	template<typename CharT, typename Traits>
	inline void BasicString<CharT, Traits>::_move_storage(CharT * dest, CharT * from, size_type n)
	{
		if (dest < from)
		{
			CharT *_dest = dest, *_from = from;
			for (size_t i = 0; i < n; i++)
				*_dest++ = std::move(*_from++);
		}
		else if (dest > from)
		{
			CharT *_dest = dest + n - 1, *_from = from + n - 1;
			for (size_t i = n; i > 0; i--)
				*_dest-- = std::move(*_from--);
		}
		else
			return;
	}

	template<typename CharT, typename Traits>
	inline void BasicString<CharT, Traits>::_allocate(size_type rsv_sz)
	{
		reserved_size = rsv_sz;
		storage = reinterpret_cast<char*>(malloc((reserved_size + 1) * Tsize));
	}

	template<typename CharT, typename Traits>
	inline void BasicString<CharT, Traits>::_add_null_char(size_type pos)
	{
		new(Tstorage + pos) CharT(0);	//How to get a null character?
	}

	template<typename CharT, typename Traits>
	template<typename ...Args>
	inline void BasicString<CharT, Traits>::_construct(size_type pos, Args && ...args)
	{
		new(Tstorage + pos) CharT(std::forward<Args>(args) ...);
	}

	template<typename CharT, typename Traits>
	template<typename ...Args>
	inline void BasicString<CharT, Traits>::_construct(iterator iter, Args && ...args)
	{
		new(iter) CharT(std::forward<Args>(args) ...);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::BasicString() noexcept : string_length(0)
	{
		_allocate(0);
		_add_null_char(string_length);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::BasicString(size_type n, const CharT & val) : string_length(0)
	{
		_allocate(n);
		while (string_length < n)
		{
			//_construct(string_length++, val);	//In case of construction failure
			_construct(string_length, val);
			++string_length;
		}
		_add_null_char(string_length);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::BasicString(const BasicString & other, size_type pos, size_type n) : string_length(0)
	{
		if (pos < other.size() && n <= other.size() - pos)	//Caution! Overflow may occur!
		{
			_allocate(n);
			memcpy(storage, other.storage + pos * Tsize, n * Tsize);
			string_length = n;
		}
		else if (pos < other.size() && n > other.size() - pos)
		{
			size_type cnt = other.size() - pos;
			_allocate(cnt);
			memcpy(storage, other.storage + pos * Tsize, cnt * Tsize);
			string_length = cnt;
		}
		else
		{
			throw std::out_of_range{ "Assigned range exceed end of source string." };
		}
		_add_null_char(string_length);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::BasicString(const CharT * s, size_type n) : string_length(0)
	{
		_allocate(n);
		memcpy(storage, s, n * Tsize);
		string_length = n;
		_add_null_char(string_length);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::BasicString(const CharT * s) : string_length(0)
	{
		size_type n = Traits::length(s);
		_allocate(n);
		memcpy(storage, s, n * Tsize);
		string_length = n;
		_add_null_char(string_length);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::BasicString(std::initializer_list<CharT> init) : string_length(0)
	{
		size_type n = init.size();
		_allocate(n);
		for (const CharT& elem : init)
		{
			_construct(string_length, elem);
			++string_length;
		}
		string_length = n;
		_add_null_char(string_length);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::BasicString(const BasicString & origin) : string_length(0)
	{
		_allocate(origin.string_length);
		memcpy(storage, origin.storage, Tsize * origin.string_length);
		string_length = origin.string_length;
		_add_null_char(string_length);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::BasicString(BasicString && origin) noexcept
	{
		swap(origin);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits>::~BasicString()
	{
		clear();
		free(storage);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::operator=(const BasicString & origin)
	{
		return assign(origin);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::operator=(BasicString && origin)
	{
		return assign(std::move(origin));
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::operator=(const CharT * s)
	{
		return assign(s);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::operator=(CharT ch)
	{
		return assign(1, ch);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::operator=(std::initializer_list<CharT> init)
	{
		return assign(init);
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::assign(size_type n, CharT ch)
	{
		swap(BasicString(n, ch));
		return *this;
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::assign(const BasicString & origin)
	{
		if (this != &origin)
		{
			swap(BasicString(origin));
		}
		return *this;
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::assign(const BasicString & origin, size_type pos, size_type n)
	{
		swap(BasicString(origin, pos, n));
		return *this;
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::assign(BasicString && origin)
	{
		if (this != &origin)
		{
			swap(origin);
		}
		return *this;
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::assign(const CharT * s, size_type n)
	{
		swap(BasicString(s, n));
		return *this;
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::assign(const CharT * s)
	{
		swap(BasicString(s));
		return *this;
	}

	template<typename CharT, typename Traits>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::assign(std::initializer_list<CharT> init)
	{
		swap(BasicString(init));
		return *this;
	}

	template<typename CharT, typename Traits>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline BasicString<CharT, Traits>::BasicString(InputIterator first, InputIterator last) : string_length(0)
	{
		size_type n = std::distance(first, last);
		_allocate(n);
		for (size_t i = 0; i < n; i++)
		{
			_construct(Tstorage + i, *first++);
		}
		string_length = n;
		_add_null_char(string_length);
	}

	template<typename CharT, typename Traits>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline BasicString<CharT, Traits> & BasicString<CharT, Traits>::assign(InputIterator first, InputIterator last)
	{
		swap(BasicString(first, last));
		return *this;
	}

	template<typename CharT, typename Traits>
	inline void BasicString<CharT, Traits>::swap(BasicString & other) noexcept
	{
		using std::swap;
		swap(storage, other.storage);
		swap(reserved_size, other.reserved_size);
		swap(string_length, other.string_length);
	}

	template<typename CharT, typename Traits>
	inline void BasicString<CharT, Traits>::clear() noexcept
	{
		for (size_t i = 0; i < string_length; i++)
		{
			Tstorage[i].~CharT();
		}
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::reference BasicString<CharT, Traits>::at(size_type index)
	{
		if (index < string_length)
			return Tstorage[index];
		throw std::out_of_range{ "Accessed position is out of range!" };
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_reference BasicString<CharT, Traits>::at(size_type index) const
	{
		if (index < string_length)
			return Tstorage[index];
		throw std::out_of_range{ "Accessed position is out of range!" };
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::reference BasicString<CharT, Traits>::operator[](size_type index)
	{
		return Tstorage[index];
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_reference BasicString<CharT, Traits>::operator[](size_type index) const
	{
		return Tstorage[index];
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::reference BasicString<CharT, Traits>::front()
	{
		return Tstorage[0];
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_reference BasicString<CharT, Traits>::front() const
	{
		return Tstorage[0];
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::reference BasicString<CharT, Traits>::back()
	{
		return Tstorage[string_length - 1];
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_reference BasicString<CharT, Traits>::back() const
	{
		return Tstorage[string_length - 1];
	}

	template<typename CharT, typename Traits>
	inline CharT * BasicString<CharT, Traits>::data()
	{
		return Tstorage;
	}

	template<typename CharT, typename Traits>
	inline const CharT * BasicString<CharT, Traits>::data() const
	{
		return Tstorage;
	}

	template<typename CharT, typename Traits>
	inline const CharT * BasicString<CharT, Traits>::c_str() const
	{
		return Tstorage;
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::iterator BasicString<CharT, Traits>::begin()
	{
		return Tstorage;
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_iterator BasicString<CharT, Traits>::begin() const
	{
		return Tstorage;
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_iterator BasicString<CharT, Traits>::cbegin() const
	{
		return begin();
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::iterator BasicString<CharT, Traits>::end()
	{
		return Tstorage + string_length;
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_iterator BasicString<CharT, Traits>::end() const
	{
		return Tstorage + string_length;
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_iterator BasicString<CharT, Traits>::cend() const
	{
		return end();
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::reverse_iterator BasicString<CharT, Traits>::rbegin()
	{
		return reverse_iterator(end());
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_reverse_iterator BasicString<CharT, Traits>::rbegin() const
	{
		return const_reverse_iterator(end());
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_reverse_iterator BasicString<CharT, Traits>::crbegin() const
	{
		return rbegin();
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::reverse_iterator BasicString<CharT, Traits>::rend()
	{
		return reverse_iterator(begin());
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_reverse_iterator BasicString<CharT, Traits>::rend() const
	{
		return const_reverse_iterator(begin());
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::const_reverse_iterator BasicString<CharT, Traits>::crend() const
	{
		return rend();
	}

	template<typename CharT, typename Traits>
	inline bool BasicString<CharT, Traits>::empty() const
	{
		return string_length == 0;
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::size_type BasicString<CharT, Traits>::size() const
	{
		return string_length;
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::size_type BasicString<CharT, Traits>::length() const
	{
		return string_length;
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::size_type BasicString<CharT, Traits>::max_size() const
	{
		return MAX_STRING_SIZE;
	}

	template<typename CharT, typename Traits>
	inline void BasicString<CharT, Traits>::reserve(size_type n)
	{
		if (reserved_size >= n)
		{
			return;
		}
		else
		{
			_reallocate(n);
			return;
		}
	}

	template<typename CharT, typename Traits>
	inline typename BasicString<CharT, Traits>::size_type BasicString<CharT, Traits>::capacity() const
	{
		return reserved_size;
	}

	template<typename CharT, typename Traits>
	inline void BasicString<CharT, Traits>::shrink_to_fit()
	{
		_reallocate(string_length);
	}

	int       stoi(const String& str, std::size_t* pos = 0, int base = 10);
	int       stoi(const WString& str, std::size_t* pos = 0, int base = 10);
	long      stol(const String& str, std::size_t* pos = 0, int base = 10);
	long      stol(const WString& str, std::size_t* pos = 0, int base = 10);
	long long stoll(const String& str, std::size_t* pos = 0, int base = 10);
	long long stoll(const WString& str, std::size_t* pos = 0, int base = 10);

	unsigned long      stoul(const String& str, std::size_t* pos = 0, int base = 10);
	unsigned long      stoul(const WString& str, std::size_t* pos = 0, int base = 10);
	unsigned long long stoull(const String& str, std::size_t* pos = 0, int base = 10);
	unsigned long long stoull(const WString& str, std::size_t* pos = 0, int base = 10);

	float       stof(const String& str, std::size_t* pos = 0);
	float       stof(const WString& str, std::size_t* pos = 0);
	double      stod(const String& str, std::size_t* pos = 0);
	double      stod(const WString& str, std::size_t* pos = 0);
	long double stold(const String& str, std::size_t* pos = 0);
	long double stold(const WString& str, std::size_t* pos = 0);


	#undef Tstorage
	#undef Tsize
}

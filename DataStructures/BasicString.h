#pragma once
#include <stdexcept>
#include <string>

#define MAX_STRING_SIZE 1073741824U		//1GB

namespace DataStructures
{
	template<typename CharT = char, typename Traits = std::char_traits<CharT>>
	class BasicString
	{
	public:
		using String = BasicString<char>;
		using WString = BasicString<wchar_t>;

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

		static const size_type npos = -1U;

		//Constructor, Destructor and Assignment
		explicit BasicString() noexcept;
		explicit BasicString(size_type n, const CharT& val);
		BasicString(const BasicString& other, size_type pos, size_type n);
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
		void resize(size_type n, CharT ch);	//Fill with val
		void swap(BasicString<CharT>& other) noexcept;

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
		BasicString<CharT, Traits> operator+(const BasicString<CharT, Traits>& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(const CharT* lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(CharT lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(const BasicString<CharT, Traits>& lhs, const CharT* rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(const BasicString<CharT, Traits>& lhs, CharT rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(BasicString<CharT, Traits>&& lhs, const BasicString<CharT, Traits>& rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(const BasicString<CharT, Traits>& lhs, BasicString<CharT, Traits>&& rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(BasicString<CharT, Traits>&& lhs, BasicString<CharT, Traits>&& rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(const CharT* lhs, BasicString<CharT, Traits>&& rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(CharT lhs, BasicString<CharT, Traits>&& rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(BasicString<CharT, Traits>&& lhs, const CharT* rhs);
		template<typename CharT, typename Traits>
		BasicString<CharT, Traits> operator+(BasicString<CharT, Traits>&& lhs, CharT rhs);

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
		friend int       stoi(const String& str, std::size_t* pos = 0, int base = 10);
		friend int       stoi(const WString& str, std::size_t* pos = 0, int base = 10);
		friend long      stol(const String& str, std::size_t* pos = 0, int base = 10);
		friend long      stol(const WString& str, std::size_t* pos = 0, int base = 10);
		friend long long stoll(const String& str, std::size_t* pos = 0, int base = 10);
		friend long long stoll(const WString& str, std::size_t* pos = 0, int base = 10);

		friend unsigned long      stoul(const String& str, std::size_t* pos = 0, int base = 10);
		friend unsigned long      stoul(const WString& str, std::size_t* pos = 0, int base = 10);
		friend unsigned long long stoull(const String& str, std::size_t* pos = 0, int base = 10);
		friend unsigned long long stoull(const String& str, std::size_t* pos = 0, int base = 10);

		friend float       stof(const String& str, std::size_t* pos = 0);
		friend float       stof(const WString& str, std::size_t* pos = 0);
		friend double      stod(const String& str, std::size_t* pos = 0);
		friend double      stod(const WString& str, std::size_t* pos = 0);
		friend long double stold(const String& str, std::size_t* pos = 0);
		friend long double stold(const WString& str, std::size_t* pos = 0);

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
		size_type reserved_size = 4;
		size_type length = 0;
		char* storage = nullptr;
		inline void reallocate();
		inline void move_storage(T* dest, T* from, size_type n);
	};

	/* Dividing Line (д├ бузе бу;)д├ (д├ бузе бу;)д├ (д├ бузе бу;)д├  */

}

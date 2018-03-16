#pragma once
#include <stdexcept>

#define MAX_VECTOR_SIZE -1U

namespace DataStructures
{
	template<typename T>
	class Vector
	{
	public:
		using value_type		= T;
		using reference			= T&;
		using const_reference	= const T&;
		using pointer			= T*;
		using const_pointer		= const T*;
		using difference_type	= ptrdiff_t;
		using size_type			= size_t;

		using iterator			= T*;
		using const_iterator	= const T*;
		using reverse_iterator			= std::reverse_iterator<iterator>;
		using const_reverse_iterator	= std::reverse_iterator<const_iterator>;

		//Constructor, Destructor and Assignment
		explicit Vector() noexcept;
		explicit Vector(size_type n);
		explicit Vector(size_type n, const T& val);

		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		Vector(InputIterator first, InputIterator last);

		Vector(std::initializer_list<T> init);
		Vector(const Vector& origin);
		Vector(Vector&& origin) noexcept;
		~Vector();
		Vector& operator=(const Vector& origin);	//Assign will modify reserved_size to origin.reserved_size, which behaves differently from STL vector.
		Vector& operator=(Vector&& origin);
		Vector& operator=(std::initializer_list<T> init);
		void assign(size_type n, const T& val);
		void assign(std::initializer_list<T> init);
		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>> 
		void assign(InputIterator first, InputIterator last);

		//Element access
		reference operator[](size_type index);	//No check
		const_reference operator[](size_type index) const;
		reference at(size_type index);			//Check and throw out_of_range exception
		const_reference at(size_type index) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		T* data() noexcept;
		const T* data() const noexcept;

		//Iterators
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator crend() const noexcept;

		//Capacity
		bool empty() const noexcept;
		size_type size() const noexcept;
		size_type max_size() const noexcept;
		void reserve(size_type n);
		size_type capacity() const noexcept;
		void shrink_to_fit();

		//Modifiers
		void clear() noexcept;
		iterator insert(const_iterator pos, const T& val);
		iterator insert(const_iterator pos, T&& val);
		iterator insert(const_iterator pos, size_type, T& val);
		iterator insert(const_iterator pos, std::initializer_list<T> init);
		template<typename InputIterator> iterator insert(const_iterator pos, InputIterator first, InputIterator last);	//last not included
		template <typename ... Args> iterator emplace(const_iterator pos, Args&& ... args);
		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);	//last not included
		void push_back(const T& val);
		void push_back(T&& rval);
		template <typename ... Args> reference emplace_back(Args&& ... args);
		void pop_back();
		void resize(size_type n);				//Fill with default initialized element
		void resize(size_type n, const T&val);	//Fill with val
		void swap(Vector<T>& other);

		//Non-Member Functions
		template<typename T> friend bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
		template<typename T> friend bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);
		template<typename T> friend bool operator<(const Vector<T>& lhs, const Vector<T>& rhs);
		template<typename T> friend bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs);
		template<typename T> friend bool operator>(const Vector<T>& lhs, const Vector<T>& rhs);
		template<typename T> friend bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs);
		template<typename T> friend void swap(Vector<T>& lhs, Vector<T>& rhs);

	private:
		size_type reserved_size = 4;
		size_type vector_size = 0;
		char* storage = nullptr;
		inline void _reallocate(size_type rsv_sz);
		inline void _move_storage(T* dest, T* from, size_type n);
		inline void _allocate(size_type rsv_sz);	//malloc some storage and set reserved_size to rsv_sz
		template <typename ... Args> inline void _construct(size_type pos, Args&& ... args);
		template <typename ... Args> inline void _construct(iterator iter, Args&& ... args);
	};

	/* Dividing Line (д├ бузе бу;)д├ (д├ бузе бу;)д├ (д├ бузе бу;)д├  */

	#define Tstorage reinterpret_cast<T*>(storage)

	template<typename T>
	inline Vector<T>::Vector() noexcept : vector_size(0)
	{
		_allocate(4);
	}

	template<typename T>
	inline Vector<T>::Vector(size_type n) : vector_size(0)
	{
		_allocate(n);
		while (vector_size < n)
		{
			_construct(vector_size);
			++vector_size;
		}
	}

	template<typename T>
	inline Vector<T>::Vector(size_type n, const T & val) : vector_size(0)
	{
		_allocate(n);
		while (vector_size < n)
		{
			_construct(vector_size, val);
			++vector_size;
		}
	}

	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> init) : vector_size(0)
	{
		size_type count = init.size();
		_allocate(count);
		for (const T& elem : init)
		{
			_construct(vector_size, elem);
			++vector_size;
		}
	}

	template<typename T>
	inline Vector<T>::Vector(const Vector& origin) : vector_size(0)
	{
		_allocate(origin.reserved_size);
		while (vector_size < origin.vector_size)
		{
			_construct(vector_size, origin[vector_size]);
			++vector_size;
		}
	}

	template<typename T>
	inline Vector<T>::Vector(Vector&& origin) noexcept
	{
		swap(origin);
	}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		clear();
		free(storage);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(const Vector& origin)
	{
		swap(Vector(origin));
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(Vector<T>&& origin)
	{
		swap(origin);
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(std::initializer_list<T> init)
	{
		swap(Vector(init));
		return *this;
	}

	template<typename T>
	inline void Vector<T>::assign(size_type n, const T & val)
	{
		swap(Vector(n, val));
	}

	template<typename T>
	inline void Vector<T>::assign(std::initializer_list<T> init)
	{
		swap(Vector(init));
	}

	template<typename T>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline Vector<T>::Vector(InputIterator first, InputIterator last)
	{
		size_type count = std::distance(first, last);
		_allocate(count);
		while (vector_size < count)
		{
			_construct(vector_size, *first++);
			++vector_size;
		}
	}

	template<typename T>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline void Vector<T>::assign(InputIterator first, InputIterator last)
	{
		swap(Vector(first, last));
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::begin() noexcept
	{
		return Tstorage;
	}

	template<typename T>
	inline typename Vector<T>::const_iterator Vector<T>::begin() const noexcept
	{
		return Tstorage;
	}

	template<typename T>
	inline typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept
	{
		return begin();
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::end() noexcept
	{
		return Tstorage + vector_size;
	}

	template<typename T>
	inline typename Vector<T>::const_iterator Vector<T>::end() const noexcept
	{
		return Tstorage + vector_size;
	}

	template<typename T>
	inline typename Vector<T>::const_iterator Vector<T>::cend() const noexcept
	{
		return end();
	}

	template<typename T>
	inline typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept
	{
		return reverse_iterator(Tstorage + vector_size);
	}

	template<typename T>
	inline typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const noexcept
	{
		return reverse_iterator(Tstorage + vector_size);
	}

	template<typename T>
	inline typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept
	{
		return rbegin();
	}

	template<typename T>
	inline typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept
	{
		return reverse_iterator(Tstorage);
	}

	template<typename T>
	inline typename Vector<T>::const_reverse_iterator Vector<T>::rend() const noexcept
	{
		return reverse_iterator(Tstorage);
	}

	template<typename T>
	inline typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept
	{
		return rend();
	}

	template<typename T>
	inline bool Vector<T>::empty() const noexcept
	{
		return vector_size == 0;
	}

	template<typename T>
	inline typename Vector<T>::size_type Vector<T>::size() const noexcept
	{
		return vector_size;
	}

	template<typename T>
	inline typename Vector<T>::size_type Vector<T>::max_size() const noexcept
	{
		return MAX_VECTOR_SIZE;
	}

	template<typename T>
	inline typename Vector<T>::size_type Vector<T>::capacity() const noexcept
	{
		return reserved_size;
	}

	template<typename T>
	inline void Vector<T>::resize(size_type n)
	{
		if (n > vector_size)
		{
			if (n > reserved_size)
			{
				_reallocate(n);
			}
		}
		else
		{
			for (size_t i = n; i < vector_size; i++)
				Tstorage[i].~T();
		}
		vector_size = n;
	}

	template<typename T>
	inline void Vector<T>::resize(size_type n, const T& val)
	{
		if (n > vector_size)
		{
			if (n > reserved_size)
			{
				_reallocate(n);
			}
			for (size_t i = vector_size; i < n; i++)
			{
				_construct(i, val);
			}
		}
		else
		{
			for (size_t i = n; i < vector_size; i++)
				Tstorage[i].~T();
		}
		vector_size = n;
	}

	template<typename T>
	inline void Vector<T>::reserve(size_type n)
	{
		if (n > reserved_size)
		{
			_reallocate(n);
		}
	}

	template<typename T>
	inline void Vector<T>::shrink_to_fit()
	{
		_reallocate(vector_size);
	}

	template<typename T>
	inline typename Vector<T>::reference Vector<T>::operator[](size_type index)
	{
		return Tstorage[index];
	}

	template<typename T>
	inline typename Vector<T>::const_reference Vector<T>::operator[](size_type index) const
	{
		return Tstorage[index];
	}

	template<typename T>
	inline typename Vector<T>::reference Vector<T>::at(size_type pos)
	{
		if (pos < vector_size)
			return Tstorage[pos];
		throw std::out_of_range{ "Accessed position is out of range!" };
	}

	template<typename T>
	inline typename Vector<T>::const_reference Vector<T>::at(size_type pos) const
	{
		if (pos < vector_size)
			return Tstorage[pos];
		throw std::out_of_range{ "Accessed position is out of range!" };
	}

	template<typename T>
	inline typename Vector<T>::reference Vector<T>::front()
	{
		return Tstorage[0];
	}

	template<typename T>
	inline typename Vector<T>::const_reference Vector<T>::front() const
	{
		return Tstorage[0];
	}

	template<typename T>
	inline typename Vector<T>::reference Vector<T>::back()
	{
		return Tstorage[vector_size - 1];
	}

	template<typename T>
	inline typename Vector<T>::const_reference Vector<T>::back() const
	{
		return Tstorage[vector_size - 1];
	}

	template<typename T>
	inline T * Vector<T>::data() noexcept
	{
		return Tstorage;
	}

	template<typename T>
	inline const T * Vector<T>::data() const noexcept
	{
		return Tstorage;
	}

	template<typename T>
	template<typename ...Args>
	inline typename Vector<T>::reference Vector<T>::emplace_back(Args && ...args)
	{
		if (vector_size == reserved_size)
		{
			_reallocate(reserved_size + reserved_size / 2 + 1);
		}
		_construct(vector_size, std::forward<Args>(args) ...);
		return Tstorage[vector_size++];
	}

	template<typename T>
	template<typename ...Args>
	inline typename void Vector<T>::_construct(size_type pos, Args && ...args)
	{
		new(Tstorage + pos) T(std::forward<Args>(args) ...);
	}

	template<typename T>
	template<typename ...Args>
	inline void Vector<T>::_construct(iterator iter, Args && ...args)
	{
		new(iter) T(std::forward<Args>(args) ...);
	}

	template<typename T>
	inline void Vector<T>::push_back(const T &val)
	{
		emplace_back(val);
	}

	template<typename T>
	inline void Vector<T>::push_back(T &&rval)
	{
		emplace_back(rval);	//Is this okay?
	}

	template<typename T>
	inline void Vector<T>::pop_back()
	{
		Tstorage[--vector_size].~T();
	}

	template<typename T>
	template<typename ...Args>
	inline typename Vector<T>::iterator Vector<T>::emplace(const_iterator iter, Args && ...args)
	{
		size_type pos = iter - Tstorage;
		iterator _iter = &Tstorage[pos];
		if (vector_size == reserved_size)
		{
			_reallocate(reserved_size + reserved_size / 2 + 1);
		}
		_iter = &Tstorage[pos];
		_move_storage(_iter + 1, _iter, vector_size - (_iter - Tstorage));
		++vector_size;
		_construct(_iter, std::forward<Args>(args) ...);
		return _iter;
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::insert(const_iterator iter, const T& lval)
	{
		return emplace(iter, lval);
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::insert(const_iterator iter, T&& rval)
	{
		return emplace(iter, rval);
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::insert(const_iterator iter, size_type n, T &val)
	{
		size_type pos = iter - Tstorage;
		iterator _iter = &Tstorage[pos];
		if (n == 0) return _iter;
		if (vector_size + n > reserved_size)
		{
			_reallocate(reserved_size / 2 > n ? reserved_size + reserved_size / 2 + 1 : reserved_size + n);
		}
		_iter = &Tstorage[pos];
		_move_storage(_iter + n, _iter, vector_size - (_iter - Tstorage));
		vector_size += n;
		for (size_t i = 0; i < n; i++)
			_construct(iter++, val);
		return &Tstorage[pos];
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::insert(const_iterator iter, std::initializer_list<T> init)
	{
		size_type pos = iter - Tstorage;
		iterator _iter = &Tstorage[pos];
		size_type n = init.size();
		if (n == 0) return _iter;
		if (vector_size + n > reserved_size)
		{
			_reallocate(reserved_size / 2 > n ? reserved_size + reserved_size / 2 + 1 : reserved_size + n);
		}
		_iter = &Tstorage[pos];
		_move_storage(_iter + n, _iter, vector_size - (_iter - Tstorage));
		vector_size += n;
		for (const T& elem : init)
			_construct(_iter++, elem);
		return &Tstorage[pos];
	}

	template<typename T>
	template<typename InputIterator>
	inline typename Vector<T>::iterator Vector<T>::insert(const_iterator iter, InputIterator first, InputIterator last)
	{
		size_type pos = iter - Tstorage;
		iterator _iter = &Tstorage[pos];

		size_type n = std::distance(first, last);

		if (n == 0) return _iter;
		if (vector_size + n > reserved_size)
		{
			_reallocate(reserved_size / 2 > n ? reserved_size + reserved_size / 2 + 1 : reserved_size + n);
		}
		_iter = &Tstorage[pos];	//Must refresh _iter after reallocation
		_move_storage(_iter + n, _iter, vector_size - (_iter - Tstorage));
		vector_size += n;
		for (size_t i = 0; i < n; i++)
			_construct(_iter++, *first++);
		return &Tstorage[pos];
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::erase(const_iterator iter)
	{
		iterator _iter = &Tstorage[iter - Tstorage];
		_iter->~T();
		_move_storage(_iter, _iter + 1, vector_size - (_iter - Tstorage));
		vector_size -= 1;
		return _iter;
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator last)
	{
		size_type n = last - first;
		iterator _iter = &Tstorage[first - Tstorage];
		iterator _last = _iter + n;
		if (n == 0) return _iter;
		for (size_t i = 0; i < n; i++)
			first++->~T();
		_move_storage(_iter, _last, vector_size - (_last - Tstorage));
		vector_size -= n;
		return _iter;
	}

	template<typename T>
	inline void Vector<T>::swap(Vector<T>& rhs)
	{
		using std::swap;
		swap(vector_size, rhs.vector_size);
		swap(reserved_size, rhs.reserved_size);
		swap(storage, rhs.storage);
	}

	template<typename T>
	inline void Vector<T>::clear() noexcept
	{
		for (size_t i = 0; i < vector_size; i++)
		{
			Tstorage[i].~T();
		}
	}

	template<typename T>
	inline bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		if (lhs.vector_size != rhs.vector_size)
			return false;
		for (size_t i = 0; i < lhs.vector_size; i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template<typename T>
	inline bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	inline bool operator<(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		typename Vector<T>::size_type n = (lhs.vector_size < rhs.vector_size) ? lhs.vector_size : rhs.vector_size;
		for (size_t i = 0; i < n; i++)
			if (lhs[i] != rhs[i])
				return lhs[i] < rhs[i];
		return lhs.vector_size < rhs.vector_size;
	}

	template<typename T>
	inline bool operator>(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		typename Vector<T>::size_type n = lhs.vector_size < rhs.vector_size ? lhs.vector_size : rhs.vector_size;
		for (size_t i = 0; i < n; i++)
			if (lhs[i] != rhs[i])
				return lhs[i] > rhs[i];
		return lhs.vector_size > rhs.vector_size;
	}

	template<typename T>
	inline bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(lhs > rhs);
	}

	template<typename T>
	inline bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(lhs < rhs);
	}

	template<typename T>
	inline void swap(Vector<T>& lhs, Vector<T>& rhs)
	{
		lhs.swap(rhs);
	}

	template<typename T>
	inline void Vector<T>::_reallocate(size_type rsv_sz)
	{
		reserved_size = rsv_sz;
		storage = reinterpret_cast<char*>(realloc(storage, reserved_size * sizeof(T)));
	}

	template<typename T>
	inline void Vector<T>::_move_storage(T * dest, T * from, size_type n)
	{
		if (dest < from)
		{
			T *_dest = dest, *_from = from;
			for (size_t i = 0; i < n; i++)
				*_dest++ = std::move(*_from++);
		}
		else if (dest > from)
		{
			T *_dest = dest + n - 1, *_from = from + n - 1;
			for (size_t i = n; i > 0; i--)
				*_dest-- = std::move(*_from--);
		}
		else
			return;
	}

	template<typename T>
	inline void Vector<T>::_allocate(size_type rsv_sz)
	{
		reserved_size = rsv_sz;
		storage = reinterpret_cast<char*>(malloc(sizeof(T)*reserved_size));
	}

	#undef Tstorage
}

#pragma once
#include <stdexcept>
#include <allocators>
#include <limits>

#define MAX_VECTOR_SIZE std::numeric_limits<size_t>::max()

namespace DataStructures
{
	template<typename T, class Allocator = std::allocator<T>>
	class Vector
	{
	public:
		using allocator_type	= Allocator;
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
		Vector() noexcept;
		explicit Vector(const Allocator& alloc) noexcept;
		explicit Vector(size_type n, const T& val, const Allocator& alloc = Allocator());
		explicit Vector(size_type n, const Allocator& alloc = Allocator());

		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator_v<InputIterator>>>
		Vector(InputIterator first, InputIterator last, const Allocator& alloc = Allocator());

		Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());
		Vector(const Vector& origin);
		Vector(const Vector& origin, const Allocator& alloc);
		Vector(Vector&& origin) noexcept;
		Vector(Vector&& origin, const Allocator& alloc);
		~Vector();
		Vector& operator=(const Vector& origin);	//Assign will modify reserved_size to origin.reserved_size, which behaves differently from STL vector.
		Vector& operator=(Vector&& origin);
		Vector& operator=(std::initializer_list<T> init);
		void assign(size_type n, const T& val);
		void assign(std::initializer_list<T> init);
		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator_v<InputIterator>>> 
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
		void swap(Vector<T, Allocator>& other);

		//Non-Member Functions
		template<typename T, class Allocator> friend bool operator==(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);
		template<typename T, class Allocator> friend bool operator!=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);
		template<typename T, class Allocator> friend bool operator<(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);
		template<typename T, class Allocator> friend bool operator<=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);
		template<typename T, class Allocator> friend bool operator>(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);
		template<typename T, class Allocator> friend bool operator>=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);
		template<typename T, class Allocator> friend void swap(Vector<T, Allocator>& lhs, Vector<T, Allocator>& rhs);

	private:
		size_type reserved_size = 4;
		size_type vector_size = 0;
		allocator_type allocator;
		T* storage = nullptr;
		inline void _reallocate(size_type rsv_sz);
		inline void _move_storage(T* dest, T* from, size_type n);
		inline void _allocate(size_type rsv_sz);	//malloc some storage and set reserved_size to rsv_sz
		template <typename ... Args> inline void _construct(size_type pos, Args&& ... args);
		template <typename ... Args> inline void _construct(iterator iter, Args&& ... args);
	};

	/* Dividing Line (д├ бузе бу;)д├ (д├ бузе бу;)д├ (д├ бузе бу;)д├  */

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector() noexcept : vector_size(0), allocator(Allocator())
	{
		_allocate(4);
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector(const Allocator & alloc) noexcept : vector_size(0), allocator(alloc)
	{
		_allocate(4);
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector(size_type n, const T & val, const Allocator & alloc) : vector_size(0), allocator(alloc)
	{
		_allocate(n);
		while (vector_size < n)
		{
			_construct(vector_size, val);
			++vector_size;
		}
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector(size_type n, const Allocator& alloc) : vector_size(0), allocator(alloc)
	{
		_allocate(n);
		while (vector_size < n)
		{
			_construct(vector_size);
			++vector_size;
		}
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector(std::initializer_list<T> init, const Allocator& alloc) : vector_size(0), allocator(alloc)
	{
		size_type count = init.size();
		_allocate(count);
		for (const T& elem : init)
		{
			_construct(vector_size, elem);
			++vector_size;
		}
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector(const Vector& origin) : Vector(origin, origin.allocator)
	{
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector(const Vector & origin, const Allocator & alloc) : vector_size(0), allocator(alloc)
	{
		_allocate(origin.reserved_size);
		while (vector_size < origin.vector_size)
		{
			_construct(vector_size, origin[vector_size]);
			++vector_size;
		}
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector(Vector&& origin) noexcept
	{
		swap(origin);
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::Vector(Vector && origin, const Allocator & alloc)
	{
		swap(origin);
		allocator = alloc;
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>::~Vector()
	{
		clear();
		allocator.deallocate(storage, reserved_size);
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& origin)
	{
		swap(Vector(origin));
		return *this;
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector<T, Allocator>&& origin)
	{
		swap(origin);
		return *this;
	}

	template<typename T, class Allocator>
	inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(std::initializer_list<T> init)
	{
		swap(Vector(init));
		return *this;
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::assign(size_type n, const T & val)
	{
		swap(Vector(n, val));
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::assign(std::initializer_list<T> init)
	{
		swap(Vector(init));
	}

	template<typename T, class Allocator>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline Vector<T, Allocator>::Vector(InputIterator first, InputIterator last, const Allocator& alloc) : allocator(alloc)
	{
		size_type count = std::distance(first, last);
		_allocate(count);
		while (vector_size < count)
		{
			_construct(vector_size, *first++);
			++vector_size;
		}
	}

	template<typename T, class Allocator>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline void Vector<T, Allocator>::assign(InputIterator first, InputIterator last)
	{
		swap(Vector(first, last));
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin() noexcept
	{
		return storage;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::begin() const noexcept
	{
		return storage;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cbegin() const noexcept
	{
		return begin();
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end() noexcept
	{
		return storage + vector_size;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::end() const noexcept
	{
		return storage + vector_size;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cend() const noexcept
	{
		return end();
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rbegin() noexcept
	{
		return reverse_iterator(storage + vector_size);
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rbegin() const noexcept
	{
		return reverse_iterator(storage + vector_size);
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crbegin() const noexcept
	{
		return rbegin();
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rend() noexcept
	{
		return reverse_iterator(storage);
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rend() const noexcept
	{
		return reverse_iterator(storage);
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crend() const noexcept
	{
		return rend();
	}

	template<typename T, class Allocator>
	inline bool Vector<T, Allocator>::empty() const noexcept
	{
		return vector_size == 0;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::size_type Vector<T, Allocator>::size() const noexcept
	{
		return vector_size;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::size_type Vector<T, Allocator>::max_size() const noexcept
	{
		return MAX_VECTOR_SIZE;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::size_type Vector<T, Allocator>::capacity() const noexcept
	{
		return reserved_size;
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::resize(size_type n)
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
				storage[i].~T();
		}
		vector_size = n;
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::resize(size_type n, const T& val)
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
				storage[i].~T();
		}
		vector_size = n;
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::reserve(size_type n)
	{
		if (n > reserved_size)
		{
			_reallocate(n);
		}
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::shrink_to_fit()
	{
		_reallocate(vector_size);
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::reference Vector<T, Allocator>::operator[](size_type index)
	{
		return storage[index];
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::operator[](size_type index) const
	{
		return storage[index];
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::reference Vector<T, Allocator>::at(size_type pos)
	{
		if (pos < vector_size)
			return storage[pos];
		throw std::out_of_range{ "Accessed position is out of range!" };
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::at(size_type pos) const
	{
		if (pos < vector_size)
			return storage[pos];
		throw std::out_of_range{ "Accessed position is out of range!" };
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::reference Vector<T, Allocator>::front()
	{
		return storage[0];
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::front() const
	{
		return storage[0];
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::reference Vector<T, Allocator>::back()
	{
		return storage[vector_size - 1];
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::back() const
	{
		return storage[vector_size - 1];
	}

	template<typename T, class Allocator>
	inline T * Vector<T, Allocator>::data() noexcept
	{
		return storage;
	}

	template<typename T, class Allocator>
	inline const T * Vector<T, Allocator>::data() const noexcept
	{
		return storage;
	}

	template<typename T, class Allocator>
	template<typename ...Args>
	inline typename Vector<T, Allocator>::reference Vector<T, Allocator>::emplace_back(Args && ...args)
	{
		if (vector_size == reserved_size)
		{
			_reallocate(reserved_size + reserved_size / 2 + 1);
		}
		_construct(vector_size, std::forward<Args>(args) ...);
		return storage[vector_size++];
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::push_back(const T &val)
	{
		emplace_back(val);
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::push_back(T &&rval)
	{
		emplace_back(rval);	//Is this okay?
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::pop_back()
	{
		storage[--vector_size].~T();
	}

	template<typename T, class Allocator>
	template<typename ...Args>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::emplace(const_iterator iter, Args && ...args)
	{
		size_type pos = iter - storage;
		iterator _iter = &storage[pos];
		if (vector_size == reserved_size)
		{
			_reallocate(reserved_size + reserved_size / 2 + 1);
		}
		_iter = &storage[pos];
		_move_storage(_iter + 1, _iter, vector_size - (_iter - storage));
		++vector_size;
		_construct(_iter, std::forward<Args>(args) ...);
		return _iter;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator iter, const T& lval)
	{
		return emplace(iter, lval);
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator iter, T&& rval)
	{
		return emplace(iter, rval);
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator iter, size_type n, T &val)
	{
		size_type pos = iter - storage;
		iterator _iter = &storage[pos];
		if (n == 0) return _iter;
		if (vector_size + n > reserved_size)
		{
			_reallocate(reserved_size / 2 > n ? reserved_size + reserved_size / 2 + 1 : reserved_size + n);
		}
		_iter = &storage[pos];
		_move_storage(_iter + n, _iter, vector_size - (_iter - storage));
		vector_size += n;
		for (size_t i = 0; i < n; i++)
			_construct(iter++, val);
		return &storage[pos];
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator iter, std::initializer_list<T> init)
	{
		size_type pos = iter - storage;
		iterator _iter = &storage[pos];
		size_type n = init.size();
		if (n == 0) return _iter;
		if (vector_size + n > reserved_size)
		{
			_reallocate(reserved_size / 2 > n ? reserved_size + reserved_size / 2 + 1 : reserved_size + n);
		}
		_iter = &storage[pos];
		_move_storage(_iter + n, _iter, vector_size - (_iter - storage));
		vector_size += n;
		for (const T& elem : init)
			_construct(_iter++, elem);
		return &storage[pos];
	}

	template<typename T, class Allocator>
	template<typename InputIterator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator iter, InputIterator first, InputIterator last)
	{
		size_type pos = iter - storage;
		iterator _iter = &storage[pos];

		size_type n = std::distance(first, last);

		if (n == 0) return _iter;
		if (vector_size + n > reserved_size)
		{
			_reallocate(reserved_size / 2 > n ? reserved_size + reserved_size / 2 + 1 : reserved_size + n);
		}
		_iter = &storage[pos];	//Must refresh _iter after reallocation
		_move_storage(_iter + n, _iter, vector_size - (_iter - storage));
		vector_size += n;
		for (size_t i = 0; i < n; i++)
			_construct(_iter++, *first++);
		return &storage[pos];
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator iter)
	{
		iterator _iter = &storage[iter - storage];
		_iter->~T();
		_move_storage(_iter, _iter + 1, vector_size - (_iter - storage));
		vector_size -= 1;
		return _iter;
	}

	template<typename T, class Allocator>
	inline typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator first, const_iterator last)
	{
		size_type n = last - first;
		iterator _iter = &storage[first - storage];
		iterator _last = _iter + n;
		if (n == 0) return _iter;
		for (size_t i = 0; i < n; i++)
			first++->~T();
		_move_storage(_iter, _last, vector_size - (_last - storage));
		vector_size -= n;
		return _iter;
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::swap(Vector<T, Allocator>& rhs)
	{
		using std::swap;
		swap(vector_size, rhs.vector_size);
		swap(reserved_size, rhs.reserved_size);
		swap(storage, rhs.storage);
		swap(allocator, rhs.allocator);
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::clear() noexcept
	{
		for (size_t i = 0; i < vector_size; i++)
		{
			storage[i].~T();
		}
	}

	template<typename T, class Allocator>
	inline bool operator==(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
	{
		if (lhs.vector_size != rhs.vector_size)
			return false;
		for (size_t i = 0; i < lhs.vector_size; i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template<typename T, class Allocator>
	inline bool operator!=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T, class Allocator>
	inline bool operator<(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
	{
		typename Vector<T, Allocator>::size_type n = (lhs.vector_size < rhs.vector_size) ? lhs.vector_size : rhs.vector_size;
		for (size_t i = 0; i < n; i++)
			if (lhs[i] != rhs[i])
				return lhs[i] < rhs[i];
		return lhs.vector_size < rhs.vector_size;
	}

	template<typename T, class Allocator>
	inline bool operator>(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
	{
		typename Vector<T, Allocator>::size_type n = lhs.vector_size < rhs.vector_size ? lhs.vector_size : rhs.vector_size;
		for (size_t i = 0; i < n; i++)
			if (lhs[i] != rhs[i])
				return lhs[i] > rhs[i];
		return lhs.vector_size > rhs.vector_size;
	}

	template<typename T, class Allocator>
	inline bool operator<=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
	{
		return !(lhs > rhs);
	}

	template<typename T, class Allocator>
	inline bool operator>=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

	template<typename T, class Allocator>
	inline void swap(Vector<T, Allocator>& lhs, Vector<T, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::_reallocate(size_type rsv_sz)
	{
		T* new_storage = allocator.allocate(rsv_sz);
		memcpy(static_cast<void*>(new_storage), static_cast<void*>(storage), sizeof(T)*vector_size);
		allocator.deallocate(storage, reserved_size);
		reserved_size = rsv_sz;
		storage = new_storage;
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::_move_storage(T * dest, T * from, size_type n)
	{
		memmove(static_cast<void*>(dest), static_cast<void*>(from), n * sizeof(T));
		//if (dest < from)
		//{
		//	T *_dest = dest, *_from = from;
		//	for (size_t i = 0; i < n; i++)
		//		*_dest++ = std::move(*_from++);
		//}
		//else if (dest > from)
		//{
		//	T *_dest = dest + n - 1, *_from = from + n - 1;
		//	for (size_t i = n; i > 0; i--)
		//		*_dest-- = std::move(*_from--);
		//}
		//else
		//	return;
	}

	template<typename T, class Allocator>
	inline void Vector<T, Allocator>::_allocate(size_type rsv_sz)
	{
		reserved_size = rsv_sz;
		storage = allocator.allocate(reserved_size);
	}


	template<typename T, class Allocator>
	template<typename ...Args>
	inline typename void Vector<T, Allocator>::_construct(size_type pos, Args && ...args)
	{
		new(storage + pos) T(std::forward<Args>(args) ...);
	}

	template<typename T, class Allocator>
	template<typename ...Args>
	inline void Vector<T, Allocator>::_construct(iterator iter, Args && ...args)
	{
		new(iter) T(std::forward<Args>(args) ...);
	}
}

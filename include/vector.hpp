#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <cstddef> // Required for std::size_t

namespace ft
{
	template<class T>
	class vector
	{
	public: // Type defintions
		typedef T				value_type;
		typedef std::size_t		size_type;

	private:
		T* m_arr; // The internal array it will be using
		size_type m_used; // The total amount of elements in m_arr
		size_type m_size; // The max internal size of the array

	public:
		// Constructors / Destructors
		vector() { }
//		explicit vector(const Allocator& alloc);
		explicit vector(size_type count, const T& value = T()/*, const Allocator& alloc = Allocator()*/) { }
//		template<class InputIt>
//		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
		vector(const vector& copy) { }

		~vector() { }
	};
}

#endif
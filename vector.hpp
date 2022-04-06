/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:04:50 by vintran           #+#    #+#             */
/*   Updated: 2022/04/06 03:48:01 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream> // asuppr
# include "utils/reverseIterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector {

		public:
		
//========================================TYPEDEF========================================//

			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointeur;
			typedef T*												iterator;
			typedef const T*										const_iterator;
			typedef typename ft::reverseIterator<iterator>			reverse_iterator;
			typedef typename ft::reverseIterator<const_iterator>	const_reverse_iterator;
			typedef ptrdiff_t										difference_type;
			typedef size_t											size_type;


//=====================================CONSTRUCTORS=====================================//

			// default constructor
			explicit vector(const allocator_type& alloc = allocator_type()) {
				
				this->_alloc = alloc;
				this->_size = 0;
				this->_capacity = 0;
				this->_start = NULL;
			}

			// fill constructor
			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) {

				_alloc = alloc;
				_start = NULL;
				_check_range(n);
				if (n)
				{
					_start = _alloc.allocate(n);
					_capacity = n;
				}
				else
					_capacity = 0;
				_size = n;

				iterator	pos = _start;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(pos++, val);
			}

			// range constructor
			template < class InputIterator >
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
			
					_alloc = alloc;
					difference_type dist = std::distance(first, last);
					this->_size = static_cast<size_type>(dist);
					this->_capacity = static_cast<size_type>(dist);
					if (dist)
					{    
						_check_range(_capacity);
						_start = _alloc.allocate(_capacity);
						std::uninitialized_copy(first, last, this->_start);
					}
			}

			// copy constructor
			vector(const vector& src) {

				_start = NULL;
				_size = src._size;
				_capacity = src._capacity;
				if (src._capacity)
					_start = _alloc.allocate(_capacity);
				if (src._capacity)
					std::uninitialized_copy(src._start, src._start + src._size, _start);
			}


//======================================DESTRUCTOR======================================//

			virtual ~vector() {

				this->clear();
				if (_capacity)
					_alloc.deallocate(_start, _capacity);
			}


//=================================ASSIGNATION OPERATOR=================================//

			vector	&operator=(const vector& rhs) {

				if (*this != rhs)
				{
					this->_dealloc();
					if (rhs.empty())
						return (*this);
					this->_size = rhs.size();
					this->_capacity = rhs.capacity();
					_check_range(rhs.capacity());
					_start = _alloc.allocate(rhs.capacity());
					std::uninitialized_copy(rhs.begin(), rhs.end(), this->_start);
				}
				return (*this);
			}


//====================================ITERATORS====================================//

			iterator	begin() {

				return (this->_start);
			}

			const_iterator	begin() const {

				return (this->_start);
			}

			iterator	end() {

				return (this->_start + this->_size);
			}

			const_iterator	end() const {

				return (this->_start + this->_size);
			}

			reverse_iterator	rbegin() {

				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const {

				return (const_reverse_iterator(end()));
			}

			reverse_iterator	rend() {

				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const {

				return (const_reverse_iterator(begin()));
			}


//=====================================CAPACITY====================================//

			size_type	size() const {

				return (this->_size);
			}

			size_type	max_size() const {

				return (this->_alloc.max_size());
			}

			void	resize(size_type n, value_type val = value_type()) {

				this->_check_range(n);
				if (n == this->_size)
					return ;
				if (n == 0)
					return (clear());
				if (n < this->_size)
				{
					iterator it = end();
					size_type diff = this->_size - n;
					while (diff--)
					{
						this->_alloc.destroy(--it);
						this->_size--;
					}
					return ;
				}
				if (n > this->_size)
					this->_realloc_fill(n, val);
			}

			size_type	capacity() const {

				return (this->_capacity);
			}

			bool	empty() const {

				if (this->_size == 0)
					return (true);
				return (false);
			}

			void	reserve(size_type n) {
				
				if (this->_capacity > n)
					return ;
				if (n > max_size())
					throw std::out_of_range("vector::reserve");
				else
					this->_realloc(n);
			}


//====================================ELEMENT ACCESS====================================//

			reference	operator[](size_type n) {

				return (this->_start[n]);
			}

			const_reference	operator[](size_type n) const {

				return (this->_start[n]);
			}

			reference	at(size_type n) {

				_check_size(n);
				return (this->_start[n]);
			}

			const_reference		at(size_type n) const {

				_check_size(n);
				return (this->_start[n]);
			}

			reference	front() {

				return (*begin());
			}

			const_reference		front() const {

				return (*begin());
			}

			reference	back() {

				return (*(end() - 1));
			}

			const_reference		back() const {

				return (*(end() - 1));
			}


//======================================MODIFIERS======================================//

			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {

				difference_type dist = std::distance(first, last);
				this->_dealloc();
				if (dist)
				{
					_check_range(dist);
					_start = _alloc.allocate(dist);
					_capacity = dist;
				}
				for (iterator i = begin(); i < begin() + dist; i++)
					this->_alloc.construct(i, *first++);
				this->_size = dist;
			}

			void	assign(size_type n, const value_type& val) {

				this->_dealloc();
				if (n)
					this->reserve(n);
				for (iterator i = begin(); i < begin() + n; i++)
					this->_alloc.construct(i, val);
				this->_size = n;
			}

			void	push_back(const value_type& val) {

				this->_insert_back(val);
				this->_size++;
			}

			void	pop_back() {

				if (this->empty() == false) {

					this->_alloc.destroy(end() - 1);
					this->_size--;
				}
			}

			// insert single element
			iterator	insert(iterator position, const value_type& val) {

				difference_type			newSize = std::distance(this->begin(), position);

				insert(position, 1, val);
				return (this->begin() + newSize);
			}

			// insert fill
			void	insert(iterator position, size_type n, const value_type& val) {

				difference_type			beginToPos = std::distance(this->begin(), position);
				difference_type			prevSize = this->_size;
				iterator				prevEnd;
				iterator				end;

				this->resize(this->_size + n);

				prevEnd = this->begin() + prevSize;
				position = this->begin() + beginToPos;
				end = this->_start + this->_size;
				while (prevEnd != position) {

					*(--end) = *(--prevEnd);
				}
				while (0 < n) {

					*position++ = val;
					n--;
				}
			}

			// insert range
			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
			
				difference_type			beginToPos = std::distance(this->begin(), position);
				difference_type			prevSize = this->_size;
				difference_type			newSize = std::distance(first, last);
				iterator				prevEnd;
				iterator				end;

				this->resize(this->_size + newSize);

				prevEnd = this->begin() + prevSize;
				position = this->begin() + beginToPos;
				end = this->end();
				while (prevEnd != position) {

					*(--end) = *(--prevEnd);
				}
				while (first != last) {

					*position = *first;
					position++;
					first++;
				}
			}

			iterator	erase(iterator position) {

				if (position == end())
					return position;
				return (this->erase(position, position + 1));
			}

			iterator	erase(iterator first, iterator last) {

				if (first == last)
					return (first);
				if (last == end())
				{
					for (iterator i = first; i != last; i++)
					{
						this->_alloc.destroy(i);
						this->_size--;
					}
					return (first);
		
				}
				iterator it = first;
				difference_type size = std::distance(first, last);
				while (it != last)
				{
					this->_alloc.destroy(it);
					it++;
				}
				it = first;
				while (it + size != end())
				{
					this->_alloc.construct(it, *(it + size));
					this->_alloc.destroy(it + size);
					it++;
				}
				this->_size -= static_cast<size_type>(size);
				return (first);
			}

			void	swap(vector& x) {

				std::swap(this->_alloc, x._alloc);
				std::swap(this->_start, x._start);
				std::swap(this->_size, x._size);
				std::swap(this->_capacity, x._capacity);
			}

			void clear() {

				for (size_type i = 0; i < _size; i++)
					this->_alloc.destroy(_start + i);
				this->_size = 0;
			}


//======================================ALLOCATOR======================================//

			allocator_type	get_allocator() const {

				return (this->_alloc);
			}


//=================================PROTECTED ATTRIBUTES================================//

		protected:
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;
			iterator		_start;


//=====================================MY FUNCTIONS===================================//

			void	_dealloc() {
			
				if (this->_capacity)
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_start + i);
					_alloc.deallocate(_start, _capacity);
				}
				_capacity = 0;
				_size = 0;
			}

			void	_realloc(size_type n) {

				size_type	prevSize = this->_size;
				iterator	tmp = _alloc.allocate(n);
				std::uninitialized_copy(_start, _start + _size, tmp);
				_dealloc();
				_size = prevSize;
				_start = tmp;
				_capacity = n;
			}

			void	_realloc_fill(size_type n, value_type const & val) {

				iterator	tmp = this->_alloc.allocate(n);
				size_type	prevSize = _size;
				std::uninitialized_copy(_start, _start + _size, tmp);
				_dealloc();
				_start = tmp;
				std::uninitialized_fill(_start + prevSize, _start + n, val);
				_size = n;
				_capacity = n;
			}

			void	_check_range(size_type n) {

				if (n > _alloc.max_size())
					throw std::out_of_range("vector::_check_range");
			}

			void	_check_size(size_type n) {

				if (n + _size)
					throw std::out_of_range("vector::_check_size");
			}

			void	_insert_back(value_type const & val)
			{
				if (_capacity == 0)
				{
					_start = _alloc.allocate(1);
					_alloc.construct(_start, val);
					_capacity = 1;
					return ;
				}
				if (_size + 1 <= this->_capacity)
				{
					_alloc.construct(_start + _size, val);
					return ;
				}
				size_type	newSize;
				size_type	prevSize = _size;
				_check_range(_size + 1);
				if (_size * 2 < _alloc.max_size())
					newSize = _size * 2;
				else
					newSize = _size + 1;
				iterator	tmp;
				tmp = _alloc.allocate(newSize);
				std::uninitialized_copy(_start, _start + _size, tmp);
				_alloc.construct(tmp + prevSize, val);    
				_dealloc();
				_capacity = newSize;
				_start = tmp;
				_size = prevSize;
			}

	};


//=============================NON-MEMBER RELATIONAL OPERATORS===========================//


	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

		if (lhs.size() == rhs.size()) {

			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
		return (false);
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

		if (lhs != rhs) {

			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
		return (false);
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

		if (lhs == rhs)
			return (true);
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

		if (lhs == rhs)
			return (false);
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

		if (lhs == rhs)
			return (true);
		return (!(lhs < rhs));
	}


//================================NON-MEMBER FUNCTION SWAP================================//

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {

		x.swap(y);
	}

};

#endif
//ft::vector	-->	13.57s user 26.23s system 15% cpu 4:09.67 total
//std::vector	-->	15.35s user 26.66s system 16% cpu 4:11.66 total
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:39:08 by vintran           #+#    #+#             */
/*   Updated: 2022/04/12 06:43:28 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include <iostream> // asuppr
# include <sstream>
# include "utils/pair.hpp"
# include "utils/node.hpp"
# include "utils/iteratorTraits.hpp"
# include "utils/mapIterator.hpp"
# include "utils/reverseIterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/lexicographical_compare.hpp"
# include "utils/equal.hpp"

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {

		public:

//=====================================================TYPEDEF=====================================================//

			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef Compare														key_compare;
			
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				public:
					bool	operator()(const value_type &x, const value_type &y) const { return comp(x.first, y.first); }
					value_compare(Compare c) : comp(c) {}
				protected:
					Compare comp;
			};
			
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef node<value_type>											node_type;
			typedef node_type*													node_pointer;
			typedef mapIterator<value_type, node_pointer>						iterator;
			typedef mapIterator<const value_type, node_pointer>					const_iterator;
			typedef ft::reverseIterator<iterator>								reverse_iterator;
			typedef ft::reverseIterator<const_iterator>							const_reverse_iterator;
			typedef std::ptrdiff_t												difference_type;
			typedef size_t														size_type;
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;


//===============================================PROTECTED ATTRIBUTES=============================================//

		protected:
		
			key_compare		_comp;
			node_allocator	_alloc;
			size_type		_size;
			node_pointer	_root;

		private:

			node_pointer	_last;


//===================================================CONSTRUCTORS=================================================//

		public:

			// empty constructor
			explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _size(0), _root(NULL) {

				_last = _create_node(value_type());
			}
			
			// range constructor
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()/*,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL*/) ///////////////////// enable_if ???????????????
					: _comp(comp), _alloc(alloc), _size(0), _root(NULL) {

				_last = _create_node(value_type());
				insert(first, last);
			}
	
			//copy constructor
			map(const map & x) : _comp(x._comp), _alloc(x._alloc), _size(0), _root(NULL) {

				_last = _create_node(value_type());
				*this = x;
			}


//====================================================DESTRUCTOR===================================================//

			virtual ~map() {

				clear();
				_alloc.destroy(_last);
				_alloc.deallocate(_last, 1);
			}


//===============================================ASSIGNATION OPERATOR==============================================//

			map &	operator=(const map & rhs) {

				if (this != &rhs) {

					clear();
					insert(rhs.begin(), rhs.end());
				}
				return (*this);
			}


//=====================================================ITERATORS===================================================//

			iterator		begin() {	//minimum a tester
				
				if (this->_size == 0)
					return (this->_root);

				node_pointer	tmp = this->_root;
				while (tmp && tmp->left)
					tmp = tmp->left;
				return (tmp);
			}

			const_iterator	begin() const {

				if (this->_size == 0)
					return (const_iterator(this->_root));

				node_pointer	tmp = this->_root;
				while (tmp && tmp->left)
					tmp = tmp->left;
				return (const_iterator(tmp));
			}

			iterator				end() { return (iterator(_last)); }

			const_iterator			end() const {

				if (_size == 0)
					return (begin());
				return (const_iterator(_last));
			}

			reverse_iterator		rbegin() { return (reverse_iterator(end()--)); }

			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end()--)); }

			reverse_iterator		rend() { return (reverse_iterator(begin())); }

			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }


//=====================================================CAPACITY====================================================//

			bool		empty() const { return (this->_size == 0); }

			size_type	size() const { return (this->_size); }

			size_type	max_size() const { return (_alloc.max_size()); }


//==================================================ELEMENT ACCESS=================================================//

			mapped_type &		operator[](const key_type & k) {

				node_pointer	tmp = _find_key(k, this->_root);

				if (tmp)
					return (tmp->value.second);
				insert(value_type(k, mapped_type()));
				return (_find_key(k, this->_root)->value.second);
			}


//====================================================MODIFIERS====================================================//

			// insert single element
			ft::pair<iterator, bool>	insert(value_type const & val) {
				
				//bool	is_insert = _insert_node(val, _root);// _insert_node_root(val);
				bool	is_insert = _insert_node_root(val);

				return (ft::pair<iterator, bool>(_find_key(val.first, this->_root), is_insert));
			}

			// insert with hint
			iterator	insert(iterator position, value_type const & val) {

				(void)position;
				_insert_node_root(val);
				//_insert_node(val, _root);
				return (iterator(_find_key(val.first, this->_root)));
			}

			// insert range
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last) {

				while (first != last) {

					insert(*first);
					first++;
				}
			}

			void	erase(iterator position) {

				if (is_in_tree(position) == true)
					erase(position->first);
			}

			size_type	erase(const key_type & k) {

				node_pointer	to_delete = _find_key(k, _root);

				if (to_delete) {

					_delete_node(to_delete);
					return (1);
				}
				return (0);
			}

			void	erase(iterator first, iterator last) {

				if (is_in_tree(first) == true && (is_in_tree(last) == true || last == iterator(_last))) {

					while (first != last)
						erase(first++);
				}
			}

			void	swap(map & x) {

				std::swap(this->_comp, x._comp);
				std::swap(this->_alloc, x._alloc);
				std::swap(this->_size, x._size);
				std::swap(this->_root, x._root);
				std::swap(this->_last, x._last);
			}

			void	clear() {

				_clean_recursive(_root);
				_root = NULL;
				_size = 0;
			}


//====================================================OBSERVERS====================================================//

			key_compare		key_comp() const {

				return (this->_comp);
			}

			value_compare	value_comp() const {

				return (value_compare(key_compare()));
			}


//====================================================OPERATIONS===================================================//

			iterator	find(key_type const & k) {

				node_pointer	res = _find_key(k, _root);

				if (res) {
					//std::cout << "res != NULL" << std::endl;
					return (iterator(res));
				}
			//	std::cout << "res == NULL --> return end()" << std::endl;
				return (end());
			}

			const_iterator	find(key_type const & k) const {

				node_pointer	res = _find_key(k, _root);

				if (res)
					return (const_iterator(res));
				return (const_iterator(end()));
			}

			size_type	count(key_type const & k) const {

				const_iterator	it = find(k);

				if (it != end())
					return (1);
				return (0);
			}

			iterator	lower_bound(key_type const & k) {

				iterator	b = begin();
				iterator	e = end();

				while (b != e) {

					if (!_comp(b->first, k))
						return (b);
					b++;
				}
				return (e);
			}

			const_iterator	lower_bound(key_type const & k) const {

				const_iterator	b = begin();
				const_iterator	e = end();

				while (b != e) {

					if (!_comp(b->first, k))
						return (b);
					b++;
				}
				return (e);
			}

			iterator	upper_bound(key_type const & k) {

				iterator	b = begin();
				iterator	e = end();

				while (b != e) {

					if (_comp(k, b->first))
						return (b);
					b++;
				}
				return (e);
			}

			const_iterator	upper_bound(key_type const & k) const {

				const_iterator	b = begin();
				const_iterator	e = end();

				while (b != e) {

					if (_comp(k, b->first))
						return (b);
					b++;
				}
				return (e);
			}

			pair<iterator, iterator>		equal_range(key_type const & k) {

				return (pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}

			pair<const_iterator, const_iterator>		equal_range(key_type const & k) const {

				return (pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}


//====================================================ALLOCATOR====================================================//

			allocator_type	get_allocator() const {

				return (this->_alloc);
			}


//===================================================MY FUNCTIONS==================================================//

		private:

			//****************PRINT TREE
			void	_print() {
				
				if (!_size)
					return ;
				std::stringstream	buffer;
				this->_recursive_print(_root, buffer, true, "");
				std::cout << buffer.str();
			}

			void	_recursive_print(node_pointer node, std::stringstream & buffer, bool is_tail, std::string prefix) {

				if (node->right && node->right != _last)
					this->_recursive_print(node->right, buffer, false, std::string(prefix).append(is_tail != 0 ? "│   " : "    "));
				buffer << prefix << (is_tail != 0 ? "└── " : "┌── ");
				buffer << "\033[31m";
				if (node)
					buffer << node->value.first << "\033[0m" << std::endl;
				if (node->left)
					this->_recursive_print(node->left, buffer, true, std::string(prefix).append(is_tail != 0 ? "    " : "│   "));
			}
			//*****************

			node_pointer	_minimum(node_pointer node) const {

				if (!node || node == _last)
					return (node);
				node_pointer	res = node;
				while (res->left)
					res = res->left;
				return (res);
			}

			node_pointer	_maximum(node_pointer node) const {

				if (!node || node == _last)
					return (node);
				node_pointer	res = node;
				while (res->right && res->right != _last)
					res = res->right;
				return (res);
			}

			bool	is_in_tree(const_iterator pos) const {

				for (const_iterator it = begin(); it != end(); it++) {

					if (it == pos)
						return (true);
				}
				return (false);
			}

			node_pointer	_find_key(key_type const & key, node_pointer node) const {

				if (!node || node == _last)
					return (NULL);
				value_type	tmp = ft::make_pair<key_type, mapped_type>(key, mapped_type());
				if (_is_equal(tmp, node->value))
					return (node);
				if (this->_comp(key, node->value.first))
					return (_find_key(key, node->left));
				else if (this->_comp(node->value.first, key))
					return (_find_key(key, node->right));
				return (NULL);
			}

			bool			_is_equal(value_type const & x, value_type const & y) const {

				return (!_comp(x.first, y.first) && !_comp(y.first, x.first));
			}

			node_pointer	_create_node(value_type const & val) {
				
				node_pointer	node = _alloc.allocate(1);

				this->_alloc.construct(node, node_type(val, NULL, NULL, NULL));
				return (node);
			}

			bool	_insert_node(const value_type &val, node_pointer current) {	//proto a alleger ?

				if (!current)
					return (false);
				if (_is_equal(val, current->value))
					return (false);
				if (_comp(val.first, current->value.first)) {

					if (!current->left) {

						node_pointer	node = _create_node(val);
						node->parent = current;
						current->left = node;
						_size++;
						return (true);
					}
					else
						return (_insert_node(val, current->left));
				}
				else if (_comp(current->value.first, val.first)) {

					if (!current->right) {

						node_pointer	node = _create_node(val);
						node->parent = current;
						current->right = node;
						_size++;
						return (true);
					}
					else if (current->right == _last) {
						
						node_pointer	node = _create_node(val);
						_last->parent = node;
						node->right = _last;
						node->parent = current;
						current->right = node;
						_size++;
						return (true);
					}
					else
						return (_insert_node(val, current->right));
				}
				return (false);
			}

			bool	_insert_node_root(const value_type &val) {

				if (!this->_root) {

					this->_root = _create_node(val);
					_last->parent = this->_root;
					this->_root->right = _last;
					_size++;
					return (true);
				}
				if (this->_root == _last) {		//????? dans quel cas ?

					node_pointer	newRoot = _create_node(val);
					this->_root->parent = newRoot;
					newRoot->right = this->_root;
					this->_root = newRoot;
					_size++;
					return (true);
				}
				return (_insert_node(val, _root));
			}

			void	_transplant(node_pointer a, node_pointer b) {
				
				if (!a->parent)
					_root = b;
				else if (a == a->parent->left)
					a->parent->left = b;
				else
					a->parent->right = b;
				if (b)
					b->parent = a->parent;
			}

			void	_delete_node(node_pointer node) {

				node_pointer	y;

				y = node;
				if (!node->left)
					_transplant(node, node->right);
				else if (!node->right)  //? || node->right == _last
					_transplant(node, node->left);
				else {

					y = _minimum(node->right);
					if (y->parent != node) {

						_transplant(y, y->right);
						y->right = node->right;
						y->right->parent = y;
					}
					_transplant(node, y);
					y->left = node->left;
					y->left->parent = y;
				}
				if (node == _last) {

					node_pointer	max = _maximum(_root);
					if (max) {

						max->right = _last;
						_last->parent = max;
					}
				}
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
				this->_size--;
			}

			void	_clean_recursive(node_pointer node) {

				if (node && node != _last) {

					_clean_recursive(node->left);
					_clean_recursive(node->right);
					if (node->right == _last)
						_last->parent = NULL;
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					//node = NULL; // ?
				}
			}

	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> & x, map<Key, T, Compare, Alloc> & y)
	{
		x.swap(y);
	}

}

#endif
//std	==>		8:55.98		8:39.93
//ft	==>		9:22.97		9:30.06
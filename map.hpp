/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:39:08 by vintran           #+#    #+#             */
/*   Updated: 2022/04/09 06:58:31 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "utils/pair.hpp"
# include "utils/node.hpp"
# include "utils/iteratorTraits.hpp"
# include "utils/mapIterator.hpp"
# include "utils/reverseIterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>> >
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
					Compare comp;
				protected:
					value_compare(Compare c) : comp(c) {}
					bool operator()(const value_type &x, const value_type &y) const { return comp(x.first, y.first); }
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


//===================================================CONSTRUCTORS=================================================//

		public:

			// empty constructor
			explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _size(0), _root(NULL) {}
			
			// range constructor
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()/*,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL*/) ///////////////////// enable_if ???????????????
					: _comp(comp), _alloc(alloc), _size(0), _root(NULL) { insert(first, last); }
	
			//copy constructor
			map(const map & x) : _comp(x._comp), _alloc(x._alloc), _size(0), _root(NULL) { *this = x; }


//====================================================DESTRUCTOR===================================================//

			virtual ~map() { /*clear_tree(this->_root);*/ }		// clear_tree a faire  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//===============================================ASSIGNATION OPERATOR==============================================//

			map &	operator=(const map & rhs) {

				if (this != &rhs) {

					clear_tree(this->_root);
					insert(rhs.begin(), rhs.end());
				}
				return (*this);
			}


//=====================================================ITERATORS===================================================//

			iterator		begin() {
				
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

			iterator		end() {

				//if (!this->_root)			~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ a verif
				//	_initTree();
				if (this->_size == 0)
					return (NULL);	// return (this->_root);

				node_pointer	tmp = this->_root;
				while (tmp && tmp->nil == false)
					tmp = tmp->right;
				return (tmp);
			}

			const_iterator	end() const {

				if (this->_size == 0)
					return (const_iterator(this->_root));

				node_pointer	tmp = this->_root;
				while (tmp && !tmp->last)
					tmp = tmp->right;
				return (const_iterator(tmp));
			}

			reverse_iterator		rbegin() {

				//if (this->_size > 0) // else    ~~useless ?
				return (reverse_iterator(end()--));
			}

			const_reverse_iterator	rbegin() const {
				
				//comme au dessus
				return (const_reverse_iterator(end()--));
			}

			reverse_iterator		rend() {

				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const {

				return (const_reverse_iterator(begin()));
			}


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
				
				bool	is_insert = _insert_node_root(val);

				if (is_insert)
					this->_size++;
				return (ft::pair<iterator, bool>(_find_key(val.first, this->_root), is_insert));
			}



//===================================================MY FUNCTIONS==================================================//

		private:

			node_pointer	_find_key(key_type const & key, node_pointer node) const {

				if (!node)
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

			bool			_is_leaf(node_pointer node) const {

				if (node && !node->left && !node->right)
					return (true);
				return (false);
			}

			node_pointer	_create_node(value_type const & val) {
				
				node_pointer	node = _alloc.allocate(1);

				this->_alloc.construct(node, node_type(val, NULL, NULL, NULL, false));
				return (node);
			}

			bool	_insert_node(const value_type &val, node_pointer current)
			{

				if (!current)
					return (false);
				if (_is_equal(val, current->value))
					return (false);
				if (_comp(val.first, current->value.first)) {

					if (!current->left) {

						node_pointer	node = _create_node(val);
						node->parent = current;
						current->left = node;
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
						return (true);
					}
					else if (current->right->nil == true) {
						
						node_pointer	node = _create_node(val);
						node->right = current->right;
						node->parent = current;
						current->right = node;
						return (true);
					}
					else
						return (_insert_node(val, current->right));
				}
				return (false);
			}

			bool	_insert_node_root(const value_type &val)
			{
				if (!this->_root) {

					this->_root = _create_node(val);
					node_pointer	nil = _create_node(value_type());
					nil->nil = true;
					nil->parent = this->_root;
					this->_root->right = nil;
					return (true);
				}
				if (this->_root->nil == true) {

					node_pointer	newRoot = _create_node(val);
					this->_root->parent = newRoot;
					newRoot->right = this->_root;
					this->_root = newRoot;
					return (true);
				}
				return (_insert_node(val, _root));
			}




	};
	
}

#endif

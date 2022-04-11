/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 06:08:53 by vintran           #+#    #+#             */
/*   Updated: 2022/04/11 10:30:26 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "iteratorTraits.hpp"
# include <iostream>

namespace ft {
	
	template <typename T, typename node_pointer>
	class mapIterator {

		public:
			
			typedef T								value_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::bidirectional_iterator_tag	iterator_category;


		protected:
			
			node_pointer	_p;


		public:
			
			mapIterator() : _p(NULL) {}
			mapIterator(node_pointer p) : _p(p) {}
			mapIterator(mapIterator const & src) : _p(src._p) {}
			virtual ~mapIterator() {}
			
			mapIterator &	operator=(mapIterator const & rhs) {

				if (this != &rhs)
					this->_p = rhs._p;
				return (*this);
			}
			

			mapIterator &	operator++(void) {

				increase();
				return (*this);
			}

			mapIterator		operator++(int) {

				mapIterator it = *this;
				++(*this);
				return (it);
			}
			mapIterator &	operator--(void) {

				decrease();
				return (*this);
			}
			mapIterator		operator--(int) {

				mapIterator it = *this;
				--(*this);
				return (it);
			}

			reference		operator*() const {

				return (this->_p->value);
			}

			pointer			operator->() const {

				return (&(operator*()));
			}

			node_pointer	get_node() const {		// sans const ?

				return (this->_p);
			}

			operator	mapIterator<const T, node_pointer>() const {

				return (mapIterator<const T, node_pointer>(this->_p));
			}

			template <typename it2>
			bool		operator==(const mapIterator<it2, node_pointer> &rhs) const {

				return (this->_p == rhs.get_node());
			}

			template <typename it2>
			bool		operator!=(const mapIterator<it2, node_pointer> &rhs) const {
				return (this->_p != rhs.get_node());
			}

		protected:

			void	increase() {

				if (!this->_p)
					return ;
				if (this->_p->right) {
					
					this->_p = this->_p->right;
					while (this->_p->left)
						this->_p = this->_p->left;
				}
				else {
					
					node_pointer	tmp = this->_p->parent;
					while (this->_p && this->_p->left != tmp) {

						tmp = this->_p;
						this->_p = this->_p->parent;
					}
				}
			}

			void	decrease() {

				if (!this->_p)
					return ;
				//std::cout << "passage\n";
				if (this->_p->left) {

		       		//std::cout << "passage\n";
					this->_p = this->_p->left;
					while (this->_p->right)
						this->_p = this->_p->right;
				}
				
				else {
					node_pointer	tmp = this->_p->parent;
					while (this->_p && this->_p->right != tmp) {

						tmp = this->_p;
						this->_p = this->_p->parent;
					}
				}
			}

	};

	template <typename _T, typename _node_pointer>
    std::ostream    &operator<<(std::ostream &o, ft::mapIterator<_T, _node_pointer> const &rhs) {
        o << *rhs.get_node();
        return (o);
    }

}

#endif
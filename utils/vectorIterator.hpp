/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:12:30 by vintran           #+#    #+#             */
/*   Updated: 2022/03/31 02:22:40 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP
# include "iteratorTraits.hpp"

namespace ft {

template < class T >
class vectorIterator : public ft::iterator<random_access_iterator_tag, T> {


//================================TYPEDEF================================//

	public :

		typedef typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;


//========================CONSTRUCTOR / DESTRUCTOR========================//

		vectorIterator(void) : _element(NULL) {}

		vectorIterator(pointer element) : _element(element){

		}

		vectorIterator(vectorIterator const & src) {

			this->_element = src._element;
		}

		virtual	~vectorIterator() {

		}


//================================OPERATORS================================//

		operator	vectorIterator<const value_type>() const {				//?///????????????????????????/////???????????????////////????????????????///////////????????????????????????????

			return (vectorIterator<const value_type>(this->_element));
		};
 
		vectorIterator &operator=(const vectorIterator& rhs) {

			if (this == &rhs)
				return (*this);
			this->_element = rhs._element;
			return (*this);
		}

		friend bool	operator==(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._element == rhs._element)
				return (true);
			return (false);
		}

		friend bool	operator!=(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._element != rhs._element)
				return (true);
			return (false);
		}

		friend bool	operator<(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._element < rhs._element)
				return (true);
			return (false);
		}

		friend bool	operator>(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._element > rhs._element)
				return (true);
			return (false);
		}

		friend bool	operator<=(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._element <= rhs._element)
				return (true);
			return (false);
		}

		friend bool	operator>=(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._element >= rhs._element)
				return (true);
			return (false);
		}


//============================INCR_OPERATORS============================//

	// pre increase
		vectorIterator&	operator++(void) {

			++(this->_element);
			return (*this);
		}

	// post increase
		vectorIterator	operator++(int) {

			vectorIterator	tmp = (*this);

			++(this->_element);
			return (tmp);
		}

	// pre decrease
		vectorIterator&	operator--(void) {

			this->_element--;
			return (*this);
		}

	// post decrease
		vectorIterator	operator--(int) {

			vectorIterator	tmp = (*this);

			--(this->_element);
			return (tmp);
		}

		vectorIterator	operator+(difference_type const & rhs) const {

			return (this->_element + rhs);
		}

		friend vectorIterator	operator+(difference_type n, vectorIterator const &rhs) {

			return (rhs._element + n);
		};

		friend difference_type	operator+(vectorIterator const &lhs, vectorIterator const &rhs) {//???

			return (lhs._element + rhs._element);
		};

		vectorIterator			operator+=(difference_type rhs) {

			return (vectorIterator(this->_element += rhs));
		}

		vectorIterator	operator-(difference_type const & rhs) const {

			return (this->_element - rhs);
		}

		friend vectorIterator	operator-(difference_type n, vectorIterator const &rhs) {

			return (rhs._element - n);
		};

		friend difference_type	operator-(vectorIterator const &lhs, vectorIterator const &rhs) {//???

			return (lhs._element - rhs._element);
		};

		vectorIterator			operator-=(difference_type const & rhs) {

			return (vectorIterator(this->_element -= rhs));
		}


//===========================VALUES_OPERATORS==========================//				????????????????????????

		difference_type		operator+(vectorIterator b) {

			return (this->_element + b._element);
		}

		difference_type		operator-(vectorIterator b) {

			return (this->_element - b._element);
		}


//===============DEREFERENCING / RANDOM_ACCESS_OPERATORS================//

		reference	operator*(void) const {

			return (*(this->_element));
		}

		reference	operator[](difference_type value) const {

			return (*(this->_element + value));
		}

		pointer		operator->(void) const {

			return (this->_element);
		}


//==============================VARIABLES==============================//

	private:

		pointer		_element;

};


};

#endif
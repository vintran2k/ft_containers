/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:12:30 by vintran           #+#    #+#             */
/*   Updated: 2022/03/30 15:08:43 by vintran          ###   ########.fr       */
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

		vectorIterator(void);

		vectorIterator(pointer p) : _p(p){

		}

		vectorIterator(vectorIterator const & src) {

			this->_p = src._p;
		}

		virtual	~vectorIterator() {

		}


//================================OPERATORS================================//

		operator	vectorIterator<const value_type>() const {				//?///????????????????????????/////???????????????////////????????????????///////////????????????????????????????

			return (vectorIterator<const value_type>(this->_p));
		};
 
		vectorIterator &operator=(const vectorIterator& rhs) {

			if (this == &rhs)
				return (*this);
			this->_p = rhs._p;
			return (*this);
		}

		bool	operator==(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._p == rhs._p)
				return (true);
			return (false);
		}

		bool	operator!=(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._p != rhs._p)
				return (true);
			return (false);
		}

		bool	operator<(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._p < rhs._p)
				return (true);
			return (false);
		}

		bool	operator>(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._p > rhs._p)
				return (true);
			return (false);
		}

		bool	operator<=(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._p <= rhs._p)
				return (true);
			return (false);
		}

		bool	operator>=(vectorIterator const & lhs, vectorIterator const & rhs) {

			if (lhs._p >= rhs._p)
				return (true);
			return (false);
		}


//============================INCR_OPERATORS============================//

	// pre increase
		vectorIterator&	operator++(void) {

			++(this->_p);
			return (*this);
		}

	// post increase
		vectorIterator	operator++(int) {

			vectorIterator	tmp = (*this);

			++(this->_p);
			return (tmp);
		}

	// pre decrease
		vectorIterator&	operator--(void) {

			this->_p--;
			return (*this);
		}

	// post decrease
		vectorIterator	operator--(int) {

			vectorIterator	tmp = (*this);

			--(this->_p);
			return (tmp);
		}

		vectorIterator	operator+(difference_type const & rhs) const {

			return (this->_p + rhs);
		}

		vectorIterator	operator+(difference_type n, vectorIterator const &rhs) {

			return (rhs._p + n);
		};

		difference_type	operator+(vectorIterator const &lhs, vectorIterator const &rhs) {//???

			return (lhs._p + rhs._p);
		};

		vectorIterator			operator+=(difference_type rhs) {

			return (vectorIterator(this->_p += rhs));
		}

		vectorIterator	operator-(difference_type const & rhs) const {

			return (this->_p - rhs);
		}

		vectorIterator	operator-(difference_type n, vectorIterator const &rhs) {

			return (rhs._p - n);
		};

		difference_type	operator-(vectorIterator const &lhs, vectorIterator const &rhs) {//???

			return (lhs._p - rhs._p);
		};

		vectorIterator			operator-=(difference_type const & rhs) {

			return (vectorIterator(this->_p -= rhs));
		}


//===========================VALUES_OPERATORS==========================//				????????????????????????

		difference_type		operator+(vectorIterator b) {

			return (this->_p + b._p);
		}

		difference_type		operator-(vectorIterator b) {

			return (this->_p - b._p);
		}


//===============DEREFERENCING / RANDOM_ACCESS_OPERATORS================//

		reference	operator*(void) const {

			return (*(this->_p));
		}

		reference	operator[](difference_type value) const {

			return (*(this->_p + value));
		}

		pointer		operator->(void) const {

			return (this->_p);
		}


//==============================VARIABLES==============================//

	private:

		pointer		_p;

};


};

#endif
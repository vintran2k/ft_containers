/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:42:56 by vintran           #+#    #+#             */
/*   Updated: 2022/04/06 03:42:30 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {

	template < class T, class Container = ft::vector<T> >
	class stack {

		public:

//========================================TYPEDEF========================================//

			typedef T										value_type;
			typedef Container								container_type;
			typedef size_t									size_type;


//=======================================CONSTUCTOR=======================================//

			explicit stack(container_type const &ctnr = container_type()) : _ctnr(ctnr) {}


//====================================MEMBER FUNCTIONS====================================//

			bool				empty() const { return _ctnr.empty(); }

			size_type			size() const { return _ctnr.size(); }

			value_type			&top() { return _ctnr.back(); }

			const value_type	&top() const { return _ctnr.back(); }

			void				push(value_type const &val) { _ctnr.push_back(val); }

			void				pop() { _ctnr.pop_back(); }


			template <typename _T, typename _Container>
			friend bool			ft::operator==(stack<_T, _Container> const &lhs, stack<_T, _Container> const &rhs);

			template <typename _T, typename _Container>
			friend bool			ft::operator<(stack<_T, _Container> const &lhs, stack<_T, _Container> const &rhs);


//==================================PROTECTED ATTRIBUTES==========================+======//

	protected:

			container_type		_ctnr;

	};


//=============================NON-MEMBER RELATIONAL OPERATORS===========================//

	template <typename _Tp, typename Container>
	bool	operator==(stack<_Tp, Container> const &lhs, stack<_Tp, Container> const &rhs)
	{
		return (lhs._ctnr == rhs._ctnr);
	}
	
	template <typename _Tp, typename Container>
	bool	operator<(stack<_Tp, Container> const &lhs, stack<_Tp, Container> const &rhs)
	{
		return (lhs._ctnr < rhs._ctnr);
	}
	
	template <typename _Tp, typename Container>
	bool	operator!=(stack<_Tp, Container> const &lhs, stack<_Tp, Container> const &rhs)
	{
		return (!(lhs == rhs));
	}
	
	template <typename _Tp, typename Container>
	bool	operator>(stack<_Tp, Container> const &lhs, stack<_Tp, Container> const &rhs)
	{
		return (rhs < lhs);
	}
	
	template <typename _Tp, typename Container>
	bool	operator<=(stack<_Tp, Container> const &lhs, stack<_Tp, Container> const &rhs)
	{
		return (!(rhs < lhs));
	}
	
	template <typename _Tp, typename Container>
	bool	operator>=(stack<_Tp, Container> const &lhs, stack<_Tp, Container> const &rhs)
	{
		return (!(lhs < rhs));
	}

};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:42:56 by vintran           #+#    #+#             */
/*   Updated: 2022/04/13 08:04:15 by vintran          ###   ########.fr       */
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

			explicit stack(container_type const &ctnr = container_type()) : c(ctnr) {}


//====================================MEMBER FUNCTIONS====================================//

			bool				empty() const { return c.empty(); }

			size_type			size() const { return c.size(); }

			value_type			&top() { return c.back(); }

			const value_type	&top() const { return c.back(); }

			void				push(value_type const &val) { c.push_back(val); }

			void				pop() { c.pop_back(); }


			template <typename _T, typename _Container>
			friend bool			ft::operator==(stack<_T, _Container> const &lhs, stack<_T, _Container> const &rhs);

			template <typename _T, typename _Container>
			friend bool			ft::operator<(stack<_T, _Container> const &lhs, stack<_T, _Container> const &rhs);


//==================================PROTECTED ATTRIBUTES==========================+======//

	protected:

			container_type		c;

	};


//=============================NON-MEMBER RELATIONAL OPERATORS===========================//

	template <typename T, typename Container>
	bool	operator==(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return (lhs.c == rhs.c);
	}
	
	template <typename T, typename Container>
	bool	operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return (lhs.c < rhs.c);
	}
	
	template <typename T, typename Container>
	bool	operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return (!(lhs == rhs));
	}
	
	template <typename T, typename Container>
	bool	operator>(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return (rhs < lhs);
	}
	
	template <typename T, typename Container>
	bool	operator<=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return (!(rhs < lhs));
	}
	
	template <typename T, typename Container>
	bool	operator>=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return (!(lhs < rhs));
	}

};

#endif

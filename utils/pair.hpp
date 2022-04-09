/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:44:25 by vintran           #+#    #+#             */
/*   Updated: 2022/04/08 07:02:14 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

	template <class T1, class T2>
	struct pair {
		
//=================================TYPEDEF=================================//

		typedef		T1 first_type;
		typedef		T2 second_type;


//================================ATTRIBUTES================================//

		first_type first;
		second_type second;


//===============================CONSTRUCTORS===============================//

		// default constructors
		pair() : first(), second() {}

		// copy constructor
		template<class U, class V>
		pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

		// initialization constructor
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}


//==============================MEMBER FUNCTIONS=============================//

		pair&	operator=(const pair& pr) {

			if (this != &pr)
			{
				this->first = pr.first;
				this->second = pr.second;
			}
			return (*this);
		}

	};


//============================RELATIONNAL OPERATORS===========================//


	template <class T1, class T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1,T2>& rhs) {

		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1,T2>& rhs) {

		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1,T2>& rhs) {

		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1,T2>& rhs) {

		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1,T2>& rhs) {

		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1,T2>& rhs) {

		return (!(lhs < rhs));
	}

	template <typename T1, typename T2>
    pair<T1, T2>	make_pair(T1 x, T2 y) {

        return (pair<T1, T2>(x, y));
    }

}

#endif

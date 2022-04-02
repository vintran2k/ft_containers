/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 20:21:35 by vintran           #+#    #+#             */
/*   Updated: 2022/03/31 20:22:50 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2) {

		while (first1 != last1) {

			if (first2 == last2 || *(first2) < *(first1))
				return (false);
			else if (*(first1) < *(first2))
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

};

#endif
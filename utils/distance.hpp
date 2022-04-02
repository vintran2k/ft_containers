/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 02:01:05 by vintran           #+#    #+#             */
/*   Updated: 2022/03/31 02:04:55 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISTANCE_HPP
# define DISTANCE_HPP
# include "iteratorTraits.hpp"

namespace ft {

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {

		typename iterator_traits<InputIterator>::difference_type len = 0;

		while (first != last) {

			len++;
			++first;
		}
		return (len);
	}

}

#endif

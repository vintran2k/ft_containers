/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteratorTraits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:36:15 by vintran           #+#    #+#             */
/*   Updated: 2022/03/27 20:24:29 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP
# include <cstddef>

namespace ft {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<typename _Category, typename _Tp, typename _Distance = std::ptrdiff_t,
			typename _Pointer = _Tp*, typename _Reference = _Tp&>
	struct iterator {

		typedef _Category	iterator_category;
		typedef _Tp			value_type;
		typedef _Distance	difference_type;
		typedef _Pointer	pointer;
		typedef _Reference	reference;
	};

	template<typename _Iterator>
	struct iterator_traits {

		typedef typename _Iterator::value_type			value_type;
		typedef typename _Iterator::difference_type		difference_type;
		typedef typename _Iterator::pointer				pointer;
		typedef typename _Iterator::reference			reference;
	};

	/// Partial specialization for pointer types.
	template<typename Tp>
	struct iterator_traits<Tp*> {

		typedef random_access_iterator_tag	iterator_category;
		typedef Tp							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef Tp*							pointer;
		typedef Tp&							reference;
	};

	/// Partial specialization for const pointer types.
	template<typename Tp>
	struct iterator_traits<const Tp*> {

		typedef random_access_iterator_tag	iterator_category;
		typedef Tp							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef const Tp*					pointer;
		typedef const Tp&					reference;
	};
};

#endif

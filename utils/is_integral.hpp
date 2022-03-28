/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:15:17 by vintran           #+#    #+#             */
/*   Updated: 2022/03/24 11:44:22 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTGRAL_HPP

namespace ft {

	/// integral_constant template struct
	template <class T, T v>
	struct integral_constant {

		static const T	value = v;

		typedef T value_type;

		typedef integral_constant<T, v> type;

		operator T() { return v; }
	};

	/// The type used as a compile-time boolean with true value
	typedef integral_constant<bool, true>	true_type;

	/// The type used as a compile-time boolean with false value
	typedef integral_constant<bool, false>	false_type;

	/// is_integral template struct
	template <class T>
	struct is_integral : public false_type {};

	template <>
	struct is_integral<bool> : public true_type {};

	template <>
	struct is_integral<char> : public true_type {};

	template <>
	struct is_integral<signed char> : public true_type {};

	template <>
	struct is_integral<unsigned char> : public true_type {};

	template <>
	struct is_integral<wchar_t> : public true_type {};

	template <>
	struct is_integral<short> : public true_type {};

	template <>
	struct is_integral<unsigned short> : public true_type {};

	template <>
	struct is_integral<int> : public true_type {};

	template <>
	struct is_integral<unsigned int> : public true_type {};

	template <>
	struct is_integral<long> : public true_type {};

	template <>
	struct is_integral<long long> : public true_type {};

	template <>
	struct is_integral<unsigned long> : public true_type {};

	template <>
	struct is_integral<unsigned long long> : public true_type {};

};
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 05:32:21 by vintran           #+#    #+#             */
/*   Updated: 2022/04/09 06:17:52 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

namespace ft {

	template <typename T>
	struct node {
		
		T		value;
		node	*left;
		node	*right;
		node	*parent;
		bool	nil;

		node(T val, node *l, node *r, node *p, bool n) : value(val), left(l), right(r), parent(p), nil(n) {}
	};
}

#endif
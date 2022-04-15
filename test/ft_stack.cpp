/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:40:11 by vintran           #+#    #+#             */
/*   Updated: 2022/04/15 03:02:06 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <deque>
#include <vector>
#include "../stack.hpp"

void	ft_main_stack(void)
{
	std::cout << "*********************************************************STACK TESTS*********************************************************" << std::endl;

	std::cout << "=== CONSTRUCTORS, EMPTY ===\n" << '\n';
	ft::stack<char> first;
	ft::stack<char, std::vector<char> > second;

	std::cout << "-> First is empty = " << first.empty() << '\n';
	std::cout << "-> First is empty = " << second.empty() << '\n';

	std::cout << "\n=== PUSH, POP, SIZE, TOP ===\n" << '\n';

	std::cout << "-> Push: (! t u l a S)\n";
	first.push('!');
	first.push('t');
	first.push('u');
	first.push('l');
	first.push('a');
	first.push('S');
	std::cout << "-> Size = " << first.size() << "\n\n";
	std::cout << "-> Top = " << first.top() << '\n';
	std::cout << "* Pop *\n";
	first.pop();
	std::cout << "-> Top = " << first.top() << '\n';
	std::cout << "* Pop *\n";
	first.pop();
	std::cout << "-> Top = " << first.top() << '\n';
	std::cout << "* Pop *\n";
	first.pop();
	std::cout << "-> Top = " << first.top() << '\n';
	std::cout << "* Pop *\n";
	first.pop();
	std::cout << "-> Top = " << first.top() << '\n';
	std::cout << "* Pop *\n";
	first.pop();
	std::cout << "-> Top = " << first.top() << '\n';

	std::cout << "\n-> Size = " << first.size() << '\n';
	
	std::cout << "\n=== OVERLOADS NON-MEMBERS ===\n" << '\n';
	
	ft::stack<int> a,b,c,d;

	a.push(1);
	a.push(2);

	b.push(1);
	b.push(2);

	std::cout << "a & b :\n\n";
	if (a == b)
		std::cout << "Equal\n";
	else
		std::cout << "Not equal\n";
	
	if (a != b)
		std::cout << "Not equal\n";
	else
		std::cout << "Equal\n";

	if (a < b || a > b)
		std::cout << "Not equal\n";
	else if (a >= b || a <= b)
		std::cout << "Equal\n";

	std::cout << "\n";


	c.push(4);

	d.push(42);

	std::cout << "\nc & d :\n\n";
	if (c == d)
		std::cout << "Equal\n";
	else
		std::cout << "Not equal\n";
	
	if (c != d)
		std::cout << "Not equal\n";
	else
		std::cout << "Equal\n";

	if (c < d || c > d)
		std::cout << "Not equal\n";
	else if (c >= d || c <= d)
		std::cout << "Equal\n";

	if (c > d)
		std::cout << "c > d\n";
	else
		std::cout << "c <= d\n";
}
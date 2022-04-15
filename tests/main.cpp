/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:25:34 by vintran           #+#    #+#             */
/*   Updated: 2022/04/15 01:25:44 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tests.hpp"

int main(int argc, char **argv)
{
	std::string choice;
	if (argc != 2)
	{
		std::cout << "No test given, testing vector." << std::endl;
		choice = "vector";
	}
	else
		choice = std::string(argv[1]);
	if (choice == "vector")
		test_vector();
	else if (choice == "list")
		test_list();
	else if (choice == "map")
		test_map();
	else if (choice == "stack")
		test_stack();
	else if (choice == "all")
	{
		test_vector();
		test_list();
		test_map();
		test_stack();
	}
	else
		std::cout << "No test for " << choice << std::endl;

	return (0);
}

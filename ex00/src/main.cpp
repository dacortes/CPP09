/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:51:10 by dacortes          #+#    #+#             */
/*   Updated: 2024/09/11 08:28:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <BitcoinExchange.hpp>

void parsing_arguments(int numArguments)
{
	if (numArguments < 2)
		std::exit(error_msg(1, ERROR_INVALID_ARGUMENTS, numArguments));
	if (numArguments > 2)
		std::exit(error_msg(1, ERROR_TOO_MANY_ARG, numArguments));
}

int main(int ac, char **av)
{
	parsing_arguments(ac);
	try
	{
		BitcoinExchange	foo(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}
	return (EXIT_SUCCESS);
}

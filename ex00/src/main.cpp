/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:51:10 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/22 10:14:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/BitcoinExchange.hpp"
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
	(void)ac;
	(void)av;
	parsing_arguments(ac);
	return (EXIT_SUCCESS);
}

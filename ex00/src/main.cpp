/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:51:10 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/21 10:56:12 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/BitcoinExchange.hpp"
#include <BitcoinExchange.hpp>

int	error_msg(int	exitCode, std::string error, std::string name)
{
	std::cerr << RED << "Error: " << END << error << name << std::endl;
	return (exitCode);
}

void parsing_arguments(int numArguments)
{
	std::stringstream ss;
	ss << numArguments;
	std::string numStr = ss.str();
	if (numArguments < 2)
		std::exit(error_msg(1, ERROR_INVALID_ARGUMENTS, numStr));
	if (numArguments > 2)
		std::exit(error_msg(1, ERROR_TOO_MANY_ARG, numStr));
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	parsing_arguments(ac);
	return (EXIT_SUCCESS);
}

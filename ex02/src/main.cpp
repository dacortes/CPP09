#include <PmergeMe.hpp>

void parsing_arguments(int numArguments)
{
	if (numArguments < 2)
		std::exit(error_msg(1, ERROR_INVALID_ARGUMENTS, numArguments));
	if (numArguments > 2)
		std::exit(error_msg(1, ERROR_TOO_MANY_ARG, numArguments));
}

timespec timespecDiff(const timespec& tl, const timespec& tr)
{
	timespec result = tl;

	if (tl.tv_sec < tr.tv_sec ||
		(tl.tv_sec == tr.tv_sec && tl.tv_nsec < tr.tv_nsec)
	)
		return (tl);

	if (tl.tv_nsec < tr.tv_nsec)
	{
		result.tv_sec -= tr.tv_sec + 1;
		result.tv_nsec = 1000000000 - tr.tv_nsec + tl.tv_nsec;
	}
	else 
	{
		result.tv_sec -= tr.tv_sec;
		result.tv_nsec -= tr.tv_nsec;
	}
	return (result);
}

template<typename contType>
timespec doTest(std::string inpNumbers, contType& queue)
{
	std::stringstream	numbers(inpNumbers);
	std::string 		number;
	struct timespec		start, end;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	while (numbers >> number)
		queue.push(number);
	queue.sort();
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	return (timespecDiff(end, start));
}

int main(int ac, char **av)
{
	sorter<std::deque<int> >			queueSorter;
	sorter<std::vector<int> >			vectorSorter;
	std::string							numbers;

	parsing_arguments(ac);
	for (int i = 1; i < ac; i++)
	{
		numbers = numbers + std::string(" ") + std::string(av[i]);
		numbers.erase(numbers.size(), 1);
	}
	std::cout << "NUMBERS : " << numbers << std::endl;
	struct timespec duration0;
	struct timespec duration1;
	try
	{
		duration0 = doTest(numbers, queueSorter);
		duration1 = doTest(numbers, vectorSorter);
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
		return (1);
	}
	std::cout << "Before: " ; queueSorter.printInitial(); std::cout << std::endl << std::endl;
	std::cout << "After: " ; queueSorter.print(); std::cout << std::endl;
	std::cout << "Time to process with queue: " << duration0.tv_sec << ", " <<  
				duration0.tv_nsec << "ns." << std::endl;
	std::cout << "Time to process with vector: " << duration1.tv_sec << ", " <<  
				duration1.tv_nsec << "ns." << std::endl;
	std::cout << std::endl;
}

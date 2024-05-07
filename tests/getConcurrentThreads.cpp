#include <iostream>
#include <thread>



int main()
{
	const auto processors = std::thread::hardware_concurrency();
	std::cout << "Number of processors: " << processors << "\n";
	return 0;
}

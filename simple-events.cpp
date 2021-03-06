
#include <iostream>
#include <string>
#include <conio.h>
#include "simple-events.h"

void prints(const std::string& e)
{
	std::cout << "From prints: " << e << std::endl;
}

int main(int argc, char *argv[])
{
	Event<void(const std::string&)> messageReceived;

	auto printLambda = [](const std::string& e) -> void
	{
		std::cout << "From print lambda: " << e << std::endl;
	};

	Event<void(const std::string&)>::Delegate printDelegate1(printLambda); // Testing lambda
	Event<void(const std::string&)>::Delegate printDelegate2(prints); // Testing standard functions
	Event<void(const std::string&)>::Delegate printDelegate3(printLambda); // Testing lamda on another delegate instance
	Event<void(const std::string&)>::Delegate printDelegate4(printDelegate1); // Testing copy ctor
	Event<void(const std::string&)>::Delegate printDelegate5 = printDelegate1; // Testing assignation

	std::cout << "Delegates 2 and 3 should be unique" << std::endl << std::endl << std::boolalpha;

	std::cout << "Is Delegate 1 the same as delegate 1? " << (printDelegate1 == printDelegate1) << std::endl;
	std::cout << "Is Delegate 1 the same as delegate 2? " << (printDelegate1 == printDelegate2) << std::endl;
	std::cout << "Is Delegate 1 the same as delegate 3? " << (printDelegate1 == printDelegate3) << std::endl;
	std::cout << "Is Delegate 1 the same as delegate 4? " << (printDelegate1 == printDelegate4) << std::endl;
	std::cout << "Is Delegate 1 the same as delegate 5? " << (printDelegate1 == printDelegate5) << std::endl;

	std::cout << std::endl << std::endl;

	messageReceived += printDelegate1;
	messageReceived += printDelegate2;
	messageReceived += printDelegate3;
	messageReceived += printDelegate4;
	messageReceived += printDelegate5;

	messageReceived("This should be printed five times");

	std::cout << std::endl;

	messageReceived -= printDelegate1;
	messageReceived -= printDelegate2;
	messageReceived -= printDelegate3;

	messageReceived("This should be printed two times");

	std::cout << std::endl;

	messageReceived -= printDelegate4;
	messageReceived -= printDelegate5;

	messageReceived("Whoops! Something is wrong: this is not supposed to be printed");

	getch();

	return 0;
}
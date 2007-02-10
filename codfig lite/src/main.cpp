#include <iostream>

#include "Config.h"
using namespace CodfigLite;

int main()
{
	{
		std::cout << "Writing to file..." << std::endl << std::endl;
		Config fig;
		int x = 5, y = 6;
		std::string s("i am teh lamez0r z0r");
		fig.add("x", x);
		fig.add("y", y);
		fig.add("s", s);

		try
		{
			double d = fig.get<double>("x");
		}
		catch (codfiglite_exception& e)
		{
			std::cout << "Couldn't get int as double" << std::endl;
		}

		int kk = fig.get<int>("x");
		std::cout << kk << std::endl;

		std::ofstream out("test.conf");
		fig.save(out);
		std::cout << "wrote config to test.conf" << std::endl << std::endl << std::endl;
	}

	{
		std::cout << "Reading from file..." << std::endl << std::endl;
		Config fig;
		std::ifstream in("test.conf");
		fig.load(in);
		std::cout << "read config from test.conf" << std::endl;

		std::cout << fig.get<int>("x") << std::endl;
		try
		{
			std::cout << fig.get<std::string>("y") << std::endl;
		}
		catch (codfiglite_exception& e)
		{
			std::cout << "Couldn't get int as string" << std::endl;
		}
		std::cout << fig.get<std::string>("s") << std::endl;

		double d = 5.5;
		fig.add("more", d);
		fig.addComment("more", "bla bla bla");
		std::ofstream out("test.conf");
		fig.save(out);
	}

	std::cout << "press enter to continue" << std::endl;
	std::cin.get();
}
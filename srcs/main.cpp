#include "Application.hpp"

int main(int argc, char **argv)
{
	try
	{
		Application app(argc, argv);
		app.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
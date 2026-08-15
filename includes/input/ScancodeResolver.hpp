#ifndef SCANCODERESOLVER_HPP
#define SCANCODERESOLVER_HPP

#include <unordered_map>
#include <string>
#include <stdexcept>

#include "Scancode.hpp"

class ScancodeResolver
{
	public:
		ScancodeResolver();
		~ScancodeResolver();

		int get(Scancode sc) const;
	private:
		std::unordered_map<int, int> _table;

		int resolve(int glfwkey, std::string name);
};
#endif
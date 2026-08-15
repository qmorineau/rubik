#include "ScancodeResolver.hpp"

#include <GLFW/glfw3.h>

ScancodeResolver::ScancodeResolver()
{
	_table[static_cast<int>(Scancode::KEY_ESC)] = resolve(GLFW_KEY_ESCAPE, "KEY_ESC");
	_table[static_cast<int>(Scancode::KEY_TAB)] = resolve(GLFW_KEY_TAB, "KEY_TAB");
	_table[static_cast<int>(Scancode::KEY_W)] = resolve(GLFW_KEY_W, "KEY_W");
	_table[static_cast<int>(Scancode::KEY_A)] = resolve(GLFW_KEY_A, "KEY_A");
	_table[static_cast<int>(Scancode::KEY_S)] = resolve(GLFW_KEY_S, "KEY_S");
	_table[static_cast<int>(Scancode::KEY_D)] = resolve(GLFW_KEY_D, "KEY_D");
	_table[static_cast<int>(Scancode::KEY_R)] = resolve(GLFW_KEY_R, "KEY_R");
	_table[static_cast<int>(Scancode::KEY_F)] = resolve(GLFW_KEY_F, "KEY_F");
	_table[static_cast<int>(Scancode::KEY_B)] = resolve(GLFW_KEY_B, "KEY_B");
	_table[static_cast<int>(Scancode::KEY_LEFT)] = resolve(GLFW_KEY_LEFT, "KEY_LEFT");
	_table[static_cast<int>(Scancode::KEY_RIGHT)] = resolve(GLFW_KEY_RIGHT, "KEY_RIGHT");
	_table[static_cast<int>(Scancode::KEY_UP)] = resolve(GLFW_KEY_UP, "KEY_UP");
	_table[static_cast<int>(Scancode::KEY_DOWN)] = resolve(GLFW_KEY_DOWN, "KEY_DOWN");
}

ScancodeResolver::~ScancodeResolver() = default;

int ScancodeResolver::get(Scancode sc) const
{
	return _table.at(static_cast<int>(sc));
};

int ScancodeResolver::resolve(int glfwkey, std::string name)
{
	int sc = glfwGetKeyScancode(glfwkey);
	if (sc == -1)
	{
		throw std::runtime_error(std::string("ScancodeResolver: failed to resolve scancode for " + name));
	}
	return sc;
}
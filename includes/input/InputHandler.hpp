#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <memory>
#include <array>
#include <unordered_map>

#include "Scancode.hpp"
#include "ScancodeResolver.hpp"

class ICommand;
class Application;


class InputHandler
{
	public:
		enum CommandID
		{
			CMD_MOUSE_MOVE = 9,
			CMD_MOUSE_SCROLL = 10,
		};
		InputHandler();
		~InputHandler();
		
		void onKeyPressed(Application* app, int key);
		void onMouseEvent(Application* app, int key);
		void updateHeldKey(Application* app);

	private:
		struct InputKey
		{
			int key;
			int mod;
			bool operator==(const InputKey& k) const
			{
				return (k.key == key && k.mod == mod);
			};
		};
		struct InputKeyHash // to put in the hashtable 
		{
			size_t operator()(const InputKey& k) const
			{
				return k.key | (k.mod << 16);  // bits 0-15 = key, bits 16-31 = mod
			}    
		};

		struct InputBindings
		{
			std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash> onPressed;
			std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash> whileHeld;
			std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash> mouse;
		};

		InputBindings		_commands;
		ScancodeResolver	_scancodes;

		bool executeCommand(Application * app, std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash>& map, InputKey key);
};

 #endif
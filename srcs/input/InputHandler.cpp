#include "InputHandler.hpp"
#include "commands.hpp"
#include "Application.hpp"

InputHandler::InputHandler()
{
	using IK = InputKey;
	using SC = Scancode;
	// Mouse Button
	auto& mouseMap = _commands.mouse;
	mouseMap[IK{GLFW_MOUSE_BUTTON_LEFT, 0}] = std::make_unique<Commands::DisableMouse>();
	mouseMap[IK{CMD_MOUSE_MOVE, 0}] = std::make_unique<Commands::MouseMove>();
	mouseMap[IK{CMD_MOUSE_SCROLL, 0}] = std::make_unique<Commands::MouseScroll>();

	// Key Press
	auto& onPressedMap = _commands.onPressed;
	onPressedMap[IK{_scancodes.get(SC::KEY_ESC), 0}] = std::make_unique<Commands::CloseWindow>();
	onPressedMap[IK{_scancodes.get(SC::KEY_TAB), 0}] = std::make_unique<Commands::EnableMouse>();
	onPressedMap[IK{_scancodes.get(SC::KEY_R), 0}] = std::make_unique<Commands::ResetCamera>();
	onPressedMap[IK{_scancodes.get(SC::KEY_ENTER), 0}] = std::make_unique<Commands::ScrambleCube>();
	onPressedMap[IK{_scancodes.get(SC::KEY_SPACE), 0}] = std::make_unique<Commands::SolveCube>();
	onPressedMap[IK{_scancodes.get(SC::KEY_1), 0}] = std::make_unique<Commands::ResetCube>();
	onPressedMap[IK{_scancodes.get(SC::KEY_LEFT), 0}] = std::make_unique<Commands::L>();
	onPressedMap[IK{_scancodes.get(SC::KEY_LEFT), GLFW_MOD_CONTROL}] = std::make_unique<Commands::LPrime>();
	onPressedMap[IK{_scancodes.get(SC::KEY_RIGHT), 0}] = std::make_unique<Commands::R>();
	onPressedMap[IK{_scancodes.get(SC::KEY_RIGHT), GLFW_MOD_CONTROL}] = std::make_unique<Commands::RPrime>();
	onPressedMap[IK{_scancodes.get(SC::KEY_UP), 0}] = std::make_unique<Commands::U>();
	onPressedMap[IK{_scancodes.get(SC::KEY_UP), GLFW_MOD_CONTROL}] = std::make_unique<Commands::UPrime>();
	onPressedMap[IK{_scancodes.get(SC::KEY_DOWN), 0}] = std::make_unique<Commands::D>();
	onPressedMap[IK{_scancodes.get(SC::KEY_DOWN), GLFW_MOD_CONTROL}] = std::make_unique<Commands::DPrime>();
	onPressedMap[IK{_scancodes.get(SC::KEY_F), 0}] = std::make_unique<Commands::F>();
	onPressedMap[IK{_scancodes.get(SC::KEY_F), GLFW_MOD_CONTROL}] = std::make_unique<Commands::FPrime>();
	onPressedMap[IK{_scancodes.get(SC::KEY_B), 0}] = std::make_unique<Commands::B>();
	onPressedMap[IK{_scancodes.get(SC::KEY_B), GLFW_MOD_CONTROL}] = std::make_unique<Commands::BPrime>();


	// Repeat Key
	auto& whileHeldMap = _commands.whileHeld;
	whileHeldMap[IK{_scancodes.get(SC::KEY_W), 0}] = std::make_unique<Commands::CameraForward>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_S), 0}] = std::make_unique<Commands::CameraBackward>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_A), 0}] = std::make_unique<Commands::CameraLeft>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_D), 0}] = std::make_unique<Commands::CameraRight>();
}

InputHandler::~InputHandler() {};

void InputHandler::onKeyPressed(Application* app, int key)
{
	InputKey inputKey = {key, app->inputContext().getMods()};
	executeCommand(app, _commands.onPressed, inputKey);
};

void InputHandler::onMouseEvent(Application* app, int key)
{
	InputKey inputKey = {key, app->inputContext().getMods()};
	executeCommand(app, _commands.mouse, inputKey);
}

void InputHandler::updateHeldKey(Application* app)
{
	InputContext ctx = app->inputContext();

	for (const auto& key : ctx.activeKeys())
	{
		InputKey inputKey = {key, app->inputContext().getMods()};
		executeCommand(app, _commands.whileHeld, inputKey);
	}
}

bool InputHandler::executeCommand(Application * app, std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash>& map, InputKey key)
{
	const auto& it = map.find(key);
	if (it != map.end())
	{
		it->second->execute(app);
		return true;
	}
	else
		return false;
};
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <string>
#include <exception>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "InputManager.hpp"
#include "InputHandler.hpp"
#include "InputContext.hpp"
#include "Renderer.hpp"
#include "Parser.hpp"
#include "Window.hpp"
#include "Scene.hpp"
#include "Solver.hpp"

class Application
{
	public:
		Application(int argc, char *argv[]);
		~Application();
		
		void run();

		// getter
		Window&			window() 			{return _window;};
		float			getDelta() 			{return _deltaTime;};
		Camera&			getCamera() 		{return _scene->camera();};
		Renderer&		renderer() 			{return _renderer;};
		Scene*			scene() 			{return _scene;};
		Solver&			solver() 			{return _solver;};
		InputManager&	inputManager()		{return _inputManager;};
		InputHandler&	inputHandler()		{return _inputHandler;};
		InputContext&	inputContext()		{return _inputContext;};
		bool			debug()				{return _debug;};
	private:
		Parser				_parser;
		Window				_window;
		InputManager		_inputManager;
		InputHandler		_inputHandler;
		InputContext		_inputContext;
		Scene*				_scene;
		Renderer			_renderer;
		Solver				_solver;
		float				_deltaTime = 0.0f;
		float				_lastFrame = 0.0f;
		bool				_debug = 1;

		void 		renderLoop();
		void 		endFrame();
};

#endif
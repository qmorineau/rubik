#include "Application.hpp"

Application::Application(int argc, char *argv[]) :
	_window(this),
	_scene(nullptr)
{
	auto moves = _parser.parse(argc, argv);
	_scene = new Scene();
	_solver = new Solver();
	for (auto m : moves)
	{
		_scene->cube().move(m, false);
		_solver->move(m);
	}
}
		

Application::~Application()
{
	if (_scene)
		delete _scene;
	if (_solver)
		delete _solver;
}

void Application::run()
{		
	renderLoop();
}

void Application::renderLoop()
{
	// glfwSwapInterval(0); // disable vsync
	glfwSwapInterval(1); // cap framerate to monitor framerate

	while (!glfwWindowShouldClose(_window.getWindow()))
	{
		// Mouse
		if (_inputContext.isMouseMoved())
			_inputHandler.onMouseEvent(this, InputHandler::CommandID::CMD_MOUSE_MOVE);
		if (_inputContext.isMouseScrolled())
			_inputHandler.onMouseEvent(this, InputHandler::CommandID::CMD_MOUSE_SCROLL);
		_inputHandler.updateHeldKey(this);
		
		// Frame / Delta
		float currentFrame = static_cast<float>(glfwGetTime());
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		_scene->update(_deltaTime);

		_renderer.beginFrame(vec3(0.3, 0.3, 0.3));
		_renderer.draw(_scene);
		endFrame();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(_window.getWindow());
        glfwPollEvents();
	}
}

void Application::endFrame()
{
	auto& ctx = _inputContext;
	ctx.setIsMouseMoved(false);
	ctx.setIsMouseScrolled(false);
	ctx.setMouseScrolled(vec2(0));
}

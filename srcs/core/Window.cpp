#include "Window.hpp"
#include "InputManager.hpp"

Window::Window(Application* app)
{
	// glfw: initialize and configure
    // ------------------------------
	if (!glfwInit())
    	throw GLWF_WindowError();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

    // glfw window creation
    // --------------------
    _window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubik", NULL, NULL);
    if (_window == NULL)
	{
		glfwTerminate();
		throw GLWF_WindowError();
	}

	glfwMakeContextCurrent(_window);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(_window, app);

    // glfwMakeContextCurrent(_window);
    glfwSetFramebufferSizeCallback(_window, Window::framebufferSizeCallback);
	glfwSetCursorPosCallback(_window, InputManager::mouseCallback);
    glfwSetScrollCallback(_window, InputManager::scrollCallback);
	glfwSetMouseButtonCallback(_window, InputManager::mouseButtonCallback);
	glfwSetKeyCallback(_window, InputManager::keyCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(_window);
	    _window = nullptr;
	    glfwTerminate();
		throw GLAD_Error();
	}

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_PROGRAM_POINT_SIZE);
}

Window::~Window()
{
	if (_window)
	{
		glfwDestroyWindow(_window);
		_window = nullptr;
	}
	glfwTerminate();
}

void Window::manageTitle(std::string title)
{
	glfwSetWindowTitle(_window, title.c_str());
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	(void) window;
    glViewport(0, 0, width, height);
}

void Window::closeWindow()
{
	glfwSetWindowShouldClose(_window, true);
};

void Window::enableMouse()
{
	if (!_isMouse)
	{
		_isMouse = true;
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void Window::disableMouse()
{
	if (_isMouse)
	{
		_isMouse = false;
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}
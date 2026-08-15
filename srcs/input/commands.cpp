#include "commands.hpp"

#include "Application.hpp"

// Window
void Commands::CloseWindow::execute(Application* app) const
{
    app->window().closeWindow();
};
// Moves
void Commands::U::execute(Application* app) const {app->scene()->cube().applyMove(Face::UP, 90);};
void Commands::UPrime::execute(Application* app) const {app->scene()->cube().applyMove(Face::UP, -90);};
void Commands::D::execute(Application* app) const {app->scene()->cube().applyMove(Face::DOWN, 90);};
void Commands::DPrime::execute(Application* app) const {app->scene()->cube().applyMove(Face::DOWN, -90);};
void Commands::L::execute(Application* app) const {app->scene()->cube().applyMove(Face::LEFT, 90);};
void Commands::LPrime::execute(Application* app) const {app->scene()->cube().applyMove(Face::LEFT, -90);};
void Commands::R::execute(Application* app) const {app->scene()->cube().applyMove(Face::RIGHT, 90);};
void Commands::RPrime::execute(Application* app) const {app->scene()->cube().applyMove(Face::RIGHT, -90);};
void Commands::F::execute(Application* app) const {app->scene()->cube().applyMove(Face::FRONT, 90);};
void Commands::FPrime::execute(Application* app) const {app->scene()->cube().applyMove(Face::FRONT, -90);};
void Commands::B::execute(Application* app) const {app->scene()->cube().applyMove(Face::BACK, 90);};
void Commands::BPrime::execute(Application* app) const {app->scene()->cube().applyMove(Face::BACK, -90);};

// Camera
void Commands::ResetCamera::execute(Application* app) const
{
    app->getCamera().resetPosition();
};
void Commands::CameraForward::execute(Application* app) const
{
    app->getCamera().processKeyboard(Camera::FORWARD, app->getDelta());
};
void Commands::CameraBackward::execute(Application* app) const
{
    app->getCamera().processKeyboard(Camera::BACKWARD, app->getDelta());
};
void Commands::CameraLeft::execute(Application* app) const
{
    app->getCamera().processKeyboard(Camera::LEFT, app->getDelta());
};
void Commands::CameraRight::execute(Application* app) const
{
    app->getCamera().processKeyboard(Camera::RIGHT, app->getDelta());
};

// Mouse
void Commands::MouseMove::execute(Application* app) const
{
	if (!app->window().getMouse())
	{	
		InputContext& ctx = app->inputContext();
		app->getCamera().onMouseMove(ctx.mousePos());
	}
};

void Commands::MouseScroll::execute(Application* app) const
{
	InputContext& ctx = app->inputContext();
	app->getCamera().onMouseScroll(ctx.mouseScroll());
};
void Commands::EnableMouse::execute(Application* app) const
{
	app->inputContext().setIsMouseCaptured(false);
	app->window().enableMouse();
};
void Commands::DisableMouse::execute(Application* app) const
{
	app->inputContext().setIsMouseCaptured(true);
	app->getCamera().disableMouse();
	glfwSetCursorPos(app->window().getWindow(), SCR_WIDTH / 2, SCR_HEIGHT / 2);
	app->window().disableMouse();
};
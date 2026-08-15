#include "commands.hpp"

#include "Application.hpp"
#include "cube_types.hpp"

// Window
void Commands::CloseWindow::execute(Application* app) const
{
    app->window().closeWindow();
};
// Cube
void Commands::ResetCube::execute(Application* app) const
{
	app->scene()->cube().reset();
	app->solver().cube().reset();
}
void Commands::ScrambleCube::execute(Application* app) const
{
	for (auto i = 0; i < 30; i++)
	{
		int randomNum = rand() % static_cast<int>(Move::COUNT);
		Move m = static_cast<Move>(randomNum);

		app->scene()->cube().move(m);
		app->solver().move(m);
	}
	std::cout << std::endl;
}
// Moves
void Commands::U::execute(Application* app) const {
	app->scene()->cube().U();
	app->solver().move(Move::U);
};
void Commands::UPrime::execute(Application* app) const
{
	app->scene()->cube().UPrime();
	app->solver().move(Move::UPrime);
};
void Commands::D::execute(Application* app) const 
{
	app->scene()->cube().D();
	app->solver().move(Move::D);
};
void Commands::DPrime::execute(Application* app) const 
{
	app->scene()->cube().DPrime();
	app->solver().move(Move::DPrime);
};
void Commands::L::execute(Application* app) const 
{
	app->scene()->cube().L();
	app->solver().move(Move::L);
};
void Commands::LPrime::execute(Application* app) const 
{
	app->scene()->cube().LPrime();
	app->solver().move(Move::LPrime);
};
void Commands::R::execute(Application* app) const 
{
	app->scene()->cube().R();
	app->solver().move(Move::R);
};
void Commands::RPrime::execute(Application* app) const 
{
	app->scene()->cube().RPrime();
	app->solver().move(Move::RPrime);
};
void Commands::F::execute(Application* app) const 
{
	app->scene()->cube().F();
	app->solver().move(Move::F);
};
void Commands::FPrime::execute(Application* app) const 
{
	app->scene()->cube().FPrime();
	app->solver().move(Move::FPrime);
};
void Commands::B::execute(Application* app) const 
{
	app->scene()->cube().B();
	app->solver().move(Move::B);
};
void Commands::BPrime::execute(Application* app) const 
{
	app->scene()->cube().BPrime();
	app->solver().move(Move::BPrime);
};

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
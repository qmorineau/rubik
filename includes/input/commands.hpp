#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <cstdlib>

#include "ICommand.hpp"
#include "Application.hpp"

namespace Commands
{
    // Window
    class CloseWindow : public ICommand {void execute(Application* app) const override;};
	// Cube
	class ResetCube : public ICommand {void execute(Application* app) const override;};
	class SolveCube : public ICommand {void execute(Application* app) const override;};
	class ScrambleCube : public ICommand {void execute(Application* app) const override;};
	// Move
	class U : public ICommand {void execute(Application* app) const override;};
	class UPrime : public ICommand {void execute(Application* app) const override;};
	class D : public ICommand {void execute(Application* app) const override;};
	class DPrime : public ICommand {void execute(Application* app) const override;};
	class L : public ICommand {void execute(Application* app) const override;};
	class LPrime : public ICommand {void execute(Application* app) const override;};
	class R : public ICommand {void execute(Application* app) const override;};
	class RPrime : public ICommand {void execute(Application* app) const override;};
	class F : public ICommand {void execute(Application* app) const override;};
	class FPrime : public ICommand {void execute(Application* app) const override;};
	class B : public ICommand {void execute(Application* app) const override;};
	class BPrime : public ICommand {void execute(Application* app) const override;};
    // Camera
    class ResetCamera : public ICommand {void execute(Application* app) const override;};
    class ChangeCameraMode : public ICommand {void execute(Application* app) const override;};
    class CameraForward : public ICommand {void execute(Application* app) const override;};
    class CameraBackward : public ICommand {void execute(Application* app) const override;};
    class CameraLeft : public ICommand {void execute(Application* app) const override;};
    class CameraRight : public ICommand {void execute(Application* app) const override;};
    // Mouse
    class MouseScroll : public ICommand {void execute(Application* app) const override;};
    class MouseMove : public ICommand {void execute(Application* app) const override;};
    class EnableMouse : public ICommand {void execute(Application* app) const override;};
    class DisableMouse : public ICommand {void execute(Application* app) const override;};
};

#endif
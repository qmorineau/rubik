#ifndef SCENE_HPP
#define SCENE_HPP

#include "Types.hpp"
#include "Camera.hpp"
#include "RubikCube.hpp"

class Scene
{
	public:
		Scene();
		~Scene();

		void update(float deltaTime);

		// getter
		Camera&			camera() {return _camera;};
		RubikCube&		cube() {return _cube;};
		// setter
	private:
		Camera			_camera;
		RubikCube		_cube;
};

#endif
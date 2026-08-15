#include "RubikCube.hpp"

RubikCube::RubikCube() : _meshGPU(_mesh)
{
	_globalRot = mat4::rotateX(math::radians(-30)).mul_mat(mat4::rotateY(math::radians(30)));
	// pieces: Left->Right; row: Back->Front;
	const vec3 translate[] = {
		// Upper
		{-1, 1, -1}, {0, 1, -1}, {1, 1, -1},
		{-1, 1, 0}, {0, 1, 0}, {1, 1, 0},
		{-1, 1, 1}, {0, 1, 1}, {1, 1, 1},
		// Middle
		{-1, 0, -1}, {0, 0, -1}, {1, 0, -1},
		{-1, 0, 0}, {0, 0, 0}, {1, 0, 0},
		{-1, 0, 1}, {0, 0, 1}, {1, 0, 1},
		// Down
		{-1, -1, -1}, {0, -1, -1}, {1, -1, -1},
		{-1, -1, 0}, {0, -1, 0}, {1, -1, 0},
		{-1, -1, 1}, {0, -1, 1}, {1, -1, 1},
	};

	for (int i = 0; i < 27; i++)
	{
		_cubelets[i].translate_pos = translate[i];
		_cubelets[i].translate = mat4::translate(translate[i]);
	}

	_moves.emplace("U", &RubikCube::U);
	_moves.emplace("U'", &RubikCube::UPrime);
	_moves.emplace("U2", &RubikCube::U2);
	_moves.emplace("D", &RubikCube::D);
	_moves.emplace("D'", &RubikCube::DPrime);
	_moves.emplace("D2", &RubikCube::D2);
	_moves.emplace("F", &RubikCube::F);
	_moves.emplace("F'", &RubikCube::FPrime);
	_moves.emplace("F2", &RubikCube::F2);
	_moves.emplace("B", &RubikCube::B);
	_moves.emplace("B'", &RubikCube::BPrime);
	_moves.emplace("B2", &RubikCube::B2);
	_moves.emplace("L", &RubikCube::L);
	_moves.emplace("L'", &RubikCube::LPrime);
	_moves.emplace("L2", &RubikCube::L2);
	_moves.emplace("R", &RubikCube::R);
	_moves.emplace("R'", &RubikCube::RPrime);
	_moves.emplace("R2", &RubikCube::R2);
}

RubikCube::~RubikCube()	= default;

std::array<int, 4> RubikCube::getLayerIndices(Face f, bool is_edge) const
{
	const std::array<int, 4> up[2] = {{0, 2, 8, 6}, {1, 5, 7, 3}};
	const std::array<int, 4> down[2] = {{24, 26, 20, 18}, {21, 25, 23, 19}};
	const std::array<int, 4> left[2] = {{0, 6, 24, 18}, {3, 15, 21, 9}};
	const std::array<int, 4> right[2] = {{8, 2, 20, 26}, {5, 11, 23, 17}};
	const std::array<int, 4> front[2] = {{6, 8, 26, 24}, {7, 17, 25, 15}};
	const std::array<int, 4> back[2] = {{2, 0, 18, 20}, {1, 9, 19, 11}};

	switch (f)
	{
		case Face::UP:
			return (up[is_edge]);
		case Face::DOWN:
			return (down[is_edge]);
		case Face::LEFT:
			return (left[is_edge]);
		case Face::RIGHT:
			return (right[is_edge]);
		case Face::FRONT:
			return (front[is_edge]);
		case Face::BACK:
			return (back[is_edge]);
		default:
			return (up[is_edge]);
	}
}

int RubikCube::getCenterIdx(Face f) const
{
	switch (f)
	{
		case Face::UP:
			return (4);
		case Face::DOWN:
			return (22);
		case Face::LEFT:
			return (12);
		case Face::RIGHT:
			return (14);
		case Face::FRONT:
			return (16);
		case Face::BACK:
			return (10);
		default:
			return (13);
	}
}

void RubikCube::move(std::string move)
{
	auto it = _moves.find(move);
    if (it == _moves.end())
        throw std::runtime_error("Unknown Move: " + move);

    (this->*(it->second))();
}

void RubikCube::applyMove(Face f, int angle)
{
	if (_animating)
	{
		_queue.push(std::pair<Face, int>(f, angle));
		return;
	}

	_animEdges = getLayerIndices(f, true);
	_animCorners = getLayerIndices(f, false);
	_animCenter = getCenterIdx(f);

	for (int i = 0; i < 4; i++)
	{
		_startEdgeOrient[i] = _cubelets[_animEdges[i]].orient;
		_startCornerOrient[i] = _cubelets[_animCorners[i]].orient;
	}

	_animFace = f;
	_animAngle = angle;
	_animProgress = 0.f;
	_animating = true;
}

mat4 RubikCube::computeRot(Face f, float angle) const
{
	float radians = math::radians(angle);
	switch (f)
	{
		case Face::UP:
			return (mat4::rotateY(radians));
		case Face::DOWN:
			return (mat4::rotateY(-radians));
		case Face::LEFT:
			return (mat4::rotateX(-radians));
		case Face::RIGHT:
			return (mat4::rotateX(radians));
		case Face::FRONT:
			return (mat4::rotateZ(radians));
		case Face::BACK:
			return (mat4::rotateZ(-radians));
		default:
			return mat4::identity();
	}
}

void RubikCube::update(float delta)
{
	if (!_animating)
		return;

	_animProgress += delta / _animDuration;
	if (_animProgress > 1.f)
		_animProgress = 1.f;

	if (_animProgress >= 1.f)
	{
		mat4 rot = computeRot(_animFace, _animAngle);

		for (int i = 0; i < 4; i++)
		{
			_cubelets[_animEdges[i]].orient = rot.mul_mat(_startEdgeOrient[i]);
			_cubelets[_animCorners[i]].orient = rot.mul_mat(_startCornerOrient[i]);
		}

		if (_animAngle < 0)
		{
			for (int i = 0; i < 3; i++)
			{
				std::swap(_cubelets[_animEdges[i]].orient, _cubelets[_animEdges[i + 1]].orient);
				std::swap(_cubelets[_animCorners[i]].orient, _cubelets[_animCorners[i + 1]].orient);
			}
		}
		else
		{
			for (int i = 3; i > 0; i--)
			{
				std::swap(_cubelets[_animEdges[i]].orient, _cubelets[_animEdges[i - 1]].orient);
				std::swap(_cubelets[_animCorners[i]].orient, _cubelets[_animCorners[i - 1]].orient);
			}
		}

		_animating = false;
		if (_queue.size())
		{
			applyMove(_queue.front().first, _queue.front().second);
			_queue.pop();
		}
    }
}

mat4 RubikCube::getModelMatrix(int index) const
{
	bool isAnimated = false;

	for (int i = 0; i < 4; ++i)
	{
		if (_animEdges[i] == index || _animCorners[i] == index || _animCenter == index)
		{
			isAnimated = true;
			break;
		}
	}

	if (!_animating || !isAnimated)
		return _globalRot.mul_mat(_cubelets[index].translate).mul_mat(_cubelets[index].orient);

	mat4 rot = computeRot(_animFace, _animAngle * _animProgress);
	mat4 cubelet = rot.mul_mat(_cubelets[index].translate).mul_mat(_cubelets[index].orient);

    return _globalRot.mul_mat(cubelet);
}

void RubikCube::U() {applyMove(Face::UP, 90);}
void RubikCube::UPrime() {applyMove(Face::UP, -90);}
void RubikCube::U2() {applyMove(Face::UP, 180);}
void RubikCube::D() {applyMove(Face::DOWN, 90);}
void RubikCube::DPrime() {applyMove(Face::DOWN, -90);}
void RubikCube::D2() {applyMove(Face::DOWN, 180);}
void RubikCube::L() {applyMove(Face::LEFT, 90);}
void RubikCube::LPrime() {applyMove(Face::LEFT, -90);}
void RubikCube::L2() {applyMove(Face::LEFT, 180);}
void RubikCube::R() {applyMove(Face::RIGHT, 90);}
void RubikCube::RPrime() {applyMove(Face::RIGHT, -90);}
void RubikCube::R2() {applyMove(Face::RIGHT, 180);}
void RubikCube::F() {applyMove(Face::FRONT, 90);}
void RubikCube::FPrime() {applyMove(Face::FRONT, -90);}
void RubikCube::F2() {applyMove(Face::FRONT, 180);}
void RubikCube::B() {applyMove(Face::BACK, 90);}
void RubikCube::BPrime() {applyMove(Face::BACK, -90);}
void RubikCube::B2() {applyMove(Face::BACK, 180);}
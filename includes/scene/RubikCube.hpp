#ifndef RUBIKCUBE_HPP
#define RUBIKCUBE_HPP

#include <vector>
#include <queue>
#include <array>
#include <unordered_map>

#include "Types.hpp"
#include "Matrix4.hpp"

#include "CubeMeshGPU.hpp"

enum class Face
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

class RubikCube
{
	public:
		struct Cubelet
		{
			mat4		orient = mat4::identity();
			mat4		translate = mat4::identity();
			vec3		translate_pos;
		};
		RubikCube();
		~RubikCube();

		void	update(float delta);
		void	draw();
		void	move(std::string move);
		void	applyMove(Face f, int rot);

		// getter
		const CubeMeshGPU	mesh() {return _mesh;};

		mat4 getModelMatrix(int index) const;

		const std::array<Cubelet,27>& cubelets() const {return _cubelets;}
	private:
		mat4					_globalRot;
		std::array<Cubelet, 27>	_cubelets;
		CubeMesh				_mesh;
		CubeMeshGPU				_meshGPU;
		bool					_animating = 0;
		float					_animProgress = 0.f;
		float					_animDuration = 0.1f;
		Face					_animFace;
		int						_animAngle;
		std::array<int, 4>		_animEdges;
		std::array<int, 4>		_animCorners;
		int						_animCenter;
		std::array<mat4, 4>		_startEdgeOrient;
		std::array<mat4, 4>		_startCornerOrient;
		
		std::unordered_map<std::string, void (RubikCube::*)()>	_moves;
		std::queue<std::pair<Face, int>>						_queue;

		std::array<int, 4>	getLayerIndices(Face f, bool is_edge) const;
		int					getCenterIdx(Face f) const;
		mat4				computeRot(Face f, float angle) const;

		void U();
		void UPrime();
		void U2();
		void L();
		void LPrime();
		void L2();
		void R();
		void RPrime();
		void R2();
		void B();
		void BPrime();
		void B2();
		void D();
		void DPrime();
		void D2();
		void F();
		void FPrime();
		void F2();
};

#endif
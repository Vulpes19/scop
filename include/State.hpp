#pragma once

#include "Matrix.hpp"
#include "Shader.hpp"

enum STATES {
	NoState,
	MainMenuState,
	ListObjectsState,
	SceneState
};

class State
{
	public:
		virtual ~State() {};
		virtual void	handleInput(void) = 0;
		virtual void	update(float = 0) = 0;
		virtual void	render(Vulpes3D::Matrix4x4 = Vulpes3D::Matrix4x4()) = 0;
		enum STATES		getStateName(void) const { return (stateName); }
	protected:
		// UILabel		label;
        Shader  *shader;
		enum STATES stateName = NoState;
        Vulpes3D::Matrix4x4   model;;
        Vulpes3D::Matrix4x4   projection;
};
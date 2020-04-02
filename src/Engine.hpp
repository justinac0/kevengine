#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "render/BufferUtil.hpp"
#include "render/Window.hpp"
#include "render/Shader.hpp"
#include "render/Mesh.hpp"
#include "scene/Camera.hpp"
#include "scene/Model.hpp"

#include "prototyping.hpp"

#include <thread>

class Engine {
private:

public:
	Window window;

	Engine();
	~Engine();

	void update();
};

#endif // ENGINE_HPP_

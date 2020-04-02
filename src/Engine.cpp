#include "Engine.hpp"

Scene scene;
Shader shader;
Camera camera;
Model model;
glm::vec3 lightPosition;

Engine::Engine() {
	// if we are going to create a seperate render thread,
	// GLFWwindow must be in the same thread as the rendering.
	this->window.create(800, 600, "kevengine");
	model.load("./bin/models/cube.obj");
	model.setScale(10, 10, 10);
    shader.load("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");

	lightPosition = glm::vec3(0, 100, 0);

	camera.init(0.5f, 4.0f);
}

Engine::~Engine() {

}

void Engine::update() {
	while (!glfwWindowShouldClose(this->window.getHandle())) {
		glfwPollEvents();
		glfwSwapBuffers(this->window.getHandle());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.update(this->window.getHandle());

		shader.use();
		shader.sendUniformVec3("lightPosition", lightPosition);
		shader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
		shader.sendUniformMat4("view", camera.getViewMatrix());
		shader.sendUniformMat4("model", model.getMatrix());
		model.render();
	}
}

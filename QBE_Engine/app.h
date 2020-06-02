//Code from https://vulkan-tutorial.com/
#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <optional>
#include <set>
#include <fstream>
#include <thread>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include "renderer.h"
#include "map.h"
typedef std::chrono::high_resolution_clock Clock;

enum DrawStatus{SUSPEND, RESUME, RELOAD, ACTIVE};

class App
{
public:

	App();
	void run();
	void mainLoop();
	void rendererLoop();
	void processInput(int deltaTime);
	void processWindowEvent(SDL_Event event);
	
private:

	Renderer renderer;
	DrawStatus drawStatus = ACTIVE;
	bool appIsRunning = true;
	bool drawLoopActive = true;
	bool windowIsMinimized = false;

	int max_fps;
	bool KEYS[322];
	bool relative_mode_enabled;
	float movement_acceleration;
	float max_movement_speed;
	float movement_speed_forward;
	float movement_speed_right;
	float mouse_speed;
	float mouseDeltaX;
	float mouseDeltaY;
	float horizontal_camera_angle;
	float vertical_camera_angle;

	WorldRenderInfo renderInfo;

	glm::vec3 camera_position;
	glm::vec3 camera_direction_up;
	glm::vec3 camera_target;
};


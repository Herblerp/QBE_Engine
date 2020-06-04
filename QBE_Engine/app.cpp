#include "app.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

App::App(Map& map) : map(map)
{
}

void App::run()
{
	//Initialize keys array
	for (int i = 0; i < 322; i++) {
		KEYS[i] = false;
	}

	//Initialize input and movement parameters
	camera_position = glm::vec3(-2.0f, 0.0f, 2.0f);
	max_movement_speed = 0.008f;
	movement_acceleration = 0.00002f;
	movement_speed_forward = 0.0f;
	movement_speed_right = 0.0f;
	mouse_speed = 0.8f;
	mouseDeltaX = 0;
	mouseDeltaY = 0;
	horizontal_camera_angle = 0.0f;
	vertical_camera_angle = -45.0f;
	max_fps = 60;

	//Initialize renderInfo
	renderCameraInfo.camera_fov = 45.0f;
	renderCameraInfo.camera_position = glm::vec3(-2.0f, 0.0f, 2.0f);
	renderTerrainInfo.terrain_position = glm::vec3(0.0f, 0.0f, 0.0f);
	renderTerrainInfo.terrain_rotation_angle = 0.0f;
	renderTerrainInfo.terrain_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	renderTerrainInfo.terrain_rotation_direction = glm::vec3(1.0f, 1.0f, 1.0f);

	map.loadMapData();

	renderVertexInfo.vertices = map.getMapVertexData();
	renderVertexInfo.indices = map.getMapIndexData();

	renderer.setRenderCameraInfo(renderCameraInfo);
	renderer.setRenderTerrainInfo(renderTerrainInfo);
	renderer.setRenderVertexInfo(renderVertexInfo);

	renderer.initialize();
	mainLoop();
	renderer.cleanup();
}

void App::mainLoop()
{
	relative_mode_enabled = false;

	//Start drawing
	drawLoopActive = true;
	mapLoopActive = true;
	std::thread rendererThread;
	std::thread mapThread;
	rendererThread = std::thread([this] { this->rendererLoop(); });
	mapThread = std::thread([this] { this->mapLoop(); });

	while (appIsRunning) {

			SDL_Event event;
			while (SDL_PollEvent(&event)) {

				switch (event.type) {

				case SDL_QUIT:

					appIsRunning = false;
					mapLoopActive = false;
					break;

				case SDL_WINDOWEVENT:
					processWindowEvent(event);
					break;

				case SDL_KEYDOWN:
					KEYS[event.key.keysym.sym] = true;
					break;

				case SDL_KEYUP:
					KEYS[event.key.keysym.sym] = false;
					break;

				case SDL_MOUSEMOTION:
					if (relative_mode_enabled) {

						//Use actual coordinates
						mouseDeltaX = static_cast<float>(event.motion.xrel / 100.0f);
						mouseDeltaY = static_cast<float>(event.motion.yrel / 100.0f);
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (!relative_mode_enabled) {
						int i = SDL_SetRelativeMouseMode(SDL_TRUE);
						std::cout << i;
						relative_mode_enabled = true;
					}
					else {
						//do something
					}
					break;
				default:
					break;
				}
			}

			switch (drawStatus)
			{
			case RESUME:

				renderer.recreateSwapChain();
				drawLoopActive = true;
				rendererThread = std::thread([this] { this->rendererLoop(); });
				drawStatus = ACTIVE;
				break;

			case RELOAD:

				drawLoopActive = false;

				if (rendererThread.joinable()) {
					rendererThread.join();
				}

				renderer.recreateSwapChain();
				drawLoopActive = true;
				rendererThread = std::thread([this] { this->rendererLoop(); });
				drawStatus = ACTIVE;

				break;

			case SUSPEND:

				drawLoopActive = false;

				if (rendererThread.joinable()) {
					rendererThread.join();
				}

				break;

			case ACTIVE:
				break;

			default:
				break;
			}
			SDL_Delay(10);
			mouseDeltaX = 0;
			mouseDeltaY = 0;
		}	
	rendererThread.join();
	mapThread.join();
}

void App::rendererLoop()
{
	//renderer.setRenderInfo(renderInfo);

	int input_timer_1 = 0;
	int input_timer_2 = 0;

	while (drawLoopActive && appIsRunning) {

		input_timer_1 = SDL_GetTicks();
		int deltaTime = input_timer_1 - input_timer_2;
		input_timer_2 = SDL_GetTicks();

		processInput(deltaTime);

		renderCameraInfo.camera_direction_up = camera_direction_up;
		renderCameraInfo.camera_position = camera_position;
		renderCameraInfo.camera_target = camera_target;

		Pos newCameraPosition{
			static_cast<uint32_t>(camera_position.x),
			static_cast<uint32_t>(camera_position.y),
			static_cast<uint32_t>(camera_position.z) };
		if (mapHasBeenUpdated){
			renderer.recreateVertexBuffers();
			mapHasBeenUpdated = false;
		}
		renderer.setRenderCameraInfo(renderCameraInfo);

		if (renderer.drawFrame() != 0) {
			drawLoopActive = false;
		}
	}
	renderer.waitIdle();
}

void App::mapLoop() {

	while (mapLoopActive) {
		Pos newCameraPosition{
				static_cast<uint32_t>(camera_position.x),
				static_cast<uint32_t>(camera_position.y),
				static_cast<uint32_t>(camera_position.z) };
		if (!mapHasBeenUpdated && map.updateMapData(newCameraPosition)) {
			renderVertexInfo.vertices = map.getMapVertexData();
			renderVertexInfo.indices = map.getMapIndexData();
			renderer.setRenderVertexInfo(renderVertexInfo);
			mapHasBeenUpdated = true;
		}
		std::chrono::milliseconds map_refresh_idle_dureation(100);
		std::this_thread::sleep_for(map_refresh_idle_dureation);
	}
}

void::App::processInput(int deltaTime) {

	//Calculate camera angle based upon mouse movement. Set back to 0 or the mouse will keep moving.
	horizontal_camera_angle += -mouseDeltaX * deltaTime * mouse_speed;
	vertical_camera_angle += -mouseDeltaY * deltaTime * mouse_speed;

	//Make sure the angles stay between 0 and 360
	if (horizontal_camera_angle < 0) {
		horizontal_camera_angle = 360 + horizontal_camera_angle;
	}
	else if (horizontal_camera_angle > 360) {
		horizontal_camera_angle = horizontal_camera_angle - 360;
	}

	if (vertical_camera_angle < 0) {
		vertical_camera_angle = 360 + vertical_camera_angle;
	}
	else if (vertical_camera_angle > 360) {
		vertical_camera_angle = vertical_camera_angle - 360;
	}

	//Set the direction sign based on the angle, or the cross product and camera will flip over.
	glm::vec3 world_direction_up;
	if (vertical_camera_angle < 90 || vertical_camera_angle > 270) {
		world_direction_up = glm::vec3(0.0f, 0.0f, -1.0f);
	}
	else if (vertical_camera_angle >= 90 && vertical_camera_angle <= 270) {
		world_direction_up = glm::vec3(0.0f, 0.0f, 1.0f);
	}

	//Calculate the camera directions
	glm::vec3 camera_direction(
		cos(glm::radians(vertical_camera_angle)) * cos(glm::radians(horizontal_camera_angle)),
		cos(glm::radians(vertical_camera_angle)) * sin(glm::radians(horizontal_camera_angle)),
		sin(glm::radians(vertical_camera_angle))
	);
	glm::vec3 camera_direction_right(glm::normalize(glm::cross(world_direction_up, camera_direction)));
	//Calculate the final vectors needed for ubo updates based upon input.
	camera_direction_up = glm::normalize(glm::cross(camera_direction_right, camera_direction));

	bool forward_idle = true;
	bool right_idle = true;

	if (KEYS[SDLK_z]) {
		movement_speed_forward += movement_acceleration * deltaTime;
		if (movement_speed_forward > max_movement_speed) {
			movement_speed_forward = max_movement_speed;
		}
		forward_idle = false;
	}
	if (KEYS[SDLK_s]) {
		movement_speed_forward -= movement_acceleration * deltaTime;
		if (movement_speed_forward < -max_movement_speed) {
			movement_speed_forward = -max_movement_speed;
		}
		forward_idle = false;
	}
	if (KEYS[SDLK_q]) {
		movement_speed_right -= movement_acceleration * deltaTime;
		if (movement_speed_right < -max_movement_speed) {
			movement_speed_right = -max_movement_speed;
		}
		right_idle = false;
	}
	if (KEYS[SDLK_d]) {
		movement_speed_right += movement_acceleration * deltaTime;
		if (movement_speed_right > max_movement_speed) {
			movement_speed_right = max_movement_speed;
		}
		right_idle = false;
	}

	if (forward_idle) {

		if (movement_speed_forward > 0.0001f) {
			movement_speed_forward -= movement_acceleration * deltaTime;
		}
		else if (movement_speed_forward < -0.0001f) {
			movement_speed_forward += movement_acceleration * deltaTime;
		}
		else {
			movement_speed_forward = 0.0f;
		}
	}

	if (right_idle) {

		if (movement_speed_right > 0.0001f) {
			movement_speed_right -= movement_acceleration * deltaTime;
		}
		else if (movement_speed_right < -0.0001f) {
			movement_speed_right += movement_acceleration * deltaTime;
		}
		else {
			movement_speed_right = 0.0f;
		}
	}

	if (KEYS[SDLK_ESCAPE]) {
		SDL_SetRelativeMouseMode(SDL_FALSE);
		relative_mode_enabled = false;
	}

	camera_position += ((movement_speed_forward * camera_direction) + (movement_speed_right * camera_direction_right)) * static_cast<float>(deltaTime);
	camera_target = camera_position + camera_direction;
}

void::App::processWindowEvent(SDL_Event event) {
	switch (event.window.event) {

	case SDL_WINDOWEVENT_RESTORED:
		if (drawStatus != SUSPEND) {
			drawStatus = RELOAD;
		}
		else {
			drawStatus = RESUME;
		}
		break;

	case SDL_WINDOWEVENT_MAXIMIZED:
		drawStatus = RELOAD;
		break;

	case SDL_WINDOWEVENT_MINIMIZED:
		drawStatus = SUSPEND;
		break;

	case SDL_WINDOWEVENT_RESIZED:
		drawStatus = RELOAD;
		break;

	default:
		break;
	}
}
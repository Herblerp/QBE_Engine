/*
 * Vulkan Windowed Program
 *
 * Copyright (C) 2016, 2018 Valve Corporation
 * Copyright (C) 2016, 2018 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 /*
 Vulkan C++ Windowed Project Template
 Create and destroy a Vulkan surface on an SDL window.
 */

 // Enable the WSI extensions
#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(__linux__)
#define VK_USE_PLATFORM_XLIB_KHR
#elif defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

// Tell SDL not to mess with main()
#define SDL_MAIN_HANDLED

#include "app.h"
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include <iostream>
#include <vector>
#include "../QBE_Engine_Data/regionFile.h"

using namespace std;
using namespace Data;

typedef chrono::high_resolution_clock Clock;

int main()
{
	cout << "[INFO] Starting app clock. \n";
	auto t1 = Clock::now();

	MapInfo mapInfo;
	mapInfo.chunkDim = 16;
	mapInfo.mapDim = 8;
	mapInfo.regionDim = 10;

	Pos cameraPos = { 0,0,0 };
	mapInfo.cameraPos = cameraPos;

	Map map("testmap");
	map.createMap(mapInfo);
	map.loadMap();

	App app(map);
	app.run();

	map.deleteMap();

	cout << "[INFO] Stopping app clock." << std::endl;
	auto t2 = Clock::now();
	cout << "[INFO] App ran for '" << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "' milliseconds.\n";
	system("pause");
}

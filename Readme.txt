To be able to compile the project the vulkan SDK must be installed and the device must have a compatible GPU to run the application. 
The vulkan SDL can be downloaded from https://www.lunarg.com/vulkan-sdk/
The glm files must be present inside the vulkan SDK folder VulkanSDK\1.1.x.x\Third-Party\Include. These can be downloaded from https://glm.g-truc.net/0.9.9/index.html

I can not guarantee the project will compile on other devices without any additional configuration.

This is a prototype, it has not yet been developped for widespread support.
This application is tested on a windows 64 system, any other platform will probably not work.

When the app launches a new map is created and generated. This map is saved in the maps folder, which will be present in the cuurent directory of the application,
which depends on the type of build (release/debug).

Unloaded chunks will be written to this folder inside their region files, you will see these appear as you fly around. 
The console also mentions the amout of bytes a chunk has been compressed to.

To move around the ZQSD keys can be used. You can move up using the space key. To un-focus the mouse, press the ESC key.

When closing the app the curently created map will be deltetd.
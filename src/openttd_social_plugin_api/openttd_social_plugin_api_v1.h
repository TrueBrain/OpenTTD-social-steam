/*
 * Copyright 2023 OpenTTD project
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/* Although all the source-files created by OpenTTD are licensed under the
 * GPL-v2, this file is an exception. This file is part of the API for
 * social presence plugins, and licensed under MIT, to allow for non-free
 * implementations.
 */

/** @file v1.h Version 1 definition of the OpenTTD Social Presence Plugin API. */

#ifndef OPENTTD_SOCIAL_PLUGIN_API_V1_H
#define OPENTTD_SOCIAL_PLUGIN_API_V1_H

#ifdef __cplusplus
extern "C" {
#endif

/** Pointers supplied by the plugin for OpenTTD to use. */
struct OpenTTD_SocialPlugin_v1_PluginApi {
	const char *name; ///< Full name of the plugin. The plugin is and remains the owner of the memory.
	const char *version; ///< Version of the plugin. The plugin is and remains the owner of the memory.

	/**
	 * OpenTTD tells the plugin to shut down.
	 *
	 * The plugin should free any resources it allocated, and must not call any of the callback functions after this call.
	 */
	void (*shutdown)();

	/**
	 * OpenTTD calls this function at regular intervals, to handle any callbacks the plugin might have.
	 *
	 * It is also safe to call the OpenTTD_SocialPluginCallbacks functions here.
	 *
	 * @return True if the plugin wants to be called again, false if the plugin wants to be unloaded.
	 */
	bool (*run_callbacks)();

	/**
	 * The player has entered the main menu.
	 */
	void (*event_enter_main_menu)();

	/**
	 * The player has entered the Scenario Editor.
	 *
	 * @param map_width The width of the map in tiles.
	 * @param map_height The height of the map in tiles.
	 */
	void (*event_enter_scenario_editor)(unsigned int map_width, unsigned int map_height);

	/**
	 * The player has entered a singleplayer game.
	 *
	 * @param map_width The width of the map in tiles.
	 * @param map_height The height of the map in tiles.
	 */
	void (*event_enter_singleplayer)(unsigned int map_width, unsigned int map_height);

	/**
	 * The player has entered a multiplayer game.
	 *
	 * @param map_width The width of the map in tiles.
	 * @param map_height The height of the map in tiles.
	 */
	void (*event_enter_multiplayer)(unsigned int map_width, unsigned int map_height);

	/**
	 * The player is joining a multiplayer game.
	 *
	 * This is followed by event_enter_multiplayer() if the join was successful.
	 */
	void (*event_joining_multiplayer)();
};

/** Pointers supplied by OpenTTD, for the plugin to use. */
struct OpenTTD_SocialPlugin_v1_OpenTTDInfo {
	const char *openttd_version; ///< Version of OpenTTD. OpenTTD is and remains the owner of the memory.
};

/** The result of the initialization. */
enum OpenTTD_SocialPlugin_v1_InitResult : int {
	OTTD_SOCIAL_PLUGIN_V1_INIT_SUCCESS = 1, ///< Plugin initialized successfully.
	OTTD_SOCIAL_PLUGIN_V1_INIT_FAILED = -1, ///< Plugin failed to initialize (generic error).
	OTTD_SOCIAL_PLUGIN_V1_INIT_PLATFORM_NOT_RUNNING = -2, ///< The Social Presence platform is not running.

	OTTD_SOCIAL_PLUGIN_V1_INIT_UNSUPPORTED_API = -98, ///< Internal state, should not be used by plugins.
	OTTD_SOCIAL_PLUGIN_V1_INIT_UNLOADED = -99, ///< Internal state, should not be used by plugins.
};

/**
 * Type of the init function the plugin is expected to export from its dynamic library.
 *
 * The plugin has to export the implementation of this function as "SocialPlugin_vN_Init", where N is the API version this entry point is for.
 * A single plugin can have multiple versions implemented.
 *
 * @note The plugin must verify the api_version passed by OpenTTD is supported before filling the api struct.
 *
 * @param[out] plugin_api    Structure the plugin must fill with pointers. Can contain nullptr if the plugin does not support a feature. The plugin is owner of the memory.
 * @param[in]  openttd_info  Structure that OpenTTD filled with pointers. All pointers will remain valid until shutdown(). OpenTTD is owner of the memory.
 * @return                   The status of the initialization.
 */
typedef OpenTTD_SocialPlugin_v1_InitResult (*OpenTTD_SocialPlugin_v1_Init)(OpenTTD_SocialPlugin_v1_PluginApi *plugin_api, const OpenTTD_SocialPlugin_v1_OpenTTDInfo *openttd_info);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OPENTTD_SOCIAL_PLUGIN_API_V1_H */
#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   define DLL_EXPORT __declspec(dllexport)
#else
#   define DLL_EXPORT
#endif /* WIN32 */

#include <chrono>
#include <time.h>
#include <string>

#include "steam/steam_api.h"
#include "openttd_social_plugin_api/openttd_social_plugin_api.h"

bool run_callbacks()
{
    SteamAPI_RunCallbacks();

    return true;
}

void shutdown()
{
    SteamFriends()->ClearRichPresence();
    SteamAPI_Shutdown();
}

void event_enter_main_menu()
{
    SteamFriends()->SetRichPresence("steam_display", "#MainMenu");
}

void event_enter_scenario_editor(unsigned int map_width, unsigned int map_height)
{
    SteamFriends()->SetRichPresence("map_width", std::to_string(map_width).c_str());
    SteamFriends()->SetRichPresence("map_height", std::to_string(map_height).c_str());

    SteamFriends()->SetRichPresence("steam_display", "#ScenarioEditor");
}

void event_enter_singleplayer(unsigned int map_width, unsigned int map_height)
{
    SteamFriends()->SetRichPresence("map_width", std::to_string(map_width).c_str());
    SteamFriends()->SetRichPresence("map_height", std::to_string(map_height).c_str());

    SteamFriends()->SetRichPresence("steam_display", "#Singleplayer");
}

void event_enter_multiplayer(unsigned int map_width, unsigned int map_height)
{
    SteamFriends()->SetRichPresence("map_width", std::to_string(map_width).c_str());
    SteamFriends()->SetRichPresence("map_height", std::to_string(map_height).c_str());

    SteamFriends()->SetRichPresence("steam_display", "#Multiplayer");
}

void event_joining_multiplayer()
{
    SteamFriends()->SetRichPresence("steam_display", "#JoiningMultiplayer");
}

extern "C" DLL_EXPORT int SocialPlugin_v1_Init(OpenTTD_SocialPlugin_v1_PluginApi *plugin_api, const OpenTTD_SocialPlugin_v1_OpenTTDInfo *)
{
    static OpenTTD_SocialPlugin_v1_PluginApi api {
        .name = "Steam Social Presence",
        .version = "v1.0.0",
        .shutdown = shutdown,
        .run_callbacks = run_callbacks,

        .event_enter_main_menu = event_enter_main_menu,
        .event_enter_scenario_editor = event_enter_scenario_editor,
        .event_enter_singleplayer = event_enter_singleplayer,
        .event_enter_multiplayer = event_enter_multiplayer,
        .event_joining_multiplayer = event_joining_multiplayer,
    };

    *plugin_api = api;

    if (!SteamAPI_IsSteamRunning()) {
        return OTTD_SOCIAL_PLUGIN_V1_INIT_PLATFORM_NOT_RUNNING;
    }

    if (!SteamAPI_Init()) {
        return OTTD_SOCIAL_PLUGIN_V1_INIT_FAILED;
    }

    return OTTD_SOCIAL_PLUGIN_V1_INIT_SUCCESS;
}

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    /* Ensure our library remains loaded. */
    return TRUE;
}
#endif /* WIN32 */

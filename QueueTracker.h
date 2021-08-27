#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include <string>
#include <ctime>
#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class QueueTracker: public BakkesMod::Plugin::BakkesModPlugin
{
private:

	void EndTimer();
	void StartTimer(bool bValue);
	std::string GetPlaylistName(int playlistId);
	time_t time_queue_start{time_t(NULL)};
	long int time_queue_difference{0};
	bool timer_already_started{ false };
	bool should_be_announced{ false };
public:
	virtual void onLoad();
	void HookEvents();
	void UnHookEvents();
	virtual void onUnload();
	

};


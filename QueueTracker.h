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

	void EndTimer(ServerWrapper caller, void* params, std::string eventName);
	void StartTimer(ServerWrapper caller, void* params, std::string eventName);
	std::string GetPlaylistName(int playlistId);
	time_t queueStart_time;
	long int queueElapsed_time;
	bool needToAnnounce;
	bool isCancelled;
	bool isSearching;
	std::string queueElapsed_str;
public:
	virtual void onLoad();
	virtual void onUnload();


};


#pragma once
#pragma comment( lib, "pluginsdk.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"

#include <string>
#include <ctime>




class QueueTracker : public BakkesMod::Plugin::BakkesModPlugin
{
private:

	void EndTimer(ServerWrapper caller, void* params, std::string eventName);
	void StartTimer(ServerWrapper caller, void* params, std::string eventName);
	std::string GetPlaylistName(int playlistId);
public:
	virtual void onLoad();
	virtual void onUnload();
	time_t queueStart_time, queueElapsed_time;
	std::string queueElapsed_str;
};
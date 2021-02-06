#pragma once
#pragma comment( lib, "pluginsdk.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod\wrappers\includes.h"
#include "utils/parser.h"
#include <string>
#include <ctime>




class QueueTracker : public BakkesMod::Plugin::BakkesModPlugin
{
private:

public:
	virtual void onLoad();
	virtual void onUnload();

	time_t queueStart_time, queueEnd_time, queueElapsed_time;
	std::string queueElapsed_str;
	void EndTimer(ServerWrapper caller, void* params, std::string eventName);
	void StartTimer(ServerWrapper caller, void* params, std::string eventName);
	void EndTimerGameComplete(ServerWrapper caller, void* params, std::string eventName);
	void EndTimerPostBeginPlay(ServerWrapper caller, void* params, std::string eventName);

};

std::string GetPlaylistName(int playlistId);

//std::shared_ptr<bool> showNotifications = std::make_shared<bool>(true);
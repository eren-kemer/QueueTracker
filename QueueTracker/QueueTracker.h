#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod\wrappers\GameEvent\TutorialWrapper.h"
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
	void EndTimer(ServerWrapper caller, void* params, std::string eventName);

};

//std::shared_ptr<bool> showNotifications = std::make_shared<bool>(true);
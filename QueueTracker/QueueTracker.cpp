#include "QueueTracker.h"


static const std::string savefile = "bakkesmod/data/queuetimetracker.data";

BAKKESMOD_PLUGIN(QueueTracker, "Queue time tracker", "0.1", PLUGINTYPE_FREEPLAY)


bool needToAnnounceTime = false;

void Log(void* object, std::string message)
{
	auto plugin = (QueueTracker*)object;
	plugin->cvarManager->log(message);
}


void QueueTracker::onLoad()
{
	time_t current_time, matchfound_time;
	current_time, matchfound_time = time(NULL);
	cvarManager->log("QueueTracker loaded");
	gameWrapper->Toast("QueueTracker", "QueueTracker loaded successfully!");
	//gameWrapper->Toast("Queuetracker", message, logo_to_use, 3.5f, toastType);

	// Register for Game starting event
	/*
	gameWrapper->HookEventWithCaller<ServerWrapper>(
		"Function GameEvent_Soccar_TA.Active.StartRound",
		bind(
			&QueueTracker::EndTimer,
			this,
			placeholders::_1,
			placeholders::_2,
			placeholders::_3
		)
		);
	*/


}

void QueueTracker::onUnload()
{
	cvarManager->log("QueueTracker unloaded");
	gameWrapper->Toast("QueueTracker", "QueueTracker unloaded successfully!");
}



void QueueTracker::EndTimer(ServerWrapper caller, void* params, std::string eventName) {
	if (gameWrapper->IsInOnlineGame()) {
		needToAnnounceTime = true;
	}
	else {
		//If we are not in online game, we are in freeplay, custom training etc
		// We will set the needToAnnounceTime flag to false and no need to announce queue time
		needToAnnounceTime = false;
		return;
	}


}
#include "pch.h"
#include "QueueTracker.h"

//static const std::string savefile = "bakkesmod/data/queuetimetracker.data"; // For possible later use
BAKKESMOD_PLUGIN(QueueTracker, "Queue time tracker", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void QueueTracker::onLoad()
{
	_globalCvarManager = cvarManager;

	//First we check if the QueueTracker is currently enabled or not. If it's enabled, we should hook the events.
	auto queuetracker_is_enabled = cvarManager->registerCvar("queuetracker_is_enabled", "1", "Enable QueueTracker", true, true, 0, true, 1);
	if (queuetracker_is_enabled.getBoolValue()) {
		HookEvents();
	}

	//Here we check the setting value after it was changed, so we can (un)hook accordingly.
	queuetracker_is_enabled.addOnValueChanged([this](std::string, CVarWrapper cvar) {
		if (cvar.getBoolValue()) {
			HookEvents();
		}
		else {
			UnHookEvents();
		}
		});
	

	time_queue_start, time_queue_difference = time(NULL);
}

void QueueTracker::HookEvents() {
	struct Params {
		unsigned long bValue;
	};

	gameWrapper->HookEventWithCallerPost<ActorWrapper>("Function ProjectX.PartyMessage_SearchStatus_X.SetIsSearching",
		[this](auto caller, void* raw_param, ...)
		{
			Params* param_t = static_cast<Params*>(raw_param);

			bool isSearching = param_t->bValue;
			QueueTracker::StartTimer(isSearching);
		}
	);

	gameWrapper->HookEventWithCallerPost<ActorWrapper>("Function TAGame.GameEvent_TA.PostBeginPlay",
		[this](auto caller, void* raw_param, ...)
		{
			QueueTracker::EndTimer();
		}
	);
	cvarManager->log("QueueTracker events hooked!");
}

void QueueTracker::UnHookEvents() {
	gameWrapper->UnhookEvent("Function ProjectX.PartyMessage_SearchStatus_X.SetIsSearching");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_TA.PostBeginPlay");
	cvarManager->log("QueueTracker events unhooked!");
}



void QueueTracker::onUnload()
{
}

void QueueTracker::StartTimer(bool isSearching) {
	if(isSearching){
		if (!timer_already_started) {
			timer_already_started = true;
			time_queue_start = time(NULL);
			cvarManager->log("Queue time logged!");
		}
	}
	else {
		timer_already_started = false;
		cvarManager->log("Timer cancelled!");
	}
}

void QueueTracker::EndTimer() {
	auto mmrWrapper = gameWrapper->GetMMRWrapper();
	if (mmrWrapper.memory_address == NULL) return;
	auto playlist = mmrWrapper.GetCurrentPlaylist();
	auto playlistName = GetPlaylistName(playlist);

	if (playlistName != "Queueless") {
		time_queue_difference = time(NULL) - time_queue_start;

		cvarManager->log("QueueTracker: Match found in " + std::to_string(time_queue_difference) + " seconds!");
		gameWrapper->Toast("QueueTracker", "Match found in " + std::to_string(time_queue_difference) + " seconds!");
	}
}

std::string QueueTracker::GetPlaylistName(int playlistId) {
	switch (playlistId) {
	case(1):
		return "Duel";
		break;
	case(2):
		return "Doubles";
		break;
	case(3):
		return "Standard";
		break;
	case(4):
		return "Chaos";
		break;
	case(10):
		return "Duel (Ranked)";
		break;
	case(11):
		return "Doubles (Ranked)";
		break;
	case(13):
		return "Standard (Ranked)";
		break;
	case(15):
		return "Snow Day";
		break;
	case(16):
		return "Rocket Labs";
		break;
	case(17):
		return "Hoops";
		break;
	case(18):
		return "Rumble";
		break;
	case(23):
		return "Dropshot";
		break;
	case(27):
		return "Hoops (Ranked)";
		break;
	case(28):
		return "Rumble (Ranked)";
		break;
	case(29):
		return "Dropshot (Ranked)";
		break;
	case(30):
		return "Snow Day (Ranked)";
		break;
	case(31):
		return "Ghost Hunt";
		break;
	case(32):
		return "Beach Ball";
		break;
	case(33):
		return "Spike Rush";
		break;
	case(37):
		return "Dropshot Rumble";
		break;
	case(38):
		return "Heatseeker";
		break;
	case(41):
		return "Boomer Ball";
		break;
	case(43):
		return "Heatseeker Doubles";
		break;
	default:
		return "Queueless";
		break;
	}
}
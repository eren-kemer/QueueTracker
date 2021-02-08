#include "pch.h"
#include "QueueTracker.h"

//static const std::string savefile = "bakkesmod/data/queuetimetracker.data"; // For possible later use
BAKKESMOD_PLUGIN(QueueTracker, "Queue time tracker", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void QueueTracker::onLoad()
{
	_globalCvarManager = cvarManager;
	time_queue_start, time_queue_difference = time(NULL);
	should_be_announced = false;

	gameWrapper->HookEventWithCaller<ServerWrapper>(
		"Function ProjectX.CheckReservation_X.StartSearch",
		bind(
			&QueueTracker::StartTimer,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3)
		);

	gameWrapper->HookEventWithCaller<ServerWrapper>(
		"Function TAGame.GameEvent_TA.PostBeginPlay",
		bind(
			&QueueTracker::EndTimer,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3)
		);
}

void QueueTracker::onUnload()
{
}

void QueueTracker::StartTimer(ServerWrapper caller, void* params, std::string eventName) {
	time_queue_start = time(NULL);
	should_be_announced = true;
	cvarManager->log("Queue time logged!");
}

void QueueTracker::EndTimer(ServerWrapper caller, void* params, std::string eventName) {
	auto mmrWrapper = gameWrapper->GetMMRWrapper();
	if (mmrWrapper.memory_address == NULL) return;
	auto playlist = mmrWrapper.GetCurrentPlaylist();
	auto playlistName = GetPlaylistName(playlist);

	if (playlistName != "Queueless" && should_be_announced) {
		time_queue_difference = time(NULL) - time_queue_start;

		if (time_queue_difference >= 60) {
			time_queue_difference_str = std::to_string(time_queue_difference / 60) + " minute(s)!";
		}
		else {
			time_queue_difference_str = std::to_string(time_queue_difference) + " seconds!";
		}
		
		cvarManager->log("QueueTracker: Match found in " + time_queue_difference_str);
		gameWrapper->Toast("QueueTracker", "Match found in " + time_queue_difference_str);
		should_be_announced = false;
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
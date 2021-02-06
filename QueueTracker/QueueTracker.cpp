#include "QueueTracker.h"


static const std::string savefile = "bakkesmod/data/queuetimetracker.data";

BAKKESMOD_PLUGIN(QueueTracker, "Queue time tracker", "0.1", PLUGINTYPE_FREEPLAY)



/*void Log(void* object, std::string message)
{
	auto plugin = (QueueTracker*)object;
	plugin->cvarManager->log(message);
}*/


void QueueTracker::onLoad()
{
	queueStart_time, queueEnd_time, queueElapsed_time = time(NULL);
	cvarManager->log("QueueTracker loaded");
	gameWrapper->Toast("QueueTracker", "QueueTracker loaded successfully!");
	
	//gameWrapper->HookEventWithCaller<ServerWrapper>(
	//	"Function GameEvent_Soccar_TA.Active.StartRound",
	//	bind(
	//		&QueueTracker::EndTimer,
	//		this,
	//		std::placeholders::_1,
	//		std::placeholders::_2,
	//		std::placeholders::_3
	//	)
	//	);
	
	gameWrapper->HookEventWithCaller<ServerWrapper>(
		"Function ProjectX.CheckReservation_X.StartSearch",
		bind(
			&QueueTracker::StartTimer,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3)
		);


	
/*	gameWrapper->HookEventWithCaller<ServerWrapper>(
		"Function ProjectX.OnlineGameMatchmakingBase_X.EventFindGameComplete",
		bind(
			&QueueTracker::EndTimerGameComplete,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3)
		);
*/


		gameWrapper->HookEventWithCaller<ServerWrapper>(
		"Function TAGame.GameEvent_TA.PostBeginPlay",
		bind(
			&QueueTracker::EndTimerPostBeginPlay,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3)
		);

}

void QueueTracker::onUnload()
{
	cvarManager->log("QueueTracker unloaded");
	gameWrapper->Toast("QueueTracker", "QueueTracker unloaded successfully!");
}

void QueueTracker::StartTimer(ServerWrapper caller, void* params, std::string eventName) {

	queueStart_time = time(NULL);
	cvarManager->log("Queue time logged!");
	gameWrapper->Toast("QueueTracker", "Queue timer started!");
}


/*void QueueTracker::EndTimerGameComplete(ServerWrapper caller, void* params, std::string eventName) {
	auto mmrWrapper = gameWrapper->GetMMRWrapper();
	auto playlist = mmrWrapper.GetCurrentPlaylist();
	auto playlistName = GetPlaylistName(playlist);

	//if (playlistName != "Queueless" && playlistName != "") {
		queueEnd_time = time(NULL);
		queueElapsed_time = queueEnd_time - queueStart_time;
		queueElapsed_str = std::to_string(queueElapsed_time);

		cvarManager->log("Queue timer finished in " + std::to_string(queueElapsed_time) + " seconds.");
		gameWrapper->Toast("QueueTracker", ("GameCompleteMatch found in " + queueElapsed_str + " seconds!"));
		gameWrapper->LogToChatbox("Test" + queueElapsed_str);
	//}
	
}*/


void QueueTracker::EndTimerPostBeginPlay(ServerWrapper caller, void* params, std::string eventName) {
	auto mmrWrapper = gameWrapper->GetMMRWrapper();
	auto playlist = mmrWrapper.GetCurrentPlaylist();
	auto playlistName = GetPlaylistName(playlist);

	if (playlistName != "Queueless" && playlistName != "") {
		queueEnd_time = time(NULL);
		queueElapsed_time = queueEnd_time - queueStart_time;
		if (queueElapsed_time >= 60) {
			queueElapsed_str = std::to_string(queueElapsed_time / 60) + " minute(s)!";
		}
		else {
			queueElapsed_str = std::to_string(queueElapsed_time) + " seconds!";
		}

		cvarManager->log("Match found in " + queueElapsed_str);
		gameWrapper->Toast("QueueTracker", "Match found in " + queueElapsed_str);
	}
}


std::string GetPlaylistName(int playlistId) {
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
	case(6):
		return "Queueless";
		break;
	case(7):
		return "Queueless";
		break;
	case(8):
		return "Queueless";
		break;
	case(9):
		return "Queueless";
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
	case(19):
		return "Queueless";
		break;
	case(20):
		return "Queueless";
		break;
	case(21):
		return "Queueless";
		break;
	case(22):
		return "Queueless";
		break;
	case(23):
		return "Dropshot";
		break;
	case(24):
		return "Queueless";
		break;
	case(26):
		return "Queueless";
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
	case(34):
		return "Queueless";
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
		return "";
		break;
	}
}

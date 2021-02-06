#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"



class QueueTracker : public BakkesMod::Plugin::BakkesModPlugin
{
public:

public:
	virtual void onLoad();
	virtual void onUnload();
};
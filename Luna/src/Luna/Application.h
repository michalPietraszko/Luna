#pragma once
#include "Core.h"

namespace Luna
{

class LUNA_API Application
{
public:
	Application();
	virtual ~Application();
	void run();
};

// To be defined in CLIENT
Application* createApplication();

}// namespace

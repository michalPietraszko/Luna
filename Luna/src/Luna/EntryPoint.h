#pragma once

#ifdef LN_PLATFORM_WINDOWS
#include <iostream>

extern Luna::Application* Luna::createApplication();

int main(int argc, char** argv)
{
	std::cout << "dupa" << std::endl;
	auto app = Luna::createApplication();
	app->run();
	delete app;
}

#endif
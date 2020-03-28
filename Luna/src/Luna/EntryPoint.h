#pragma once

#ifdef LN_PLATFORM_WINDOWS

extern Luna::Application* Luna::createApplication();

int main(int argc, char** argv)
{
    Luna::Log::init();
    LN_CORE_WARN("Initialized log!");
    int a = 5;
    LN_INFO("Hello! Var={0}", a);

    auto app = Luna::createApplication();
    app->run();
    delete app;
}

#endif
#include "Application.h"
#include "EngineLoop.h"

namespace Ceres {

    void Application::Start() {
        if (EngineLoop::Instance().isGameRunning) {
            throw std::exception(
                "Cannot start engine after it has already been started!");
        }
        EngineLoop::Instance().Run();
    }

    void Application::Exit() { EngineLoop::Instance().isGameRunning = false; }

}
#pragma once
#include "Application.h"

namespace Ceres {
    class CERES_DLL EngineLoop {
    public:
        struct LoopConfig {

        };

        // Start the whole game
        EngineLoop();
        ~EngineLoop();

        static EngineLoop& Instance();
        static class Clock& GetGameClock();

    private:
        bool isGameRunning;
        double accumulateTime;
        double intervalTime;
        int maxSimulationCount;

        class MemoryManager* memoryManager;
        class AudioModule* audioModule;
        class WindowModule* windowModule;
        class RenderModule* renderModule;
        class InputModule* inputModule;
        class GUIModule* guiModule;
        class NetworkingModule* networkingModule;
        class CollisionsModule* collisionsModule;
        class CollisionSolverModule* collisionSolverModule;
        class Events* events;

        void Run();
        void StartUp();
        void Update();
        void FixedUpdate(float deltaTime) const;
        void VariableUpdate(float deltaTime) const;
        void ShutDown();

        void StartGameClock() const;

        friend class Application;
    };
}
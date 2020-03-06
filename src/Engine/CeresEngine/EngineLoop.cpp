#include "EngineLoop.h"

namespace Ceres {

    EngineLoop& EngineLoop::Instance() {
        static EngineLoop instance;
        return instance;
    }
}
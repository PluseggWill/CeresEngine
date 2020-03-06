#pragma once

#include "Ceres_DLL.h"

namespace Ceres {

    class Ceres_DLL Application {
    public:
        /**
         * \brief Start the game. Should be called in your main.cpp
         */
        static void Start();
        /**
         * \brief Exit the game, can be called anywhere
         */
        static void Exit();
    };

} 
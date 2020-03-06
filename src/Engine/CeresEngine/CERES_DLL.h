#pragma once

#if defined(IN_ENGINE) || defined(IN_TEST)
#define CERES_DLL
#define CERES_DLL_DECLARE
#else
#ifdef CERES_EXPORTS
#define CERES_DLL __declspec(dllexport)
#define CERES_DLL_DECLARE __declspec(dllexport)
#else
#define CERES_DLL __declspec(dllimport)
#define CERES_DLL_DECLARE
#endif
#endif

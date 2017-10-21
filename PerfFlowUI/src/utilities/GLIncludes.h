#pragma once

#if defined(_WIN32) && !defined(APIENTRY)
#define APIENTRY __stdcall
#endif
#include "glad/glad.h"

#ifndef OGLPLUS_NO_SITE_CONFIG
#define OGLPLUS_NO_SITE_CONFIG
#endif
#undef OGLPLUS_LINK_LIBRARY
#define OGLPLUS_LINK_LIBRARY 1
#include "oglplus/all.hpp"
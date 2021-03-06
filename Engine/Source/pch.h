#ifndef PCH_H_
#define PCH_H_

// std includes
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <future>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <random>
#include <sstream>
#include <queue>
#include <cstdio>
#include <array>
#include <numeric>
#include <regex>
#include <filesystem>

// cuda
#include <cuda.h>

// glm
#define GLM_FORCE_CUDA // Has to be defined after #include <cuda.h>
#include <glm/glm.hpp>
#include <types/vector.hpp>	
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_access.hpp>

// Fluid Engine
#include <Debug/Debug.h>
#include <Core/Input.h>
#include <Core/Ref.h>
#include "Core/Events/Event.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

#endif // !PCH_H_

// Whether debug macros such as Assert() or Log() should be enabled in release
#define ENABLE_DEBUG_MACROS_RELEASE true

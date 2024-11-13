#ifndef MASTER_HEADER_H
#define MASTER_HEADER_H

// COMMON-LIBS
#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <memory>
#include <bitset>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_map>
#include <map>
#include <functional>
#include <cassert>

// HEADERS
#include "ecs/core/types.hpp"
#include "ecs/core/ecsManager.hpp"

#include "ecs/components/velocity.hpp"
#include "ecs/components/acceleration.hpp"

#include "ecs/systems/MovementSystem.hpp"

#include "core/interface.hpp"
#include "core/savefile.hpp"
#include "core/game.hpp"
#include "core/audio.hpp"
#include "core/control.hpp"




#endif
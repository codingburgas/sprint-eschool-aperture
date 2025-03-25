#pragma once

#include <crow.h>

#include "app-type.hpp"
#include "database.hpp"

void setupLessons(App& app, crow::Blueprint& lessonsBlueprint, Database& database);
#pragma once

#include <crow.h>

#include "app.hpp"
#include "database.hpp"

void setupLessons(App& app, crow::Blueprint& lessonsBlueprint, Database& database);
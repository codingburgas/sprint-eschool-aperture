#pragma once

#include <crow.h>

#include "app.hpp"
#include "database.hpp"

void authorize(App&, const crow::request&, crow::response&, const string& userId);

void setupSignup(App&, Database&);
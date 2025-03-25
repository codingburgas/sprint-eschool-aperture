#pragma once

#include <crow.h>
#include <crow/middlewares/cookie_parser.h>

#include "authentication.hpp"

using App = crow::App<crow::CookieParser, Authentication>;
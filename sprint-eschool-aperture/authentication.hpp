#pragma once

#include <string>

#include <crow.h>
#include <crow/middlewares/cookie_parser.h>
#include <jwt-cpp/jwt.h>

using namespace std;

string generateToken(string userId);

struct Authentication : crow::ILocalMiddleware
{
	struct context
	{};

	template <typename AppContext>
	void before_handle(crow::request&, crow::response& response, context&, AppContext& appContext)
	{
		string key = appContext.get<crow::CookieParser>().get_cookie("key");

		try
		{
			jwt::verify()
				.with_issuer("Aperture Notepad")
				.allow_algorithm(jwt::algorithm::hs256("MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDe7euZqvMwZPAa1MAl0P7NveXhE/96npELa2Nw6ukf28gUbME/l8biEOA+fF1sM0eY/QcG2GjuUnAEuGPjqDvmFhxA7G4K1CjzxZFm8EZjTXtcHsJ3YP1qAJkqgb1f5YmH4fvuWPSNA700BUXzXvqCJs3z6bpzBfv+mNJg8CsLJzqOVceKzxgpqdEl1Yns8GOO95yvJTjjCQrGcYXo7MqC/Mc7IQfMk84CNDdfYwefxQ6/lt2Lp5IkImIhSBpm1haX6Sty0WnVQjFnyGC506dJuSsupD3gVTaHwCkqxaSPeSRA3g7RrJwgPCyrur7fVWyd0xMKkUZxK9a0d660GvPnAgMBAAECggEAJElO1aL9Va3AZWWm5yDnML8NyX6zUZa43kZ7F7is/JoOLcDsDblbTpXXomQk4sVQDKd2+tbD8bLqd+I5pCdQpKmJrMmvOcUB63gHrF1E38oPX9XD6qGXbictxzz6Ab9/jOYsV0YUfFWU+QA4vB4EIaZGVMMBLdLWC0F90PiW0QgiWr1CrAMVFYWzcxdVoQk50HzX7iL2kg0Mc2pCzqoOdH8k4wC8rhs8KRkbK6d1IMxAV+srq0emmPciLgt4Pqp/c3kt5mAgonedSRCpPuLogaVB/t5AuOLt68LFEe5GBmqiAOqVFW4KLCc7N8KKy6OXUwFcI7aiNeXsLT/KwC699QKBgQDwSKzTD6kymwJoEooLyXxoANnsLbI6+kDaoZnPpKkq+tVWRRVwuRA4DZVoie27R4yFOanc0rrvEDJ9E98q3seHO05kGOO5h2UWSD+ogtz1Vm/w6e1fTOaNYzBIPq0+m9IXpbXf0XirenTRX9RpjxGn8KqPWghyo9LI8/sZUrDAbQKBgQDtgqkTvnsNP2SvMN2i0p5tSgR7PgdtYViAMMbP3MmaEi1Jn+m8hF4CopOL33A3QZHLelirFhPRIKN4HuB/10fmlWewk2Qt30AXl1WACLELCsYcR5y1lXHI+9g5mj3P+I5t2GXrNK8PWToeZsV6fokr9kawRr6DUtu1r8jis/4ZIwKBgQCYspahymIL9tYgrSdtNi4JKgFTRfbt4/sy9V95xXp8Bcttd5mYeQMFnBxGwuCBE4cJYwu/eWuyYOi089vusoS6O8YldmvBi3mCH4fU3tTsVHHu97oRxhz93Prh7nLKRtvMi1J5WfUFhFyYcf3a10CxKRA66UxVDib17Za1EQeiQQKBgBOuq0JGm73qTfayrvtKRvS5mIt6BXWMBqCA6kjZfB93eCdMyDrmIUBIpr+FobACkAlztxtedf/zm3hd3q7ZcUzrfq9EV53xjUcnNF+q2LkYiHhZeuQVYVuNe0qyvIKaj3sM3s1SDVvRQh64146iI83v18XN5wXM/QYebiBTWDBPAoGAf8UCXyzcu0XtG21SBUuSL80OMQKOCPxctl+Kv3pgQ1KTcEThPUVNeGBUBNB6HcFyYRJVL3N0XmN7X5ttuGXpib7OC/EyHcrERoVu0KpGy/WbtL5idw4PqYhOQ2fOALFdQgSIA4U07CzhVY5E6eMDDsA6Vk4nBAPtU8eQt66Gy/M"))
				.verify(jwt::decode(key));
		}
		catch (...)
		{
			response.add_header("Location", "/login/");
			response.code = crow::SEE_OTHER;
			response.end();
		}
	}

	template <typename AppContext>
	void after_handle(crow::request&, crow::response&, context&, AppContext& appContext)
	{}
};

// AuthSkip
/*
if (request.url == "/login/" || request.url == "/register/")
			{
				response.add_header("Location", "/lessons/");
				response.code = crow::SEE_OTHER;
				response.end();
			}*/
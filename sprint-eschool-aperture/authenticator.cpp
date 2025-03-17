#include "authenticator.hpp"

#include <chrono>
#include <string>

#include <jwt-cpp/jwt.h>

using namespace std;

string generateToken(const string& email, const string& key)
{
	return jwt::create()
		       .set_issuer("Aperture Notepad")
		       .set_subject(email)
		       .set_expires_at(chrono::system_clock::now() + chrono::months(1))
		       .sign(jwt::algorithm::hs256("0ee82d17ea3579a2f3d876ed730f338edb05af97c8a3d78e8f55cd8f392dff1b"));
}

bool validateToken(const string& token)
{

}
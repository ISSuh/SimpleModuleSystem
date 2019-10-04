#define _CRT_SECURE_NO_DEPRECATE

#include <cpprest/http_listener.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>

#include <mrm/server.hpp>

using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

int main()
{
	mrm::MrmServer server(U("http://0.0.0.0:9090/api"));
	server.Init();
	server.OpenWait();

	server.Run();

	return 0;
}

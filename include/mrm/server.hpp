#ifndef MRM_MRMSERVER_HPP
#define MRM_MRMSERVER_HPP

// std
#include <iostream>

// casablanca
#include <cpprest/http_listener.h>

using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

namespace mrm
{

class MrmServer
{
public:
	MrmServer(const utility::string_t &address) : m_address(address) {}

	~MrmServer()
	{
		std::cout << "Terminating." << std::endl;
	}

	bool Init()
	{
		std::cout << "Initialize listener." << std::endl;
		m_listener = std::unique_ptr<http_listener>(new http_listener(m_address));

		std::cout << "Regist handle." << std::endl;
		m_listener->support(methods::GET, std::bind(&MrmServer::Get,
													this,
													std::placeholders::_1));
		m_listener->support(methods::POST, std::bind(&MrmServer::Post,
													 this,
													 std::placeholders::_1));
		m_listener->support(methods::PUT, std::bind(&MrmServer::Put,
													this,
													std::placeholders::_1));
		m_listener->support(methods::DEL, std::bind(&MrmServer::Delete,
													this,
													std::placeholders::_1));

		return true;
	}

	void OpenWait()
	{
		std::cout << "Listener Wait." << std::endl;
		m_listener->open().wait();
	}

	void Run()
	{
		std::cout << "Running MRM Server" << std::endl;

		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}

private:
	// Definde Get method 
	void Get(http_request req)
	{
		auto http_get_vars = uri::split_query(req.request_uri().query());
		auto http_get_path = uri::split_path(req.request_uri().path());

		test(req, status_codes::OK, json::value::string(U("TEST")));
	}

	// Definde Post method 
	void Post(http_request req)
	{
	}

	// Definde Put method 
	void Put(http_request req)
	{
	}

	// Definde Delete method 
	void Delete(http_request req)
	{
	}

private:
	void test(const http_request &request, const status_code &status, const json::value &response)
	{
		json::value resp;
		resp[U("status")] = json::value::number(status);
		resp[U("response")] = response;

		// Pack in the current time for debugging purposes.
		time_t now = time(0);
		// utility::stringstream_t ss;`
		// ss << put_time(localtime(&now), L"%Y-%m-%dT%H:%S:%MZ");
		resp[U("server_time")] = json::value::string(std::to_string(now));

		request.reply(status, resp);
	}

public:
private:
	// Casablanca
	std::unique_ptr<http_listener> m_listener;

	// std
	utility::string_t m_address;
};

} // namespace mrm

#endif
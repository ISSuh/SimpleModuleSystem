#ifndef MRM_MRMSERVER_HPP
#define MRM_MRMSERVER_HPP

// std
#include <iostream>
#include <memory>
#include <thread>
#include <csignal>

// casablanca
#include <cpprest/http_listener.h>

// log
#include <spdlog/spdlog.h>


using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

namespace mrm
{

class MrmApiServer
{
public:
	MrmApiServer(const utility::string_t &address) : m_address(address){
		m_consoleLogger = spdlog::get("MRM_APIServer");
	}

	bool Init()
	{	
		m_consoleLogger->info("Initialize listener");
		m_listener = std::unique_ptr<http_listener>(new http_listener(m_address));

		m_consoleLogger->info("Regist handle");
		m_listener->support(methods::GET, std::bind(&MrmApiServer::Get,
													this,
													std::placeholders::_1));
		m_listener->support(methods::POST, std::bind(&MrmApiServer::Post,
													 this,
													 std::placeholders::_1));
		m_listener->support(methods::PUT, std::bind(&MrmApiServer::Put,
													this,
													std::placeholders::_1));
		m_listener->support(methods::DEL, std::bind(&MrmApiServer::Delete,
													this,
													std::placeholders::_1));

		return true;
	}

	void OpenWait()
	{
		m_consoleLogger->info("Listener Wait");
		m_listener->open().wait();
	}

	void Run()
	{
		m_consoleLogger->info("Running MRM API Server");

		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}

	void Clear()
	{
		m_consoleLogger->info("Terminating");
	}

private:
	// Define GET, POST, PUT, DELETE Handler

	// Define Get method 
	void Get(http_request req)
	{
		auto http_get_vars = uri::split_query(req.request_uri().query());
		auto http_get_path = uri::split_path(req.request_uri().path());

		test(req, status_codes::OK, json::value::string(U("TEST")));
	}

	// Define Post method 
	void Post(http_request req)
	{
	}

	// Define Put method 
	void Put(http_request req)
	{
	}

	// Define Delete method 
	void Delete(http_request req)
	{
	}

private:
	// Define Main Logic method

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

private:
	// Casablanca
	std::unique_ptr<http_listener> m_listener;

	// std
	utility::string_t m_address;

	//log
	std::shared_ptr<spdlog::logger> m_consoleLogger;
	std::shared_ptr<spdlog::logger> m_fileLogger;

};

} // namespace mrm

#endif
#ifndef MRM_MRMSERVER_HPP
#define MRM_MRMSERVER_HPP

// std
#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>

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

class MrmUriList
{
public:
	MrmUriList()
	{
		uri.insert(std::make_pair("api", true));
		uri.insert(std::make_pair("list", true));
		uri.insert(std::make_pair("setting", true));
	}
	
	std::unordered_map<std::string, bool> uri;
};

class Publisher
{

};

class Message
{

};

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
		auto httpGetPath = uri::split_path(req.relative_uri().path());


		if(httpGetPath[0] == "list")
		{
			req.reply(status_codes::OK);
		}
		else if(httpGetPath[0] == "setting")
		{
			req.reply(status_codes::OK);
		}

		req.reply(status_codes::NotFound);
	}

	// Define Post method 
	void Post(http_request req)
	{
		auto httpPostPath = uri::split_path(req.relative_uri().path());


		if(httpPostPath[0] == "list")
		{
			if(httpPostPath[1] == "item")
			{
				AddNewMessage(req);
			}
		}

		req.reply(status_codes::NotFound);
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

	void postItem(const http_request &request)
	{
		request.reply(status_codes::OK);
	}

	void test(const http_request &request, const status_code &status, const json::value &response)
	{
		json::value resp;
		resp[U("status")] = json::value::number(status);
		resp[U("response")] = response;

		// Pack in the current time for debugging purposes.
		time_t now = time(0);
		resp[U("server_time")] = json::value::string(std::to_string(now));

		request.reply(status, resp);
	}

private:
	//log
	std::shared_ptr<spdlog::logger> m_consoleLogger;
	std::shared_ptr<spdlog::logger> m_fileLogger;

	// casablanca
	std::unique_ptr<http_listener> m_listener;

	// uri Lists
	MrmUriList uriList;
	
	// std
	utility::string_t m_address;



};

} // namespace mrm

#endif
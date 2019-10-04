// std
#include <iostream>

// casablanca
#include <cpprest/http_listener.h>

// mrm
#include <mrm/server.hpp>

// log
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

int main()
{

	// Create Logging
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto apiServer_consoleLogger = std::make_shared<spdlog::logger>("MRM_APIServer", consoleSink);
	auto messageBroker_consoleLogger  = std::make_shared<spdlog::logger>("MRM_MessageBroker",  consoleSink);
	consoleSink->set_level(spdlog::level::debug);

    // auto fileSink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logfile", 23, 59);		
	// auto apiServer_fileLogger = std::make_shared<spdlog::logger>("apiServer_fileLogger", fileSink);
	// auto messageBroker_fileLogger  = std::make_shared<spdlog::logger>("messageBroker_fileLogger",  fileSink);
	// fileSink->set_level(spdlog::level::debug);
	
	spdlog::logger mainLogger("MRM_MainLogger", {consoleSink/*, fileSink*/});
	mainLogger.set_level(spdlog::level::debug);

	spdlog::register_logger(apiServer_consoleLogger);
	spdlog::register_logger(messageBroker_consoleLogger);
	// spdlog::register_logger(apiServer_fileLogger);
	// spdlog::register_logger(messageBroker_fileLogger);

	spdlog::set_default_logger(std::make_shared<spdlog::logger>("MRM_MainLogger", spdlog::sinks_init_list({consoleSink/*, fileSink*/})));


	// MRM API Server 
	mainLogger.info("RUNNING PROCESS");
	mrm::MrmApiServer server(U("http://0.0.0.0:9090/api"));
	server.Init();
	server.OpenWait();

	server.Run();

	server.Clear();
	
	mainLogger.info("STOP PROCESS");
	spdlog::shutdown();
}

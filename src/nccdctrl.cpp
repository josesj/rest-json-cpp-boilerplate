#include "nccdctrl.h"

std::string LOG_CONSOLE;
std::shared_ptr<nCcdCtrl> nCcdCtrlApp;

int main(const int, const char **) {
    nCcdCtrlApp = shared_ptr<nCcdCtrl>(new nCcdCtrl());
    return 0;
}

nCcdCtrl::nCcdCtrl() {

    std::ostringstream stringStream;

    // Add SIGTERM handler
    std::signal(SIGINT, sigtermHandler);

    configFileReader = &ConfigFileReader::getInstance();
    configFileReader->readConfigFile();
    LOG_CONSOLE = configFileReader->getSystemName();

    try {

        std::string logNamePrefix = configFileReader->getSystemName();
        transform(logNamePrefix.begin(), logNamePrefix.end(), logNamePrefix.begin(),
                  (int (*)(int)) tolower);
        stringStream << configFileReader->getLogsPath() << logNamePrefix
                     << "-ccdctrl.log";

        // Set async logging flush policy
        size_t q_size = 4096; // queue size must be power of 2
        spdlog::set_async_mode(q_size, spdlog::async_overflow_policy::block_retry,
                               nullptr, std::chrono::seconds(2));

        // Create combined logger: console and rotating file.
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                stringStream.str(), 1048576, 9));
        auto combined_logger =
                std::make_shared<spdlog::logger>(LOG_CONSOLE, begin(sinks), end(sinks));
        combined_logger->set_level(spdlog::level::trace);
        // Set logging levels
        combined_logger->flush_on(spdlog::level::err);
        sinks[0]->set_level(spdlog::level::trace);
        sinks[1]->set_level(spdlog::level::trace);
        // Register logger
        spdlog::register_logger(combined_logger);
    } catch (const spd::spdlog_ex &ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        exit(1);
    }

    spdlog::get(LOG_CONSOLE)->info("Starting ccd controller!");

    stringStream.str("");
    stringStream.clear();
#ifdef _WIN32
    stringStream << "Service PID is " << _getpid();
#else
    stringStream << "Service PID is " << getpid();
#endif
    spdlog::get(LOG_CONSOLE)->info(stringStream.str());

    // Create command queue
    commandQueue = new CommandQueue();
    commandFactory = new CommandFactory();

    // Create Rest Api Manager object
    restAPI = new RestAPI(this->commandQueue, this->commandFactory);
}

nCcdCtrl::~nCcdCtrl() { spdlog::drop_all(); }

void nCcdCtrl::shutdown() {
    spdlog::get(LOG_CONSOLE)->info("Shutdown hook...");
    this->commandQueue->stopCommandQueue();
}

void nCcdCtrl::sigtermHandler(const int signal_number) {
    std::ostringstream stringStream;
    stringStream << "Received SIGTERM signal number " << signal_number;
    spdlog::get(LOG_CONSOLE)->info(stringStream.str());
    nCcdCtrlApp->shutdown();
    // Flush log to disk before exit.
    spdlog::get(LOG_CONSOLE)->flush();
    spdlog::drop_all();
}

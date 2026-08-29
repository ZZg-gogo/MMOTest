#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>


void Logger::init()
{
    auto consoleSink =
        std::make_shared<
            spdlog::sinks::stdout_color_sink_mt>();

    auto fileSink =
        std::make_shared<
            spdlog::sinks::basic_file_sink_mt>(
                "/home/zzh/MMOTest/logs/server.log",
                true
            );

    std::vector<spdlog::sink_ptr> sinks{
        consoleSink,
        fileSink
    };

    m_logger = std::make_shared<spdlog::logger>(
        "server",
        sinks.begin(),
        sinks.end()
    );
}
#ifndef __LOGGER_H__
#define __LOGGER_H__



#include <spdlog/spdlog.h>



class Logger
{
public:
    static Logger& instance()
    {
        static Logger logger;
        return logger;
    }

    void init();

    template<typename... Args>
    void info(
        spdlog::format_string_t<Args...> fmt,
        Args&&... args)
    {
        m_logger->info(
            fmt,
            std::forward<Args>(args)...
        );
    }

    template<typename... Args>
    void error(
        spdlog::format_string_t<Args...> fmt,
        Args&&... args)
    {
        m_logger->error(
            fmt,
            std::forward<Args>(args)...
        );
    }

private:
    Logger() {init();};

private:
    std::shared_ptr<spdlog::logger> m_logger;
};



#define LOGGER_INFO(...) Logger::instance().info(__VA_ARGS__)
#define LOGGER_WARN(...) Logger::instance().warn(__VA_ARGS__)
#define LOGGER_ERROR(...) Logger::instance().error(__VA_ARGS__)






#endif
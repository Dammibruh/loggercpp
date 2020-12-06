#include <fmt/core.h>
#include <fmt/color.h>
#include <sstream>
#include <fmt/chrono.h>

enum class LEVEL {
    DEBUG,
    INFO,
    ANY,
    ERROR,
    WARNING
};

class Logger {
    std::string c_log_format = "[{LEVEL} | {DATE}] {TEXT}";
    LEVEL c_default_level = LEVEL::ANY;
    LEVEL c_filter_level = LEVEL::ANY;
    public:
    std::stringstream p_logs;
    void set_log_format(const std::string& new_log_format){
        this->c_log_format = new_log_format;
    }
    void set_default_log_level(LEVEL new_log_level){
        this->c_default_level = new_log_level;
    }
    void filter_logs_by_level(LEVEL new_filter_level){
        this->c_filter_level = new_filter_level;
    }
    auto getColor( LEVEL level){
        switch(level){
            case LEVEL::DEBUG:
                return fmt::color::floral_white;
            case LEVEL::INFO:
                return fmt::color::steel_blue;
            case LEVEL::WARNING:
                return fmt::color::yellow;
            case LEVEL::ERROR:
                return fmt::color::crimson;
            case LEVEL::ANY:
                return fmt::color::white;
        }
    }
    std::string getLevelStr( LEVEL level){
        switch(level){
            case LEVEL::DEBUG:
                return "DEBUG";
            case LEVEL::INFO:
                return "INFO";
            case LEVEL::WARNING:
                return "WARNING";
            case LEVEL::ERROR:
                return "ERROR";
            case LEVEL::ANY:
                return "LOG";
        }
    }
    void log(const std::string& str, LEVEL level){
        auto color = this->getColor(level);
        std::string level_str = this->getLevelStr(level);
        std::time_t t = std::time(nullptr);
        std::string date = fmt::format("{:%Y-%m-%d}", fmt::localtime(t));
        std::string logout = fmt::format(
                this->c_log_format, fmt::arg("LEVEL", level_str),
                fmt::arg("DATE", date), fmt::arg("TEXT", str)
        );
        this->p_logs << fmt::format("{}\n", logout);
        if(this->c_filter_level == level || level == LEVEL::ANY || this->c_filter_level == LEVEL::ANY)
            fmt::print(fg(color) | fmt::emphasis::bold, "{}\n", logout);
    }
    void debug(const std::string& str){
        this->log(str, LEVEL::DEBUG);
    }
    void error(const std::string& str){
        this->log(str, LEVEL::ERROR);
    }
    void info(const std::string& str){
        this->log(str, LEVEL::INFO);
    }
    void warn(const std::string& str){
        this->log(str, LEVEL::WARNING);
    }
};

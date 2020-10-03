#include <ctime>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

enum class LEVEL {
    ANY,
    INFO,
    WARN,
    DEBUG,
    ERROR
};
struct LOG {
    std::string_view content;
    std::string_view date;
    LEVEL level;
    LEVEL filter_level;
};
class Logger {
    std::map<LEVEL, std::string_view> level_to_str = {
        {LEVEL::ANY, "LOG"},
        {LEVEL::INFO, "INFO"},
        {LEVEL::WARN, "WARN"},
        {LEVEL::DEBUG, "DEBUG"},
        {LEVEL::ERROR, "ERROR"}
    };
    std::map<std::string_view, LEVEL> str_to_level = {
        {"LOG", LEVEL::ANY},
        {"INFO", LEVEL::INFO},
        {"WARN", LEVEL::WARN},
        {"DEBUG", LEVEL::DEBUG},
        {"ERROR", LEVEL::ERROR}
    };
    LEVEL level = LEVEL::ANY;
    std::string format = "[{LEVEL} {DATE}] - {TEXT}";
    std::stringstream logs;
    LEVEL filter_level = LEVEL::ANY;
    void _log(const std::string_view& str, const LEVEL& level){
        std::string_view date = this->currentDateTime(),
            levelstr = this->level_to_str[level],
            file = __FILE__;
            std::vector<std::vector<std::string_view>> formats {
                {"{DATE}", date},
                    {"{LEVEL}", levelstr},
                    {"{TEXT}", str},
                    {"{FILE}", file},
            };
            std::string form = std::move(this->format);
            for(const auto& i: formats){
                form.replace(form.find(i[0]), i[0].size(), i[1]);
            }
            this->logs << form;
            std::cout << form;
    }
    bool _checkLevel(const LEVEL& level){
        return (this->filter_level == LEVEL::ANY || this->filter_level == level || level == LEVEL::ANY);
    }
    void _on_log(const LOG& log){
        if( this->_checkLevel(log.level)){
            this->_log(log.content, log.level);
        }
    }

    std::string currentDateTime() {
        std::time_t     t = time(0);
        std::tm*  now = std::localtime(&t);
        std::stringstream buf;
        buf << (now->tm_year)+1900 << "-"
            << (now->tm_mon)+1 << "-" 
            << (now->tm_mday) << " "
            << (now->tm_hour) << ":"
            << (now->tm_min) << ":"
            << (now->tm_sec);
        return buf.str();
    }

    public:
    void setFormat(const std::string_view& form){
        this->format = form;
    }
    std::string_view getFormat(){
        return this->format;
    }
    void setDefaultLevel(const LEVEL& lvl){
        this->level = lvl;
    }
    void setFilter(const LEVEL& level){
        this->filter_level = level;
    }
    LEVEL getLevel(){
        return this->level;
    }
    std::string_view getLogs(){
        return this->logs.str();
    }
    void log(const std::string_view& str, const LEVEL& level){
        LOG _logs {.content = str, .date = this->currentDateTime(), .level = level, .filter_level = this->filter_level};
        this->_on_log(_logs);
    }
    void log(const std::string_view& str){
        LOG _logs {.content = str, .date = this->currentDateTime(), .level = this->level, .filter_level = this->filter_level};
        this->_on_log(_logs);
    }
};

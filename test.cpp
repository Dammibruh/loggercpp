#include "logger.hpp"

int main(){
    Logger logger;
    logger.filter_logs_by_level(LEVEL::DEBUG);
    logger.error("gay");
    logger.debug("bruh");
    logger.info("hahayes");
}

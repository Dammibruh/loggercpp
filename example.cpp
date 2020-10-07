#include "logger.cpp"

int main(){
    Logger logger;
    logger.setFormat("{LEVEL} | {DATE} > {TEXT} | {FILE}");
    logger.setDefaultLevel(LEVEL::DEBUG);
    logger.log("hahayes");
}

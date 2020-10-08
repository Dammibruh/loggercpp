#include "logger.cpp"

int main(){
    Logger logger;
    logger.setFormat("{LEVEL} | {DATE} > {TEXT} | {FILE}\n");
    logger.setDefaultLevel(LEVEL::DEBUG);
    logger.setLog(true);
    logger.log("hahayes");
}

#include "factoryPattern.h"

std::unique_ptr<Logger> LoggerFactory::createLogger(LoggerType type){
    switch(type){
        case FILE: return std::make_unique<FileLogger>();
        case CONSOLE: return std::make_unique<ConsoleLogger>();
        default: throw std::invalid_argument("Invalid type.");
    }
}
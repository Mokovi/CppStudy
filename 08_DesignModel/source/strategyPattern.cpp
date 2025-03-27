#include "strategyPattern.h"

void Compressor::setStrategy(std::unique_ptr<CompressionStrategy> newStrategy) {
    strategy = std::move(newStrategy);
}

void Compressor::executeCompression(const std::string& file) {
    strategy->compress(file);
}
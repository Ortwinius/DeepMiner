#pragma once

#include <random>
#include <chrono>
#include "constants.h"

int generateRandomNumber(std::mt19937& gen, int min, int max);

const char convertBlockToChar(const BlockType& blockType);

int convertBlockTypeToScoreValue(const BlockType& blockType);

const std::string convertBlockTypeToString(const BlockType& blockType);

double calculateDeltaTime(std::chrono::time_point<std::chrono::high_resolution_clock> startTime, std::chrono::time_point<std::chrono::high_resolution_clock> endTime);
#pragma once

#include <random>
#include "constants.h"

int generateRandomNumber(std::mt19937& gen, int min, int max);

const char convertBlockToChar(const BlockType& blockType);

int convertBlockTypeToScoreValue(const BlockType& blockType);


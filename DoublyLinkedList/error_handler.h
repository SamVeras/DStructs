#pragma once
#define ERROR_ALLOC_FAIL -1
#define ERROR_INDEX_ERROR -2
#define ERROR_NOT_FOUND -3
#define ERROR_NONLETHAL -99

void error_handler(int error, char* message);

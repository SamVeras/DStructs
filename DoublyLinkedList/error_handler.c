#include "error_handler.h"
#include <stdio.h>
#include <stdlib.h>

void error_handler(int error, char* message) {
  switch (error) {
    case ERROR_ALLOC_FAIL:
      fprintf(stderr, "AllocFailure: %s\n", message);
      exit(1);
    case ERROR_INDEX_ERROR:
      fprintf(stderr, "IndexError: %s\n", message);
      exit(1);
    case ERROR_NOT_FOUND:
      fprintf(stderr, "NotFoundError: %s\n", message);
      exit(1);
    case ERROR_NONLETHAL:
      fprintf(stderr, "NonLethal: %s\n", message);
      break;
    default:
      fprintf(stderr, "UnknownError: %s (%d)\n", message, error);
      exit(1);
  }
};
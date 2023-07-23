#ifndef S21_EXCEPTION_HANDLING_H
#define S21_EXCEPTION_HANDLING_H

#include <stdexcept>
#include <string>

class InvalidMatrixException : public std::invalid_argument {
 public:
  InvalidMatrixException(const std::string& message)
      : std::invalid_argument(message) {}
};

class DifferentMatrixDimensionsException : public std::invalid_argument {
 public:
  DifferentMatrixDimensionsException(const std::string& message)
      : std::invalid_argument(message) {}
};

class MultInvalidMatrixSizeException : public std::invalid_argument {
 public:
  MultInvalidMatrixSizeException(const std::string& message)
      : std::invalid_argument(message) {}
};

class NotSquaredMatrixException : public std::invalid_argument {
 public:
  NotSquaredMatrixException(const std::string& message)
      : std::invalid_argument(message) {}
};

class ZeroDeterminantException : public std::runtime_error {
 public:
  ZeroDeterminantException(const std::string& message)
      : std::runtime_error(message) {}
};

#endif /* S21_EXCEPTION_HANDLING_H */

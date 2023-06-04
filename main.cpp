#include <iostream>

#include "includes.inc"

int main() {
  for (int i = 0; i < 5; i++) {
    std::cout << "Hello, World!" << std::endl;
  }

  int length;
  std::cout << "Input: " << std::endl;
  std::cin >> length;
  std::cout << "Done!";

  int arr[length];

  for (int i = 0; i < length; i++) {
    arr[i] = -1;
  }

  for (int i = 0; i < length; i++) {
    std::cout << arr[i] << std::endl;
  }
  return 0;
}
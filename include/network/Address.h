#include <string>

struct Address
{
  std::string address;
  int portNumber;

  Address(std::string address, int portNumber)
  : address(std::move(address)), portNumber(portNumber) {}
};

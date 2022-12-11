#include <iostream>
#include <string>
#include <cstring>

int main()
{

  char s[30] = { "Ana are mere" };
  char t[30] = { "B" };

  char* p = strtok(s, " ");

  while (p != NULL)
  {
    t[1] = { '0' };
    p = strtok(NULL, " ");
  }


  std::cout << t;

  return 0;
}
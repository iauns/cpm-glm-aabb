
#include <cstdlib>
#include <iostream>
#include <exception>
#include <memory>

#include <gtest/gtest.h>

int main(int argc, char** argv)
{
  // Add a global test environment that initializes an OpenGL batch renderer.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


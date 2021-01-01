// MIT License

// Copyright (c) 2020 Edward Liu

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "test/utest_framework/simple_unit_test.h"

#include <iostream>

namespace elsh {
namespace test {
namespace utest_framework {

TestFactory* TestFactory::Instance() {
  static TestFactory instance;
  return &instance;
}

void TestFactory::Append(std::shared_ptr<TestBase> test_case) {
  tests_.push_back(test_case);
}

void TestFactory::Run() {
  for (auto test_case : tests_) {
    test_case->TestFunc();
  }
}

void TestFactory::Dump() {
  for (const auto& test_case : tests_) {
    for (const auto& test_info : test_case->test_infos_) {
      if (test_info.as_expected) {
        continue;
      }
      std::cout << test_info.file << ": " << test_case->name_ << " : "
                << test_info.line_num << ": " << test_info.condition
                << " check failed.\n"
                << std::flush;
    }
  }
}

}  // namespace utest_framework
}  // namespace test
}  // namespace elsh

int main(int, char**) {
  elsh::test::utest_framework::TestFactory::Instance()->Run();
  elsh::test::utest_framework::TestFactory::Instance()->Dump();
  return 0;
}

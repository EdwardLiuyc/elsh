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

#ifndef TEST_SIMPLE_UNIT_TEST_H_
#define TEST_SIMPLE_UNIT_TEST_H_

/// @brief A simple unit test framework which rely on only c++11 stl.
/// Should be used like this:
///
///  #include "simple_unit_test.h"
///  #include <fstream>
///
///  namespace std {
///  SIMPLE_TEST(LEX, TEST_1) {
///    fstream fs("test.txt");
///    EXPECT_TRUE(fs.is_open());
///  }
///  }

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace elsh {
namespace simple_unit_test {

class TestFactory;

class TestBase {
 public:
  TestBase() = default;
  virtual ~TestBase() {}

  /// @brief This function should be implemented by child class for each test
  /// case.
  virtual void TestFunc(){};
};

class TestFactory {
 public:
  TestFactory() = default;
  ~TestFactory() = default;

  static std::shared_ptr<TestFactory> Instance() {
    if (!instance_) {
      instance_ = std::shared_ptr<TestFactory>(new TestFactory);
    }
    return instance_;
  }

  void Append(TestBase* test_case);
  void Run();

 private:
  std::vector<TestBase*> tests_;
  static std::shared_ptr<TestFactory> instance_;
};

namespace internal {
inline int RegisterNewTestCase(TestBase* test_case) {
  TestFactory::Instance()->Append(test_case);
  return 0;
}

}  // namespace internal
}  // namespace simple_unit_test
}  // namespace elsh

#define TEST_CLASS_NAME(package_name, test_case_name) \
  SimpleTest##package_name##test_case_name

#define SIMPLE_TEST_(package_name, test_case_name, parent_class,               \
                     factory_class)                                            \
  class TEST_CLASS_NAME(package_name, test_case_name) : public parent_class {  \
   public:                                                                     \
    TEST_CLASS_NAME(package_name, test_case_name)() : parent_class(){};        \
    void TestFunc() override;                                                  \
                                                                               \
    static int const nothing_important;                                        \
  };                                                                           \
                                                                               \
  int const TEST_CLASS_NAME(package_name, test_case_name)::nothing_important = \
      elsh::simple_unit_test::internal::RegisterNewTestCase(                   \
          new TEST_CLASS_NAME(package_name, test_case_name));                  \
  void TEST_CLASS_NAME(package_name, test_case_name)::TestFunc()

#define SIMPLE_TEST(package_name, test_case_name)  \
  SIMPLE_TEST_(package_name, test_case_name,       \
               ::elsh::simple_unit_test::TestBase, \
               ::elsh::simple_unit_test::TestFactory)

#endif  // TEST_SIMPLE_UNIT_TEST_H_

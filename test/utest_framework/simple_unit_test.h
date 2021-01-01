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

#ifndef TEST_UTEST_FRAMEWORK_SIMPLE_UNIT_TEST_H_
#define TEST_UTEST_FRAMEWORK_SIMPLE_UNIT_TEST_H_

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

#if defined(__GNUC__) && !defined(COMPILER_ICC)
#define TEST_ATTRIBUTE_UNUSED_ __attribute__((unused))
#elif defined(__clang__)
#if __has_attribute(unused)
#define TEST_ATTRIBUTE_UNUSED_ __attribute__((unused))
#endif
#endif
#ifndef TEST_ATTRIBUTE_UNUSED_
#define TEST_ATTRIBUTE_UNUSED_
#endif

namespace elsh {
namespace test {
namespace utest_framework {

struct TestInfo {
  int line_num;
  std::string file;
  std::string condition;
  bool as_expected = true;
};

class TestBase {
  friend class TestFactory;

 public:
  TestBase() = default;
  virtual ~TestBase() {}

  /// @brief This function should be implemented by child class for each test
  /// case.
  virtual void TestFunc() = 0;

  void Insert(const std::string& file, const std::string& condition,
              const int line_num, const bool as_expected) {
    test_infos_.emplace_back();
    auto& test_info = test_infos_.back();
    test_info.line_num = line_num;
    test_info.condition = condition;
    test_info.file = file;
    test_info.as_expected = as_expected;
  }

 protected:
  std::vector<TestInfo> test_infos_;
  std::string name_;
};

class TestFactory {
 public:
  /// Singleton
  static TestFactory* Instance();
  /// @brief Add a new test case.
  void Append(std::shared_ptr<TestBase> test_case);
  /// @brief Run all test cases.
  void Run();
  /// @brief Dump all test informations.
  void Dump();

 private:
  std::vector<std::shared_ptr<TestBase>> tests_;
};

namespace internal {
inline int RegisterNewTestCase(std::shared_ptr<TestBase> test_case) {
  TestFactory::Instance()->Append(test_case);
  return 0;
}

template <typename T1, typename T2>
constexpr bool StaticAssertTypeEq() noexcept {
  static_assert(std::is_same<T1, T2>::value, "T1 and T2 are not the same type");
  return true;
}

}  // namespace internal

}  // namespace utest_framework
}  // namespace test
}  // namespace elsh

#define TEST_CLASS_NAME(package_name, test_case_name) \
  SimpleTest##package_name##test_case_name

#define SIMPLE_TEST_(package_name, test_case_name, parent_class,              \
                     factory_class)                                           \
  class TEST_CLASS_NAME(package_name, test_case_name) : public parent_class { \
   public:                                                                    \
    TEST_CLASS_NAME(package_name, test_case_name)() : parent_class() {        \
      this->name_ = std::string(#package_name) + "." + #test_case_name;       \
    }                                                                         \
    ~TEST_CLASS_NAME(package_name, test_case_name)() override = default;      \
    void TestFunc() override;                                                 \
                                                                              \
   private:                                                                   \
    static int const nothing_important_ TEST_ATTRIBUTE_UNUSED_;               \
  };                                                                          \
                                                                              \
  int const TEST_CLASS_NAME(package_name,                                     \
                            test_case_name)::nothing_important_ =             \
      elsh::test::utest_framework::internal::RegisterNewTestCase(             \
          std::make_shared<TEST_CLASS_NAME(package_name, test_case_name)>()); \
  void TEST_CLASS_NAME(package_name, test_case_name)::TestFunc()

#define SIMPLE_TEST(package_name, test_case_name)       \
  SIMPLE_TEST_(package_name, test_case_name,            \
               ::elsh::test::utest_framework::TestBase, \
               ::elsh::test::utest_framework::TestFactory)

#define EXPECT_OP(val1, val2, operator)                       \
  {                                                           \
    if (!((val1) operator(val2)))                             \
      Insert(__FILE__, std::string(#val1) + #operator+ #val2, \
             __LINE__,((val1) operator(val2)));               \
  }

#define EXPECT_EQ(val1, val2) EXPECT_OP(val1, val2, ==)
#define EXPECT_NE(val1, val2) EXPECT_OP(val1, val2, !=);
#define EXPECT_GE(val1, val2) EXPECT_OP(val1, val2, >=);
#define EXPECT_GT(val1, val2) EXPECT_OP(val1, val2, >);
#define EXPECT_LE(val1, val2) EXPECT_OP(val1, val2, <=);
#define EXPECT_LT(val1, val2) EXPECT_OP(val1, val2, <);
#define EXPECT(condition) EXPECT_EQ(condition, true)

#endif  // TEST_UTEST_FRAMEWORK_SIMPLE_UNIT_TEST_H_

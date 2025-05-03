#ifndef __COMMON_TEST_H__
#define __COMMON_TEST_H__

#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>
#include <string>
#include <unordered_set>

struct Tester {
    std::string m_name;
    uint m_line;
    Tester(const std::string &name, uint line) : m_name(name), m_line(line) {}
    Tester &Is(bool x, const std::string &msg = "") {
        if (!x) std::cout << "\033[31m" << "[      !OK ] " << m_name << ":" << m_line << " " << msg << "\033[0m" << std::endl;
        return *this;
    }
};

#define ASSERT_TRUE(x) Tester(__FILE__, __LINE__).Is((x), #x)
#define ASSERT_FALSE(x) Tester(__FILE__, __LINE__).Is(!(x), #x)
#define ASSERT_EQ(a, b) Tester(__FILE__, __LINE__).Is((a) == (b), #a " == " #b)
#define ASSERT_NE(a, b) Tester(__FILE__, __LINE__).Is((a) != (b), #a " != " #b)
#define ASSERT_LT(a, b) Tester(__FILE__, __LINE__).Is((a) < (b), #a " < " #b)
#define ASSERT_LE(a, b) Tester(__FILE__, __LINE__).Is((a) <= (b), #a " <= " #b)
#define ASSERT_GT(a, b) Tester(__FILE__, __LINE__).Is((a) > (b), #a " > " #b)
#define ASSERT_GE(a, b) Tester(__FILE__, __LINE__).Is((a) >= (b), #a " >= " #b)
#define ASSERT_NEAR(a, b, c) Tester(__FILE__, __LINE__).Is(std::abs((a) - (b)) < (c), #a " ~= " #b)

class RegisterTest {
public:
    static RegisterTest *GetInstance() {
        static RegisterTest instance;
        return &instance;
    }

    void Register(const std::string &name, void (*test)()) {
        if (!m_tests) m_tests = new std::vector<ContextTest>();
        m_tests->push_back(ContextTest{name, test});
    }

    bool RunAllTests() {
        if (!m_tests) return false;

        std::cout << "\033[34m" << "[ INFO     ] Available tests:" << "\033[0m" << std::endl;
        for (size_t i = 0; i < m_tests->size(); ++i) std::cout << "\033[32m" << "  [" << i << "] " << m_tests->at(i).name << "\033[0m" << std::endl;
        std::cout << "\033[32m" << "  [q] exit" << "\033[0m" << std::endl;
        std::cout << "\033[34m" << "=> Please enter a number or press [q] to exit: " << "\033[0m";

        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
			if(input == "q") return true;
			
            uint choice = std::stoi(input);
            if (choice >= 0 && choice < m_tests->size()) {
                RunTest(m_tests->at(choice));
            } else {
                std::cout << "\033[31m" << "[ ERROR    ] Invalid choice." << "\033[0m" << std::endl;
                return false;
            }
        }else{
            for(auto test: *m_tests) RunTest(test);
        }

        return true;
    }

private:
    struct ContextTest {
        std::string name;
        void (*test)();
    };

    uint GetTime() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

    void RunTest(const ContextTest &test) {
        std::cout << "\033[32m" << "[ RUN      ] " << test.name << "\033[0m" << std::endl;
        uint start_time = GetTime();
        test.test();
        std::cout << "\033[32m" << "[     PASS ] " << test.name << " (" << (GetTime() - start_time) << " ms)" << "\033[0m" << std::endl;
        std::cout << "\033[32m" << "[=======================================================================]" << "\033[0m" << std::endl;
    }

    std::vector<ContextTest> *m_tests;
};

#define TEST(base, name) struct base##name##_Test { base##name##_Test() { RegisterTest::GetInstance()->Register(#base "." #name, &base##name##_Test::Run); } static void Run(); }; base##name##_Test g_##base##name##_Test; void base##name##_Test::Run()
#define RUN_ALL_TESTS() RegisterTest::GetInstance()->RunAllTests()

#endif // __COMMON_TEST_H__
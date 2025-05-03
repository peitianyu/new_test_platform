#ifndef __COMMON_BACKTRACE_H__
#define __COMMON_BACKTRACE_H__

#include <execinfo.h>
#include <signal.h>
#include <cxxabi.h>
#include <iomanip>

static void PrintTrace(int sig) {
    void *array[50];
    size_t size = backtrace(array, 50);
    char **messages = backtrace_symbols(array, size);

    std::cout << "\033[31m------------------*** Error: signal " << sig << "***------------------" << std::endl;
    for (uint i = 1; i < size && messages != NULL; ++i) {
        char *mangled_name = 0, *offset_begin = 0, *offset_end = 0;
        for (char *p = messages[i]; *p; ++p){
            if (*p == '(') mangled_name = p;
            else if (*p == '+') offset_begin = p;
            else if (*p == ')') { offset_end = p;  break; }
        }

        if (mangled_name && offset_begin && offset_end && mangled_name < offset_begin){
            *mangled_name++ = '\0';
            *offset_begin++ = '\0';
            *offset_end++ = '\0';

            int status;
            char *real_name = abi::__cxa_demangle(mangled_name, 0, 0, &status);

            std::string str = "["+std::to_string(i)+"] " + offset_begin;
            if(str.size() < 15) str.append(15-str.size(), ' ');
            std::string str1 = messages[i];
            if(str1.size() < 35) str1.append(35-str1.size(), ' ');
            std::cout << "\033[33m" << str << offset_end << "[" << str1 << "]:" << (status ? mangled_name : real_name) << std::endl;

            free(real_name);
        }
        else{ std::cout << "\033[33m" << "[" << i << "] " << messages[i] << std::endl;}
    }

    free(messages);
    exit(1);
}

#define REGISTER_SEGFAULT_HANDLER do {  \
    signal(SIGSEGV, PrintTrace);        \
    signal(SIGINT, PrintTrace);         \
    signal(SIGABRT, PrintTrace);        \
    signal(SIGFPE, PrintTrace);         \
    signal(SIGILL, PrintTrace);         \
    signal(SIGBUS, PrintTrace);         \
    signal(SIGQUIT, PrintTrace);        \
    signal(SIGUSR1, PrintTrace);        \
    signal(SIGUSR2, PrintTrace);        \
} while(0);

#endif // __COMMON_BACKTRACE_H__
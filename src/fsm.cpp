#include "fsm.h"

std::string demangle(const char *mangled_name)
{
    int status = 0;
    char *demangled = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
    std::string result(demangled ? demangled : mangled_name);
    free(demangled);
    return result;
}
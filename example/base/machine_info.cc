#include <iostream>

#include "base/machine_info.h"

int main()
{
    std::cout << "      # cpus = " << machine_info::num_cpus() << std::endl;
    std::cout << "total memory = " << machine_info::system_total_memory() << std::endl;
    std::cout << "  memory res = " << machine_info::memory_resident() << std::endl;

    return 0;
}

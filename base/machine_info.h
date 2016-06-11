#ifndef BASE_MACHINE_INFO_H_
#define BASE_MACHINE_INFO_H_

#include <cstdint>

namespace machine_info {

// Returns the number of installed cpus.
int num_cpus();

// Returns system installed memory. Returns 0 if failed to take.
// The unit is byte.
std::int64_t system_total_memory();

// Returns memory amount which the current process is using. Returns 0 if failed to take.
// The unit is byte.
std::int64_t memory_resident();

} // namespace machine_info

#endif // BASE_MACHINE_INFO_H_

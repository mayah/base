#include "base/machine_info.h"

#include <stdio.h>
#include <sys/types.h>

#include "base/build_config.h"
#include "base/file/file.h"
#include "third_party/glog/glog/logging.h"

#ifdef OS_LINUX
#   include <unistd.h>
#endif

#ifdef OS_MACOSX
#   include <libproc.h>
#   include <sys/sysctl.h>
#   include <sys/proc_info.h>
#endif

#ifdef OS_WIN
#   include <psapi.h>
#   include <windows.h>
#   include "base/file/scoped_fd.h"
#endif

namespace machine_info {

#ifdef OS_LINUX

int num_cpus()
{
    int cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (cpus < 0) {
        PLOG(ERROR) << "sysconf(_SC_NPROCESSORS_ONLN) failed";
        return 0;
    }

    return cpus;
}

std::int64_t system_total_memory()
{
    const std::int64_t page_size = sysconf(_SC_PAGESIZE);
    if (page_size < 0) {
        PLOG(ERROR) << "sysconf(_SC_PAGESIZE) failed";
        return 0;
    }

    const std::int64_t num_pages = sysconf(_SC_PHYS_PAGES);
    if (num_pages < 0) {
        PLOG(ERROR) << "sysconf(_SC_PHYS_PAGES) failed";
        return 0;
    }

    return page_size * num_pages;
}

std::int64_t memory_resident()
{
    // Reads /proc/self/statm
    // It contains something like the following line.
    // 5174 90 70 11 0 80 0
    // The second column is the number of pages for resident.

    const std::int64_t page_size = sysconf(_SC_PAGESIZE);
    if (page_size < 0) {
        PLOG(ERROR) << "sysconf(_SC_PAGESIZE) failed";
        return 0;
    }

    std::string buf;
    if (!file::read_file("/proc/self/statm", &buf)) {
        PLOG(ERROR) << "Failed to read /proc/self/statm";
        return 0;
    }

    int num_pages;
    if (sscanf(buf.c_str(), "%*d %d", &num_pages) != 1) {
        LOG(ERROR) << "Data from /proc/self/statm is not in expected form";
        return 0;
    }

    return num_pages * page_size;
}
#endif

#ifdef OS_MACOSX

int num_cpus()
{
    static const char* kCandidates[] = {
        "hw.logicalcpu_max", "hw.ncpu"
    };

    int size = 0;
    size_t len = sizeof(size);
    for (const auto& candidate : kCandidates) {
        if (sysctlbyname(candidate, &size, &len, nullptr, 0) == 0) {
            return size;
        }
    }

    // Failed for all candidates.
    LOG(ERROR) << "sysctlbyname for GetNumCPUs failed";
    return 0;
}

std::int64_t system_total_memory()
{
    std::int64_t size;
    size_t len = sizeof(size);

    if (sysctlbyname("hw.memsize", &size, &len, nullptr, 0) < 0) {
        PLOG(ERROR) << "sysctlbyname(hw.memsize) failed";
        return 0;
    }

    return size;
}

std::int64_t memory_resident()
{
    const pid_t pid = Getpid();

    struct proc_taskinfo taskinfo;
    int infosize = proc_pidinfo(pid, PROC_PIDTASKINFO, 0,
                                &taskinfo, sizeof(taskinfo));
    if (infosize < 0) {
        PLOG(ERROR) << "proc_pidinfo failed";
        return 0;
    }

    // According to this blog,
    // http://vinceyuan.blogspot.jp/2011/12/wrong-info-from-procpidinfo.html
    // we have to check proc_pidinfo returning value. Sometimes proc_pidinfo
    // returns too few bytes.
    if (infosize < sizeof(taskinfo)) {
        LOG(ERROR) << "proc_pidinfo returned too few bytes " << infosize
                   << " (expected " << sizeof(taskinfo) << ")";
        return 0;
    }

    return taskinfo.pti_resident_size;
}
#endif

#ifdef OS_WIN

int num_cpus()
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}

std::int64_t system_total_memory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    if (!GlobalMemoryStatusEx(&status)) {
        fprintf(stderr, "GlobalMemoryStatusEx failed: %d\n", GetLastError());
        return 0;
    }

    return status.ullTotalPhys;
}

std::int64_t memory_resident()
{
    DWORD process_id = GetCurrentProcessId();

    ScopedFd process(OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, process_id));
    if (!process.valid()) {
        PLOG(ERROR) << "OpenProcess failed";
        return 0;
    }

    PROCESS_MEMORY_COUNTERS pmc;
    if (!GetProcessMemoryInfo(process, &pmc, sizeof(pmc))) {
        PLOG(ERROR) << "GetProcessMemoryInfo failed";
        return 0;
    }

    return pmc.WorkingSetSize;
}

#endif

} // namespace machine_info

#include "executor.hpp"
#include <sys/stat.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

bool needs_rebuild(const std::string& target, const std::vector<std::string>& deps) {
    struct stat t_stat;
    if (stat(target.c_str(), &t_stat) != 0) return true;

    for (const auto& dep : deps) {
        struct stat d_stat;
        if (stat(dep.c_str(), &d_stat) == 0) {
            if (d_stat.st_mtime > t_stat.st_mtime) return true;
        }
    }

    return false;
}

void execute_if_needed(const std::string& target, const Rule& rule) {
    if (!needs_rebuild(target, rule.dependencies)) {
        std::cout << "[smake] " << target << " is up to date.\n";
        return;
    }

    for (const auto& cmd : rule.commands) {
        std::cout << "[smake] Running: " << cmd << "\n";
        int res = system(cmd.c_str());
        if (res != 0) {
            std::cerr << "[smake] Command failed: " << cmd << "\n";
            exit(1);
        }
    }
}

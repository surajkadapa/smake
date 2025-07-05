#pragma once
#include <unordered_map>
#include <vector>
#include <string>

struct Rule {
    std::string target;
    std::vector<std::string> dependencies;
    std::vector<std::string> commands;
};

using RuleMap = std::unordered_map<std::string, Rule>;

RuleMap parse_smakefile(const std::string& filename);
std::vector<std::string> topo_sort(const RuleMap& rules, const std::string& target);
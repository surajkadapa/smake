#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <stack>

RuleMap parse_smakefile(const std::string& filename){
    RuleMap rules;
    std::ifstream file(filename);
    std::string line, current_target;

    while(std::getline(file, line)){
        if(line.empty()) continue;

        //target line
        if(line[0] != ' ' &&  line[0] != '\t'){
            std::istringstream iss(line);
            std::string target;

            std::getline(iss, target, ':');

            std::string dep;
            Rule rule;

            rule.target = target;
            while(iss >> dep){
                if(dep.back() == ':') dep.pop_back();
                rule.dependencies.push_back(dep);
            }

            current_target = target;
            rules[target] = rule;
        }else{
            if(!current_target.empty()){
                rules[current_target].commands.push_back(line.substr(4));
            }
        }
    }
    return rules;
}

bool dfs(const std::string& node, const RuleMap& rules, 
    std::unordered_set<std::string>& visited,
    std::unordered_set<std::string>& on_stack,
    std::vector<std::string>& result) {

    if (on_stack.count(node)) return false; //this is for cycle detection
    if (visited.count(node)) return true;

    visited.insert(node);
    on_stack.insert(node);

    for (const std::string& dep : rules.at(node).dependencies) {
        if (rules.find(dep) != rules.end()) {
            if (!dfs(dep, rules, visited, on_stack, result))
                return false;
        }
    }

    result.push_back(node);
    on_stack.erase(node);
    return true;
}

std::vector<std::string> topo_sort(const RuleMap& rules, const std::string& target) {
    std::vector<std::string> result;
    std::unordered_set<std::string> visited, on_stack;

    if (!dfs(target, rules, visited, on_stack, result))
        return {};

    std::reverse(result.begin(), result.end());
    return result;
}
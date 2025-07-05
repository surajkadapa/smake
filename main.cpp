#include "parser.hpp"
#include "executor.hpp"
#include <iostream>

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Usage: ./smake <target>" << std::endl;
        return 1;
    }

    std::string target = argv[1];
    auto rules = parse_smakefile("smakefile");

    //checking if target given is present in the smakefile
    if(rules.find(target) == rules.end()){
        std::cerr << "Target not found in smakefile." << std::endl;
        return 1;
    }

    //checking for cycle
    auto sorted = topo_sort(rules, target);
    if(sorted.empty()){
        std::cerr << "Cycle detected or invalid graph." << std::endl;
        return 1;
    }

    //execute all the commands if needed
    for(std::string &tgt : sorted){
        execute_if_needed(tgt, rules[tgt]);
    }

    return 0;
}
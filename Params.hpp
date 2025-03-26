// Created by Murtaza & Yash on 2/14/2025.
#pragma once
#include "tools.hpp"

using namespace std;

class Params {
private:
    char* pathname;
    char* filename{};
    ofstream out;
    bool switches[4]{};
    string command;
    string wlist="";

public:
    Params(int argc,char *const argv[]);
    Params(const Params&) = delete; // Explicitly delete the copy constructor
    Params& operator=(const Params&) = delete; // Explicitly delete copy assignment
    Params(Params&&) = default; // Allow move constructor
    Params& operator=(Params&&) = default; // Allow move assignment
    void print();
    bool isCaseInSensitive() const {return switches[1];}
    bool isVerbose()const {return switches[0];}
    string getWlist()const {return wlist;}
    string getPathName() const {
        return pathname;
    }
    ofstream getOfstream(){return move(out);}
};

inline void usage() {
    printf("\nUsage: options [-vo] [--verbose] [--ignore]\n"
    "\t\t [--output filename] [--dir path] \n");
}

// Created by Murtaza & Yash on 2/14/2025
#include "Params.hpp"
#include "tools.hpp"
#include "Sniff.hpp"

int main(int argc, char* argv[]) {
    banner();

    Params param(argc,argv);
    param.print();
    Sniff sniff(move(param));
    sniff.oneDir();

    bye();
    return 0;
}
//File: Printer.hpp
//Name: Murtaza & Yash
// ------------------------------------
#pragma once
#include "tools.hpp"
//------------------------------------------------------------
//Singleton Class for printing to the file and terminal output
//____________________________________________________________
class Printer {
private:
    Printer()=default;
    ~Printer();
    ofstream file;
    static Printer instance; //instance
public:
    static void getControl(ofstream out){ instance.file = move(out); }
    static void write(const string& message , ostream& out); //write to the file and defined ostream
    static void writeln(const string& message , ostream& out); //write to the file and defined ostream
};

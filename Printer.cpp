// File: Printer.cpp
// Name: Murtaza & Yash
//  ------------------------------------
#include "tools.hpp"
#include "Printer.hpp"

Printer Printer::instance;
//------------------------------------------------------------------------
// Printing function where it prints messages to file and terminal--------
//------------------------------------------------------------------------
void Printer::write(const string &message, ostream &out)
{
    out << message;
    instance.file << message;
}

void Printer::writeln(const string &message, ostream &out)
{
    out << message << '\n';
    instance.file << message << '\n';
}

//-------------------------------------------------
// Destructor that closes test print file  --------
//-------------------------------------------------
Printer::~Printer()
{
    instance.file.close();
}

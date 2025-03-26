#pragma once
#include "tools.hpp"
#include "Params.hpp"
#include "FileID.hpp"
#include "Printer.hpp"

class Sniff{
private:
  Params param;
  string dirName; //name of the file
  string pathName; //name of the path
  vector<string> unpackWords;
  vector<FileID> susFiles;
  struct dirent *entry;

public:
  Sniff(Params param);
  void oneDir();
  FileID oneFile();
};

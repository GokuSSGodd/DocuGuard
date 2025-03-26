#pragma once
#include "tools.hpp"

using namespace std;

class FileID {
private:
    string fileName;
    int iNode;
    string pathName;
    vector<string> sniffWordsArr;
    bool flag;
public:
  FileID(string fileName, int iNodeNumber, string pathName);
  void print(ostream& out);
  void insertSniffWord(string& sniffWord);
  bool flagStatus(){return flag;}
};

inline ostream& operator<<(ostream& out, FileID& fileID) {
  fileID.print(out);
  return out;
}
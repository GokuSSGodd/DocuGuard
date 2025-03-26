#include "FileID.hpp"
#include "Printer.hpp"

FileID::FileID(string fileName, int iNode, string pathName):fileName(fileName),iNode(iNode),pathName(pathName){
}

void FileID::print(ostream& out){
  Printer::writeln(to_string(iNode), out);
  Printer::writeln(pathName, out);
}

void FileID::insertSniffWord(string& sniffWord){
  flag = false;
  int cnt = count(sniffWordsArr.begin(), sniffWordsArr.end(), sniffWord);
  if (cnt <= 0){
    sniffWordsArr.push_back(sniffWord);
  }
  else{
    Printer::write(sniffWord + " is already in there\n", cout);
    flag=true;
  }
}


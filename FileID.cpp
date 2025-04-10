#include "FileID.hpp"
#include "Printer.hpp"

FileID::FileID(string fileName, int iNode, string pathName):fileName(fileName),iNode(iNode),pathName(pathName), flag(false){
}

void FileID::print(ostream& out){
  Printer::writeln(to_string(iNode), out);
  Printer::writeln(pathName, out);
}

void FileID::insertSniffWord(string& sniffWord, bool isSensitive){
  int cnt{};
  if(!isSensitive)
    cnt = count(sniffWordsArr.begin(), sniffWordsArr.end(), sniffWord);
  else{
    for(string str: sniffWordsArr)
      if(caseInsensitiveEquals(sniffWord , str))
        cnt++;
  }
  if (cnt <= 0){
    sniffWordsArr.push_back(sniffWord);
    Printer::writeln(sniffWord+" was successfully added to sniffWordArr",cout);
  }
  else{
    Printer::write(sniffWord + " is already in there\n", cout);
    flag=true;
  }
}


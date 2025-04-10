#include "Sniff.hpp"

string getCWD(){
  const size_t size=1024;
  char cwd[size]{};
  getcwd(cwd, size);
  return string(cwd);
}

Sniff::Sniff(Params params): param(std::move(params)) {
  string word;
  istringstream instr(param.getWlist());
  while(!instr.eof()) {
    instr >> word;
    unpackWords.push_back(word);
  }
  Printer::getControl(std::move(param.getOfstream()));
  dirName ="./";
  pathName = param.getPathName();
}



void Sniff::oneDir(){
  DIR* dir = opendir(dirName.c_str()); //opening the the current working directory
  if(!dir){
    cerr<<"Error: Unable to open directory "<<dirName<<endl;
    return;
  }

  string cwd = getCWD();
  //skipping the dir 2 times
  readdir(dir); readdir(dir);
  //Runs till entry is not null
  while((entry = readdir(dir))){
   string filename = string(entry->d_name);
   string fullPath = pathName+"/"+filename;
   struct stat fileStat;
    if (stat(fullPath.c_str(), &fileStat) == -1) {
      std::cerr << "Error reading file stats: " << filename << std::endl;
      continue;
    }
    bool is_Dir=S_ISDIR(fileStat.st_mode), is_Reg=S_ISREG(fileStat.st_mode);
    if(param.isVerbose()&&(is_Dir||is_Reg))
      Printer::writeln(filename,cout);
    if(is_Dir){
      run(filename);
    }
    else if(S_ISREG(fileStat.st_mode)){
      FileID fileId = oneFile();
      if(fileId.flagStatus()){
        susFiles.push_back(fileId);
        Printer::writeln(string(entry->d_name)+" with the sniffword was added to the susFiles list",cout);
      }
    }
  }
  closedir(dir);
}


FileID Sniff::oneFile(){
  string pathname = getCWD();
  FileID fileID(string(entry->d_name),entry->d_ino, pathname);
  ifstream inputFile(string(entry->d_name));
  //cout<<"Path Name: "<<pathName<<string(entry->d_name)<<endl;
  if (!inputFile.is_open()) {//we can work on it later since your busy
    cerr << "Error opening file: " << pathName << endl;
    return fileID;  // Return empty or partially filled FileID object
  }
  string sniffword;
  while(inputFile >> sniffword){
    sniffword.erase(remove_if(sniffword.begin(), sniffword.end(), [](char c) {return !isalpha(c); }), sniffword.end());
    for(int i = 0; i < unpackWords.size(); i++){
      if(param.isCaseInSensitive() && caseInsensitiveEquals(sniffword , unpackWords[i]))
        fileID.insertSniffWord(sniffword, true);
      else if(sniffword == unpackWords[i]) fileID.insertSniffWord(sniffword, false);
    }
  }
  inputFile.close();
  return fileID;
}

void Sniff::run(string& name){
    //dirName = name;
   // pathName = name;
    travel(name);
    Printer::writeln("\n\nResults of travel: ", cout );
    for(FileID fileID : susFiles){
      Printer::writeln("---------------------------------------------",cout);
      cout << fileID;
      Printer::writeln("---------------------------------------------",cout);
      vector<string> vec = fileID.getSniffWords();
      for(string word : vec) Printer::writeln(word,cout);
    }
}

void Sniff::travel(string& dirname){
  chdir(dirname.c_str());
  string cwd = getCWD();
  Printer::writeln( "Visiting: "+ cwd , cout);
  DIR* dir = opendir("./"); //opening the the current working directory
  if(!dir){
    cerr<<"Error: Unable to open directory "<<dirName<<endl;
    return;
  }
  readdir(dir); readdir(dir);
  while((entry = readdir(dir))){
   string filename = string(entry->d_name);
   struct stat fileStat;
    if (stat(filename.c_str(), &fileStat) == -1) {
      std::cerr << "Error reading file stats: " << filename << std::endl;
      continue;
    }
    bool is_Dir=S_ISDIR(fileStat.st_mode), is_Reg=S_ISREG(fileStat.st_mode);
    if(is_Dir) {
      //string parameter = string(entry->d_name) + "/" + dirName;
      travel(filename);
    }
    else if(S_ISREG(fileStat.st_mode)){
      FileID fileId = oneFile();
      if(fileId.flagStatus()){
        susFiles.push_back(fileId);
        Printer::writeln(string(entry->d_name)+" with the sniffword was added to the susFiles list",cout);
      }
    }
  }
  closedir(dir);
  chdir("../");
}

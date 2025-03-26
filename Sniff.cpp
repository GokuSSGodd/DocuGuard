#include "Sniff.hpp"

Sniff::Sniff(Params params): param(std::move(params)) {
  string word;
  istringstream instr(param.getWlist());
  while(!instr.eof()) {
    instr >> word;
    unpackWords.push_back(word);
  }
  dirName = param.getDirName();
  pathName = param.getPathName();
}

void Sniff::oneDir(){
  DIR* dir = opendir(dirName.c_str()); //opening the directory
  if(!dir){
    cerr<<"Error: Unable to open directory "<<dirName<<endl;
    return;
  }
  const size_t size=1024;
  char cwd[size]{};
  if(getcwd(cwd, size))
    Printer::writeln("Current working directory: "+string(cwd),cout);
  else{
    Printer::writeln("Unable to get current working directory",cerr);
    return;
  }
  //skipping the dir 2 times
  readdir(dir);
  readdir(dir);
  //Runs till entry is not null
  while((entry = readdir(dir))){
   string filename = string(entry->d_name);
   string fullPath = pathName+"/"+dirName+"/"+filename;
   struct stat fileStat;
    if (stat(fullPath.c_str(), &fileStat) == -1) {
      std::cerr << "Error reading file stats: " << filename << std::endl;
      continue;
    }
    bool is_Dir=S_ISDIR(fileStat.st_mode), is_Reg=S_ISREG(fileStat.st_mode);
    if(param.isVerbose()&&(is_Dir||is_Reg))
      Printer::writeln(filename,cout);
    if(is_Dir){
      //Nothing at the moment
      //Wait for Program 4
    }
    else if(S_ISREG(fileStat.st_mode)){
      FileID fileId = oneFile();
      if(fileId.flagStatus()) susFiles.push_back(fileId);
    }
  }
  closedir(dir);
}

FileID Sniff::oneFile(){
  FileID fileID(string(entry->d_name),entry->d_ino, pathName);
  ifstream inputFile(pathName);
  if (!inputFile.is_open()) {//we can work on it later since your busy
    cerr << "Error opening file: " << pathName << endl;
    return fileID;  // Return empty or partially filled FileID object
  }
  string sniffword;
  while(inputFile >> sniffword){
    sniffword.erase(remove_if(sniffword.begin(), sniffword.end(), [](char c) {return !isalpha(c); }), sniffword.end());
    if(param.isCaseInSensitive()) transform(sniffword.begin(), sniffword.end(), sniffword.begin(), ::tolower);
  	for(int i = 0; i < unpackWords.size(); i++){
    	if(sniffword == unpackWords[i]) fileID.insertSniffWord(sniffword);
  	}
  }
  inputFile.close();
  return fileID;
}



#include "Sniff.hpp"

Sniff::Sniff(Params params): param(std::move(params)) {
  string word;
  istringstream instr(param.getWlist());
  while(!instr.eof()) {
    instr >> word;
    unpackWords.push_back(word);
  }
  Printer::getControl(move(param.getOfstream())); 
  dirName ="./";
  pathName = param.getPathName();
}

void Sniff::oneDir(){
  DIR* dir = opendir(dirName.c_str()); //opening the the current working directory
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
      //Nothing at the moment
      //Wait for Program 4
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
  FileID fileID(string(entry->d_name),entry->d_ino, pathName);
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



#include "Sniff.hpp"

Sniff::Sniff(Params params) : param(std::move(params))
{
  string word;
  istringstream instr(param.getWlist());
  while (!instr.eof())
  {
    instr >> word;
    unpackWords.push_back(word);
  }
  Printer::getControl(move(param.getOfstream()));
  dirName = "./";
  pathName = param.getPathName();
}

void Sniff::oneDir()
{

  DIR *dir = opendir(dirName.c_str()); // opening the the current working directory
  if (!dir)
  {
    cerr << "Error: Unable to open directory " << dirName << endl;
    return;
  }
  const size_t size = 1024;
  char cwd[size]{};
  if (getcwd(cwd, size))
    Printer::writeln("Current working directory: " + string(cwd), cout);
  else
  {
    Printer::writeln("Unable to get current working directory", cerr);
    return;
  }
  // skipping the dir 2 times
  readdir(dir);
  readdir(dir);
  // Runs till entry is not null
  while ((entry = readdir(dir)))
  {
    string filename = string(entry->d_name);
    string fullPath = pathName + "/" + filename;
    struct stat fileStat;
    if (stat(fullPath.c_str(), &fileStat) == -1)
    {
      std::cerr << "Error reading file stats: " << filename << std::endl;
      continue;
    }
    bool is_Dir = S_ISDIR(fileStat.st_mode), is_Reg = S_ISREG(fileStat.st_mode);
    if (param.isVerbose() && (is_Dir || is_Reg))
      Printer::writeln(filename, cout);
    if (is_Dir)
    {
      // Nothing at the moment
      // Wait for Program 4
    }
    else if (S_ISREG(fileStat.st_mode))
    {
      FileID fileId = oneFile();
<<<<<<< HEAD
      if (fileId.flagStatus())
      {
        susFiles.push_back(fileId);
        Printer::writeln(string(entry->d_name) + " with the sniffword was added to the susFiles list", cout);
      }
    }
  }
  closedir(dir);
}

FileID Sniff::oneFile()
{
  FileID fileID(string(entry->d_name), entry->d_ino, pathName);
<<<<<<< HEAD
  ifstream inputFile(string(entry->d_name));
  // cout<<"Path Name: "<<pathName<<string(entry->d_name)<<endl;
  == == == =
               ifstream inputFile(pathName);
>>>>>>> b62ac9c38d506919ac5678de217df1c56c1bd505
  if (!inputFile.is_open())
  { // we can work on it later since your busy
    cerr << "Error opening file: " << pathName << endl;
    return fileID; // Return empty or partially filled FileID object
  }
  string sniffword;
  while (inputFile >> sniffword)
  {
    sniffword.erase(remove_if(sniffword.begin(), sniffword.end(), [](char c)
                              { return !isalpha(c); }),
                    sniffword.end());
<<<<<<< HEAD

    for (int i = 0; i < unpackWords.size(); i++)
    {
      if (param.isCaseInSensitive() && caseInsensitiveEquals(sniffword, unpackWords[i]))
        fileID.insertSniffWord(sniffword, true);
      else if (sniffword == unpackWords[i])
        fileID.insertSniffWord(sniffword, false);
      == == == =
                   if (param.isCaseInSensitive()) transform(sniffword.begin(), sniffword.end(), sniffword.begin(), ::tolower);
      for (int i = 0; i < unpackWords.size(); i++)
      {
        if (sniffword == unpackWords[i])
          fileID.insertSniffWord(sniffword);
>>>>>>> b62ac9c38d506919ac5678de217df1c56c1bd505
      }
    }
    inputFile.close();
    return fileID;
  }

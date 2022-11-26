/**
1. Brynn McGovern
   2370579
   bmcgovern@chapman.edu
   CPSC 380-01
   Assignment 1 - File Status
2. A program to find and display file information including Inode number,
  file type, total size, date last modified, and the user who created it.
*/

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <iomanip>
#include <cerrno>
#include <cstring>
#include <pwd.h>
#include <stdlib.h>

using namespace std;

  struct stat fileInfo;
  struct tm dt;
  struct passwd *pws;

  void getInodeNum();
  void getFileType();
  void getUsername();
  void getTotalSize();
  void convertToDate();

/**
  getInodeNum()
  prints out file's Inode number
  @return void
*/

void getInodeNum(){
  cout << "Inode number" << "     : " << fileInfo.st_ino << endl;

}

/**
  getFileType()
  prints out file tyoe
  @return void
*/
void getFileType(){
  if((fileInfo.st_mode & S_IFMT) == S_IFDIR){
    cout << "File Type" << "        : Directory" << endl;
  }
  else{
    cout << "File Type" << "        : Regular file " << endl;
  }
}

/**
  convertToDate()
  prints out file's last modified date
  localtime() would print out in UTC timezone instead of PST, so I had to
  manually change it
  @return void
*/
void convertToDate(){

  char mtime[80];
  time_t t = fileInfo.st_mtime; 
  setenv("TZ", "GMT+7", 1);
  tzset();
  struct tm lt;
  localtime_r(&t, &lt);
  strftime(mtime, sizeof mtime, "Modified on      : %a, %d %b %Y %T", &lt);
  printf("%s\n", mtime);
  cout << endl;

}

/**
  getUsername()
  prints out username of who created the file
  @return void
*/
void getUsername(){
  pws = getpwuid(fileInfo.st_uid);
  cout << "User Name" << "        : " << pws->pw_name << endl;

}

/**
  getTotalSize()
  prints out file's size
  @return void
*/
void getTotalSize(){
  cout << "Total Size" << "       : " << fileInfo.st_size << endl;

}

/**
  main method
  checks for errors with command line input then prints out file information
*/
int main(int argc, char** argv){
  if(argc > 2){
    cout << "Error: Too many arguments." << endl;
    return(EXIT_FAILURE);

  }
  else{

    if(stat(argv[1], &fileInfo) != 0){
      cout << "Error: " << strerror(errno) << '\n';
      return(EXIT_FAILURE);
    }

      getInodeNum();
      getFileType();
      getUsername();
      getTotalSize();
      convertToDate();

  }
}

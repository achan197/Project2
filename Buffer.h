#ifndef BUFFER_H
#define BUFFER_H

#include <cstdlib>
#include <ncurses.h>
//#include <Editor.h>
#include <vector>
#include <string>

typedef unsigned int uint;

/**
* This class handles the editing
* and manipulation of the buffer
* of text passed in by the Editor
*/

class Buffer{

 public:

  //member variables
  WINDOW * win;
  uint row,col;
  std::vector<std::string> contents;
  uint cursorY, cursorX;

  //Constructors
  Buffer();
  Buffer(std::vector<std::string> &);
  Buffer(std::string);
  ~Buffer();

  //Cursor movement
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

  //Editing
  void insertCharacter(char);
  void deleteChracter();

  //Scrolling
  void nextLine();
  void prevLine();
  void nextPage();
  void prevPage();

  //Input
  void inputLoop();

  //test
  std::vector<std::string> readFile(std::string,std::vector<std::string> & contents);
};



#endif

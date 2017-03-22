#ifndef BUFFER_H
#define BUFFER_H

#include <cstdlib>
#include <ncurses.h>
#include <Editor.h>
#include <vector>

typedef unsigned int uint;

/**
* This class handles the editing
* and manipulation of the buffer
* of text passed in by the Editor
*/
class Buffer{

  //member variables
  WINDOW * win;
  uint row,col;
  std::vector<char> contents;
  uint cursorY, cursorX;

  //Constructor
  Buffer(const std::vector);
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

}

#endif

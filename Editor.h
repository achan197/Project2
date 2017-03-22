#ifndef EDITOR_H
#define EDITOR_H

#include <cstdlib>
#include <ncurses.h>
#include <vector>
#include <string>

/**
* This class will handle the non-text
* elements of the editor like the menu,
* file i/o, and printing status information
* to the screen for the user. Will encapsulate
* the text buffer itself.
*/

typedef unsigned int uint;

class Editor{
  uint row,col; //The height and width of the entire terminal
  WINDOW * win; //the editor window itself
  Buffer * buff; //The buffer containing the text
  std::string filename,quitText,saveText; //string menu info

  //Constructors
  Editor(const std::string);
  ~Editor();

  //File IO
  int readFile(std::string);
  int writeFile(Buffer *);
  void openBuffer(std::vector);

  void updateMenu();
  void createWindow();

}

#endif

#include <cstdlib>
#include <fstream>
#include <string>
#include "./Buffer.h"
#include <vector>

typedef unsigned int uint;

using std::vector;
using std::string;

/**
* Constructors / Deconstructor
**/

/*
  Default Constructor
*/
Buffer::Buffer(){

  getmaxyx(stdscr,this->row,this->col);

  this->cursorY = 2;
  this->cursorX = 2;

  this-> win = newwin(row-5,col,0,0);

  keypad(this->win, TRUE);

  box(this->win,0,0);
  wrefresh(this->win);

  mvwaddstr(this->win,0,(col/2)-4,"  Text Editor  ");

  wmove(this->win,this->cursorY,this->cursorX);
  inputLoop();
}

/*
  Vector Constructor
*/
Buffer::Buffer(vector<string> & contents){

  this->contents = contents;

  getmaxyx(stdscr,this->row,this->col);

  this->cursorY = 2;
  this->cursorX = 2;

  this->win = newwin(row-5,col,2,0);

  //Print vector to the window
  for (uint i = 0; i < (row-6); ++i) {

    if(i < contents.size()-1){
      mvwaddstr(this->win,i+2,2,contents[i].c_str());
      wrefresh(this->win);
    }

  }

  box(this->win,0,0);
  mvwaddstr(this->win,0,(col/2)-4,"  Text Editor  ");
  wrefresh(this->win);
  wmove(this->win,cursorY,cursorX);
  inputLoop();
}

/*
* File name constructor NOTE// This should be removed before final build
*/
Buffer::Buffer(string filename){
  vector<string> info;
  this->contents = readFile(filename,info);

  getmaxyx(stdscr,this->row,this->col);

  this->cursorY = 2;
  this->cursorX = 2;

  this->win = newwin(row-5,col,2,0);

  //Print vector to the window
  for (uint i = 0; i < (row-6); ++i) {
    if(i < contents.size()-1){
      mvwaddstr(this->win,i+2,2,contents[i].c_str());
      wrefresh(this->win);
    }
  }

  box(this->win,0,0);
  mvwaddstr(this->win,0,(col/2)-4,"  Text Editor  ");
  wrefresh(this->win);
  wmove(this->win,cursorY,cursorX);
  inputLoop();
}

/*
  Deconsturctor
*/
Buffer::~Buffer(){
  delwin(this->win);
}


/*
* Arrow Key movement functions
*/
void Buffer::moveUp(){
  if(this->cursorY-1 != 0){
    --this->cursorY;
    wmove(this->win,this->cursorY,this->cursorX);
    wrefresh(this->win);
  }
}

void Buffer::moveDown(){
  if(this->cursorY+1 < this->row-6){
    ++this->cursorY;
    wmove(this->win,this->cursorY,this->cursorX);
    wrefresh(this->win);
  }
}

void Buffer::moveRight(){
  if(this->cursorX+1 < col- 1){
    ++this->cursorX;
    wmove(this->win,this->cursorY,this->cursorX);
    wrefresh(this->win);
  }
}

void Buffer::moveLeft(){
  if(this->cursorX-1 > 2){
    --this->cursorX;
    wmove(this->win,this->cursorY,this->cursorX);
    wrefresh(this->win);
  }

}

/*
* Insertion Character //Needs work
*/
void Buffer::insertCharacter(char ch){
  string str = this->contents[cursorY];
  str.insert(str.begin()+cursorX,ch);
}

void deleteCharacter(){

}

void Buffer::inputLoop(){

  const int EXIT_CHAR = 'q';
  int ch;

    while(ch!=EXIT_CHAR){

    ch = wgetch(this->win);

    switch(ch){

    case KEY_DOWN:
      moveDown();
      wrefresh(this->win);
      break;

    case KEY_UP:
      moveUp();
      break;

    case KEY_RIGHT:
      moveRight();
      break;

    case KEY_LEFT:
      moveLeft();
      break;

    case EXIT_CHAR:
      break;

    default:
      insertCharacter(ch);
      break;

    } // switch
  } // while
}

//Remove this function before final build //handled by editor class
vector<string> Buffer::readFile(string filename,vector<string> &  contents){

  std::ifstream file;
  file.open(filename);

  string line;

  while(!file.eof()){
    getline(file,line);
    contents.push_back(line);
  }

  return contents;

}

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ncurses.h>

using namespace std;

typedef unsigned int uint;

void endCurses();
void startCurses();
void run(string);
vector<string> readFile(string,vector<string> &);
void readNextPage(vector<string> &,uint &);
void readPrevPage(vector<string> &, uint &);

//Lab 07 text reader
int main(int argc, const char * argv[])
{
  startCurses();
  string filename;

  if(argc == 2){
    filename = argv[1];
  } else {
    endwin();
    cout << "Please only inlcude one filename as an argument" << endl;
    exit(EXIT_FAILURE);
  }
  run(filename);
  endCurses();
}

void endCurses(){
  endwin();
}

/*
  Starts Curses
*/
void startCurses()
{
  initscr();
  noecho();
  curs_set(0);
  cbreak();
  keypad(stdscr,true);
}

/*
  Main Loop arrow key functionality
*/
void run(string filename)
{
  vector<string> text;
  uint row,col;
  getmaxyx(stdscr,row,col);
  text = readFile(filename,text);
  uint position = 0;
  int ch;
  readNextPage(text,position);
    while(ch!='q'){
      ch = getch();

      switch(ch)
       {
      case KEY_DOWN:
	if(position < text.size()-1){
	  readNextPage(text,position);
	}
	break;

      case KEY_UP:
	if(position >= (row-4) && position - 2*(row-8) >= 0){
	  readPrevPage(text,position);
	}
	break;

      case 'q':
	break;

      default:
	break;
      }
    }
}

/*
  Reads the file into a vector
*/
vector<string> readFile(string filename,vector<string> &  contents){

  ifstream file;
  file.open(filename);

  string line;

  while(!file.eof()){
    getline(file,line);
    contents.push_back(line);
  }

  return contents;

}

/*
  prints the next page of contents to the window based on the size of the terminal
*/
void readNextPage(vector<string> & contents, uint & position){
  uint row,col;
  getmaxyx(stdscr,row,col);
  clear();

  //wborder(stdscr,'|','|','-','-','+','+','+','+');

  //position -= (row-7);

  for(uint i = 4; i < (row-4); ++i){

    if(position <  contents.size()-1){
      mvaddstr(i,2,contents[position].c_str());
      refresh();
      ++position;
    }

  }

  mvprintw(row-2,2,"Press q to quit");
  mvprintw(1,2,"Navigate with up and down arrow keys");

}

/*
  prints the previous page of file contents to the window
  based on the size of the terminal.
  NOTE - this function is pretty redundant
*/
void readPrevPage(vector<string> & contents, uint & position){
  uint row,col;

  getmaxyx(stdscr,row,col);
  clear();

  //wborder(stdscr,'|','|','-','-','+','+','+','+');

  position -= (row-9);

  for(uint i = 4; i < (row-4); ++i){
    mvaddstr(i,2,contents[position].c_str());
    refresh();
    ++position;
  }

  mvprintw(row-2,2,"Press q to quit");
  mvprintw(1,2,"Navigate with up and down arrow keys");

}

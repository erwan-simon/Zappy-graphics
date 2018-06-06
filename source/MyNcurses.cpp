#include <ncurses.h>
#include "MyNcurses.h"

void	MyNcurses::OpenWindow(const int &x, const int &y)
{
  initscr();
  cbreak();
  noecho();
  timeout(0);
  keypad(stdscr, TRUE);
  start_color();
  use_default_colors();
  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(3, COLOR_RED, COLOR_RED);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(6, COLOR_GREEN, COLOR_GREEN);
  curs_set(0);
  this->win = newwin(y, x, 0, 0);
}

void	MyNcurses::RefreshWindow()
{
  refresh();
}

void	MyNcurses::ClearWindow()
{
  clear();
}

void	MyNcurses::CloseWindow()
{
  delwin(this->win);
  curs_set(1);
  endwin();
}

MyNcurses::e_key	MyNcurses::GetKey() const
{
  switch (getch()) {
  case KEY_LEFT:
    return (MyNcurses::E_LEFT);
  case KEY_RIGHT:
    return (MyNcurses::E_RIGHT);
  case KEY_UP:
    return (MyNcurses::E_UP);
  case KEY_DOWN:
    return (MyNcurses::E_DOWN);
  case 'x':
    return (MyNcurses::E_X);
  case '2':
    return (MyNcurses::E_2);
  case '3':
    return (MyNcurses::E_3);
  case '4':
    return (MyNcurses::E_4);
  case '5':
    return (MyNcurses::E_5);
  case '8':
    return (MyNcurses::E_8);
  case '9':
    return (MyNcurses::E_9);
  case 27:
    return (MyNcurses::E_ESC);
  }
  return (MyNcurses::E_NONE);
}

void	MyNcurses::BuildCell(const int &x, const int &y, const MyNcurses::e_color &col)
{
  attron(COLOR_PAIR(col));
  mvprintw(y, (x * 2), "OO");
  attroff(COLOR_PAIR(col));
}

void		MyNcurses::WriteStuff(const int &x, const int &y, const std::string &text)
{
  unsigned int	a = 0;

  while (a < text.size() * 2)
    {
      mvprintw(y, (x * 2) + a, "%c", text.at(a / 2));
      a += 2;
    }
}

#ifndef MYNCURSES_H_
# define MYNCURSES_H_

#include <string>
#include <ncurses.h>

class MyNcurses
{
public:
  typedef enum {
    E_BLACK,
    E_WHITE,
    E_YELLOW,
    E_RED,
    E_BLUE,
    E_PINK,
    E_GREEN
  } e_color;

  typedef enum {
    E_NONE = -1,
    E_LEFT = 0,
    E_RIGHT,
    E_UP,
    E_DOWN,
    E_X,
    E_2,
    E_3,
    E_4,
    E_5,
    E_8,
    E_9,
    E_ESC
  } e_key;
  
  MyNcurses() {};
  ~MyNcurses() {};
  
  // Window
  virtual void			OpenWindow(int x, int y);
  virtual void			RefreshWindow();
  virtual void			ClearWindow();
  virtual void			CloseWindow();
  virtual e_key			GetKey() const;

  // Draw
  virtual void			BuildCell(int x,
					  int y,
					  const e_color &col);
  virtual void			WriteStuff(int x,
					   int y,
					   const std::string& text);

private:
  WINDOW			*win;
};

#endif

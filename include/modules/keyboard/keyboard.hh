/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_KEYBOARD_
#define _QNX_AUDI_KEYBOARD_

class Keyboard
{
public:
  Keyboard();
  virtual ~Keyboard() = 0;

  virtual void init() = 0;
  virtual void dispose() = 0;

  const bool &isLeftPressed() const { return m_isLeftPressed; };
  const bool &isRightPressed() const { return m_isRightPressed; };
  const bool &isExitPressed() const { return m_isExitPressed; };

protected:
  bool m_isLeftPressed, m_isRightPressed, m_isExitPressed;
};

#endif
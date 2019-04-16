#include "Board3.h"

/*
  クラスの選択。

  BOARD_CLASSが適時読みかえられる。
*/

#if BOARD == 1
#define BOARD_CLASS Board
#elif BOARD == 2
#define BOARD_CLASS Board2
#elif BOARD == 3
#define BOARD_CLASS Board3
#else
#error "ERROR"
#endif

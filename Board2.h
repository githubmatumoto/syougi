/*
  Board2.h

  Set* の返り値の意味を増やした。
  ret = 0 : 失敗
  ret = 1 : 駒を置く事に成功した。但しEFFECTは増やしてない。
  ret = 2以上: 駒を置く事に成功し,それに加えてEFFECTの数をret-1個増やした
*/
#include "Board.h"

class Board2 : public Board {
public:
  int Set_Array_e(int array_e, KOMA c){
    int ret = 0;

    if(b[array_e] != EMPTY)
      return 0;

#ifdef IKIDOKORO_NASHI
    if(BOARD_NG[c][array_e])
      return 0;
#endif

    for(int i= 0; ; i++) {
      int j = KOMA_EFFECT[c][i];
      if(j==0)
	break;
      if(b[array_e+j] >= KOMA_START) // 駒が無いか?
	return 0;
    }
    /*成功*/

    b[array_e] = c; // 駒を設置。
    ret++;

    // 駒の影響個所に印
    for(int i = 0;; i++){
      int j = KOMA_EFFECT[c][i];
      if(j==0)
	  break;
      if(b[array_e+j]==EMPTY){
	ret++;
	b[array_e+j] = EFFECT;
      }
    }
    return ret;
  }

  // Virtual関数じゃないので、再定義の必要有り。
  int Set(int x, int y, KOMA c){return Set_Array_e(XY_to_Array_e(x, y), c);}
  int Set_Array(int array, KOMA c){return Set_Array_e(Array_to_Array_e(array), c);}
};

/*
  Board3.h

  Board2.hとの違いは駒を外すUnSetを実装。
  それのため、EFFECTの状態を2重/3重。。と重ねている。

  Class Boardを基本コピーしなくて良くなる。
*/
#include "Board2.h"

class Board3 : public Board2 {
public:
  

  int Set_Array_e(int array_e, KOMA c){
    int ret = 0;

    if(b[array_e] != EMPTY)
      return 0;


    if(flag_enable_rule_ikidokoro_nashi && BOARD_NG[c][array_e])
      return 0;


    for(int i= 0; ; i++) {
      int j = KOMA_EFFECT[c][i];
      if(j==0)
	break;
      if(b[array_e+j] >= KOMA_START) // 駒が無いか?
	return 0;
    }
    //成功

    b[array_e] = c; // 駒を設置。
    ret++;

    // 駒の影響個所に印
    for(int i = 0;; i++){
      int j = KOMA_EFFECT[c][i];
      if(j==0)
	  break;
      if(b[array_e+j]==EMPTY){
	ret++;
      }
      // EFFECTの状態を2重/3重。。と重ねている。
      b[array_e+j] += EFFECT;
    }
    return ret;
  }

  /*
  int Set_Array_e(int array_e, KOMA c){
    int ret = 0;

    if(b[array_e] != EMPTY)
      return 0;

    int i=0;
    for(; ; i++) {
      int j = KOMA_EFFECT[c][i];
      if(j==0)
	break;
      if(b[array_e+j]==EMPTY){
        ret++;
      }
      if(b[array_e+j] >= KOMA_START) // 駒が有った
	goto loopout;

      // EFFECTの状態を2重/3重。。と重ねている。
      b[array_e+j] += EFFECT;
    }
    //成功

    b[array_e] = c; // 駒を設置。
    ret++;

    return ret;

  loopout:
    // 駒の影響個所に印
    i--;
    for(;i>=0;i--){
      b[array_e + KOMA_EFFECT[c][i]] -= EFFECT;      
    }
    return 0;
    }*/

  // Virtual関数じゃないので、再定義の必要有り。
  int Set(int x, int y, KOMA c){return Set_Array_e(XY_to_Array_e(x, y), c);}
  int Set_Array(int array, KOMA c){return Set_Array_e(Array_to_Array_e(array), c);}

  void UnSet_Array_e(int array_e, KOMA c){
    int debug=0;

    if(debug){
      if(b[array_e] != c){
	cerr << "Bad UnSet_e() "<< endl;
	exit(1);
      }
    }

    b[array_e] = EMPTY; // 駒を外す。

    // 駒の影響個所のEFFECTをはずす。
    for(int i = 0;; i++){
      int j = KOMA_EFFECT[c][i];
      if(j==0)
	  break;

      if(debug){
	if(b[array_e+j] <= EMPTY){
	  cerr << "Bad UnSet_e()/ EMPTY "<< endl;
	  exit(1);
	}
      }
      b[array_e+j]--;
    }
  }

  void UnSet(int x, int y, KOMA c){UnSet_Array_e(XY_to_Array_e(x, y), c);}
  void UnSet_Array(int array, KOMA c){UnSet_Array_e(Array_to_Array_e(array), c);}
};

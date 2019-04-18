#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

#ifdef KANRYAKU
#ifndef GEN_GOTE
#error "ERROR: Please Set -DGEN_GOTE"
#endif
#endif

#ifndef MASU_LIMIT
#define MASU_LIMIT 0
#endif


#if IKIDOKORO_NASHI
// 廃止フラグ
#error "NG: -DIKIDOKORO_NASHI"
#endif


enum KOMA {
//飛車・角行・王将・香車・金将・銀将・桂馬・歩兵
  EMPTY = 0, // 
  EFFECT=1, // 駒の影響ある盤面
  /*
    class Board/ Borad2ではEFFECTは1の状態だけ。

    class Board3およびそれ以降では

    2の場合はEFFECTが２重にかかっている。
    3の場合はEFFECTが3重にかかっている。
              ....

    98の場合はEFFECTが98重にかかっている。

  */
#ifdef COUNT_KOMAITI
  KOMAITI_CHANGE = 99,
#endif

  KOMA_START = 100, // 駒の順番を変える可能性あるため、最初の駒
  HISYA=100, // 2枚
  KAKU=101, // 2枚
  OH=102, // 2枚
  KYOU=103, // 4枚
  KIN=104, // 4枚
  GIN=105, // 4枚
  KEI=106, // 4枚
  FU=107, // 18枚
  // 飛車, 角, 王は先手後手の区別無し。
  rKYOU = 108,
  rKIN = 109,
  rGIN = 110,
  rKEI = 111,
  rFU = 112,

  // 簡略タイプの駒
  TATE = 113,
  ISHI = 114,
  JYU = 115,
  KOMA_END=115 // 駒の順番を変える可能性あるため、最後の駒  
};

/* 拡張盤2

BANPEIのサイズを減らす。

何故か遅くなる。 */
//#define EXT_BAN_2

class Board {
public:
  static const int SIZE = 9; // 盤面の縦/横
  //static const int SIZE = 13; // 盤面の縦/横

  // 拡張盤のサイズ。盤面の外は(アルゴリズムで使う意味の)番兵。

#ifndef EXT_BAN_2
  static const int BANPEI_SIZE = SIZE-1; // 通常の盤面の外側にある番兵のサイズ
#else
  static const int BANPEI_SIZE = (int)SIZE/2;
#endif
  static const int OFFSET =  SIZE + BANPEI_SIZE + BANPEI_SIZE; // 9 + 8 + 8
  static const int OFFSETn2 = OFFSET*OFFSET;
  static const int XY_START_ARRAY_E= OFFSET * BANPEI_SIZE + BANPEI_SIZE;

  static char **KOMA_PRINT; // 印刷用文字列 init()で初期化/日本語まじり
  static char **KOMA_PRINT_ENG; // 印刷用文字列 init()で初期化/英字のみ。


  static int **KOMA_EFFECT; // 駒の動き init()で初期化
  static int64_t found_count; // 見付かった数
  static int best_koma_nokori; // 現時点で一番駒を置く事が出来た場合の、残りの駒数。

  // flagの初期化はBoard.ccの頭
  // 初期値を書き換えた場合はBoard.cの頭を書き換える。

  // true:英語表示, false:日本語表示(default)
  static bool flag_print_english; 

  // TODO: 実際に使うか検討。
  // true:後手の駒あり。false:後手なし(default)
  // ファイルの入力の時にチェックするだけ。内部的には常に有効
  static bool flag_enable_gote; 

  // true: 行き所の無い駒を反則とする. false:反則としない(default)
  static bool flag_enable_rule_ikidokoro_nashi; 

  static int BOARD_NG[KOMA_END+1][OFFSETn2];

  // classのstatic変数の初期化。
  static void init(void);

  // 拡張盤(Xe,Ye) ->  拡張盤(Array)へ変換
  static int XeYe_to_Array_e(int x_e, int y_e){
    return y_e * OFFSET + x_e;
  }

  // PC表現(X,Y) -> 拡張盤(Array)へ変換
  static int XY_to_Array_e(int x, int y){
    return XeYe_to_Array_e(x + BANPEI_SIZE, y + BANPEI_SIZE);
  }

  // PC表現(X,Y) -> PC表現(Array)へ変換
  static int XY_to_Array(int x, int y){
    return y * SIZE + x;
  }

  // PC表現(array) -> 拡張盤(Array)へ変換
  // TODO: 計算コストが高すぎる。
  static int Array_to_Array_e(int array){
    int y = array / SIZE;
    int x = array % SIZE;
    return XY_to_Array_e(x, y);
  }

  static int Array_to_X(int array){
    return array % SIZE;
  }
  static int Array_to_Y(int array){
    return array / SIZE;    
  }

  // 拡張盤(Array)
#ifndef EXT_BAN_2
  int b[OFFSETn2];
#else
  // 始点をずらすのでメモリをおおめに。
  int bb[OFFSETn2 + (SIZE-BANPEI_SIZE)*OFFSET*2];
  int *b;
#endif

  Board(void){
    // 通常盤の中はEMPTY、外の拡張盤は番兵代りのEFFECTで埋める。

#ifdef EXT_BAN_2
    if(SIZE <= BANPEI_SIZE){
      cerr << "ERROR" << endl;
    }
    // 始点をずらす。そのままだと飛車角がマイナス側ではみでる。
    b = bb + (SIZE-BANPEI_SIZE)*OFFSET;
    for(unsigned i = 0; i < sizeof(bb)/sizeof(int); i++)
      bb[i] = EFFECT;
#else
    for(int i = 0; i < OFFSETn2; i++)
      b[i] = EFFECT;
#endif

    for(int i = 0; i < SIZE; i++){
      for(int j = 0; j < SIZE; j++){
	b[XY_to_Array_e(i,j)] = EMPTY;
      }
    }
  }

  Board(const Board&x){
    //cout << "In constract"<<endl;

#ifdef EXT_BAN_2
    if(SIZE <= BANPEI_SIZE){
      cerr << "ERROR" << endl;
    }

    // 始点をずらす。そのままだと飛車角がマイナス側ではみでる。
    b = bb + (SIZE-BANPEI_SIZE)*OFFSET;
    for(unsigned i = 0; i < sizeof(bb)/sizeof(int); i++)
      bb[i] = x.bb[i];
#else
    for(int i = 0; i < OFFSETn2; i++)
      b[i] = x.b[i];
#endif
  }

  /*
    将棋の盤面の 
    「1一」はX=8, Y=8, 
    「1九」はX=0, Y=8, 
    「9一」はX=8, Y=0, 
    「9九」はX=0, Y=0, 
  */

  // 日本語まじり
  // 独自定義。

  // 英字のみ。
  // コンピュータ将棋のコマの標準的な表し方(?)
  // http://www2.computer-shogi.org/protocol/record_v2.html


  void Print(); // 盤面表示
  void Print_e(); // 拡張盤全体表示
  void PrintLine(); // 1行で盤面表示
  void PrintLine_e(); // 1行で拡張盤全体表示
  void PrintLast(int koma_nokori, int masu_nokori); // 盤面発見時の表示用
  void PrintLast_FuKei(int koma_nokori, int masu_nokori); // 歩と香をまじめに置いてない用

  /*
    ret = 0 : 駒を置く事に失敗した。
    ret = 1 : 駒を置く事に成功した。

    下位classでoverrideするのでvitual宣言。
  */

  int Set_Array_e(int array_e, KOMA c){
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
    /*成功*/

    b[array_e] = c; // 駒を設置。

    // 駒の影響個所に印
    for(int i = 0;; i++){
      int j = KOMA_EFFECT[c][i];
      if(j==0)
	  break;
      b[array_e+j] = EFFECT;
    }
    return 1;
  }

  int Set(int x, int y, KOMA c){return Set_Array_e(XY_to_Array_e(x, y), c);}
  int Set_Array(int array, KOMA c){return Set_Array_e(Array_to_Array_e(array), c);}

  KOMA Get(int x, int y){return (KOMA)b[XY_to_Array_e(x, y)];}
  KOMA Get_Array(int array){return (KOMA)b[Array_to_Array_e(array)];}
  KOMA Get_Array_e(int array_e){return (KOMA)b[array_e];}
};

static inline void PrintStep(Board &list, int step)
{
  //  asm("PRINT_STEP START:");
  static int step_count=0;
  static int step_count2 = 1;//最初に1回表示されるよう1.
  step_count2--;
  if(step_count2 == 0){
    step_count2 = step;
    step_count++;
    cout << "STEP: " << step_count << ", best_koma_nokori = " << Board::best_koma_nokori  << endl;
    list.Print();
    cout.flush();
  }
  //asm("PRINT_STEP END:");
}

#include "misc.h"


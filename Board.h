#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

using namespace std;

#ifndef MASU_LIMIT
#define MASU_LIMIT 0
#endif


// ここ変更したら Board::initを書き換える。
enum KOMA {
  EMPTY = 0, // 空きマス
  EFFECT=1, // 駒の影響あるマス
  /*
    class Board/ Borad2ではEFFECTは1の状態だけ。

    class Board3およびそれ以降では

    2の場合はEFFECTが２重にかかっている。
    3の場合はEFFECTが3重にかかっている。
              ....

    98の場合はEFFECTが98重にかかっている。

  */
  EFFECT_LAST= 98,

  // 大駒以外の移動検出用。 
  KOMAITI_CHANGE = 99,

  // 駒
  //飛車・角行・王将・香車・金将・銀将・桂馬・歩兵
  KOMA_START = 100, // 駒の順番を変える可能性あるため、最初の駒
  HISYA=100,    // "+HI", "飛", 2枚
  KAKU=101,     // "+KA", "角",  2枚
  OH=102,       // "+OU", "王", 2枚
  KYOU=103,     // "+KY", "香", 4枚
  KIN=104,      // "+KI", "金", 4枚
  GIN=105,      // "+GI", "銀", 4枚
  KEI=106,      // "+KE", "桂", 4枚
  FU=107,       // "+FU", "歩", 18枚
  // 飛車, 角, 王は先手後手の区別無し。
  // それ以外の駒の後手は当て字で表示する。
  rKYOU = 108,  // "-KY", "京", 後手/香
  rKIN = 109,   // "-KI", "琴", 後手/金
  rGIN = 110,   // "-GI", "吟", 後手/銀
  rKEI = 111,   // "-KE", "軽", 後手/桂
  rFU = 112,    // "-FU", "符", 後手/歩
  // 簡略タイプの駒。Ref: http://www.ktr.to/Game/Java/kaisetsu.html
  TATE = 113,   // "+TA", "縦", 上下どこでも移動できる。(先手の香車+後手の香車)
  ISHI = 114,   // "+IS", "石", 移動できない駒。
  // 独自。
  JYU = 115,    // "+JY", "拾"(語源は"十"。角みたいな動きで一コマのみ移動可。)
  KOMA_END=115 // 駒の順番を変える可能性あるため、最後の駒  
};

class Board {
public:
  static const int SIZE = 9; // 盤面の縦/横
  //static const int SIZE = 13; // 盤面の縦/横

  // 拡張盤のサイズ。盤面の外は(アルゴリズムで使う意味の)番兵。

  static const int BANPEI_SIZE = SIZE-1; // 通常の盤面の外側にある番兵のサイズ
  static const int OFFSET =  SIZE + BANPEI_SIZE + BANPEI_SIZE; // 9 + 8 + 8
  static const int OFFSETn2 = OFFSET*OFFSET;
  static const int XY_START_ARRAY_E= OFFSET * BANPEI_SIZE + BANPEI_SIZE;

  // KOMA_PRINT関連変数。
  struct KomaStringInit
  {
    static const int default_str_size = 30;

    // enum KOMA
    int k; 
    // enum KOMAの文字列
    char enum_str[default_str_size]; 
    // 日本語表記 幅:2, 後手は当て字で表示。
    char jp_str[default_str_size]; 
    // 日本語表記 幅:2/ 後手の色反転, Ref: http://vorfee.hatenablog.jp/entry/2015/03/17/173635
    // ファイルからの読み込みは未対応。
    char jp_str_rev[default_str_size]; 
    // 英語表記 幅:3, Ref: http://www2.computer-shogi.org/protocol/record_v2.html
    char eng_str[default_str_size]; 

    static const int enum_str_index = 0;
    static const int jp_str_index = 1;
    static const int jp_str_rev_index = 2;
    static const int eng_str_index = 3;
    static const int coma_string_size = 4; // 上記のKomaStringの*strの数。
  };
  static char ***KOMA_PRINT; // 印刷用文字列 init()で初期化

  static int **KOMA_EFFECT; // 駒の動き init()で初期化
  static int64_t found_count; // 見付かった数
  static int best_koma_nokori; // 現時点で一番駒を置く事が出来た場合の、残りの駒数。

  // 命名: flag* : あとから変更可能なフラグ
  // 命名: cflag* : init実行前に設定するフラグ。後から変更不可

  // flagの初期化はBoard.ccの頭
  // 初期値を書き換えた場合はBoard.cの頭とparse_arg()を書き換える。

  // 盤面表示: true:英語表示, false:日本語表示(default)
  static bool flag_print_english; 

  // 後手を色反転で表示
  // ttyの文字反転escape対応時のみ。
  // less & moreで見ると化ける。
  // flag_print_englishがtrueの時のみ
  // true: 反転, false:当て字
  static bool flag_print_gote_rev_coler; 

  // TODO: 実際に使うか検討。
  // true:後手の駒あり。false:後手なし(default)
  // ファイルの入力の時にチェックするだけ。内部的には常に有効
  static bool flag_enable_gote; 

  // true: 行き所の無い駒を反則とする. false:反則としない(default)
  static bool flag_enable_rule_ikidokoro_nashi; 

  // 最初に見付かった時と、大駒が動いた時のみ表示
  // 大駒が動いた時は動かなかった駒はそのまま表示し、動いた駒を△で表示。
  // true: 表示, false: 無効。(default)
  static bool flag_count_komaiti; 

  // 多重EFFECTを数字で表記
  // true: 数字で表記(default), false: 「■」もしくは「=E=」
  static bool cflag_print_enhanced_effect;

  static int BOARD_NG[KOMA_END+1][OFFSETn2];

  static int SelectLangIndex_KOMA_PRINT(void)
  {
    int index = KomaStringInit::eng_str_index;
    if(flag_print_english==false)
      {
	index = KomaStringInit::jp_str_index;
	if(flag_print_gote_rev_coler)
	  index = KomaStringInit::jp_str_rev_index;
      }
    return index;
  }

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

  int b[OFFSETn2];

  Board(void){
    // 通常盤の中はEMPTY、外の拡張盤は番兵代りのEFFECTで埋める。

    for(int i = 0; i < OFFSETn2; i++)
      b[i] = EFFECT;

    for(int i = 0; i < SIZE; i++){
      for(int j = 0; j < SIZE; j++){
	b[XY_to_Array_e(i,j)] = EMPTY;
      }
    }
  }

  Board(const Board&x){
    //cout << "In constract"<<endl;

    for(int i = 0; i < OFFSETn2; i++)
      b[i] = x.b[i];
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


  void Print(void); // 盤面表示
  void Print_e(void); // 拡張盤全体表示
  void PrintLine(void); // 1行で盤面表示
  void PrintLine_e(void); // 1行で拡張盤全体表示
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


#include "Board.h"

const int
  Board::SIZE;
const int
  Board::OFFSET;
char **
  Board::KOMA_PRINT;
int **
  Board::KOMA_EFFECT;
int64_t
  Board::found_count;
int
  Board::best_koma_nokori;

#ifdef IKIDOKORO_NASHI
int
  Board::BOARD_NG[KOMA_END+1][OFFSETn2];
#endif

static int  cmpint(const void *p1, const void *p2)
{
  return *(int*)p1 - *(int*)p2;
}

void
Board::init (void)
{
  int debug = 0;
  Board::found_count = 0;
  Board::best_koma_nokori = SIZE * SIZE;

// 飛車, 角, 王は先手後手の区別無し。

  static const char *tmp[] =
  { "□", 
    //"■",  // EFFECTが1重の時の表現
    " 1", // EFFECTが1重の時の表現
    "飛", "角", "王", "香", "金", "銀", "桂", "歩" 
#ifdef GEN_GOTE // 後手有り
    // 後手/香, 後手/金, 後手/銀, 後手/桂, 後手/歩
      ,"京"    , "琴"  , "吟"  , "軽" , "符" 
#ifdef KANRYAKU
    ,"縦", "石", "拾"
#endif
#endif
};

  // debug用にマイナスの部分にも値を入れておく。
  // "-9", "-8", "-7" .... "-1", "□", "■", " 2", " 3", ... "飛",  "角" ... 

  int offset = 9;
  int mem_len = KOMA_END + 1 + offset;
  KOMA_PRINT = new char *[mem_len];

  for (int i = 0; i < mem_len; i++)
    {
      KOMA_PRINT[i] = new char[10];
      KOMA_PRINT[i][0] = '\0';
    }

  // "-9", "-8", "-7" .... "-1"
  for (int i = 0; i < offset; i++)
    sprintf (KOMA_PRINT[i], "%d", (i - offset));

  // 始点を"□"に
  KOMA_PRINT += offset;
  strcpy (KOMA_PRINT[0], tmp[0]);
  strcpy (KOMA_PRINT[1], tmp[1]);

  // 2 から KOMA_START-1まで数字を入れる。

  for (int i = 2; i < KOMA_START; i++)
    sprintf (KOMA_PRINT[i], "%2d", i);

#ifdef COUNT_KOMAITI
  strcpy(KOMA_PRINT[KOMAITI_CHANGE], "△");
#endif

  // tmp[2]=飛車から入れる。
  for (int i = KOMA_START, j = 2; i <= KOMA_END; i++, j++)
    strcpy (KOMA_PRINT[i], tmp[j]);

  if (debug)
    {				// debug print
      for (int i = -offset; i < 0; i++)
	{
	  cout << "i=" << i << " = \"" << KOMA_PRINT[i] << "\"" << endl;
	}
      for (int i = 0; i <= KOMA_END; i++)
	{
	  cout << "i=" << i << " = \"" << KOMA_PRINT[i] << "\"" << endl;
	}
    }
  
#ifdef GEN_GOTE // 後手有り
  cout << "後手有り。表示の都合で以下のように表記" << endl;
  cout << "> 後手/香 :" << KOMA_PRINT[rKYOU];
  cout << ", 後手/金 :" << KOMA_PRINT[rKIN];
  cout << ", 後手/銀 :" << KOMA_PRINT[rGIN];
  cout << ", 後手/桂 :" << KOMA_PRINT[rKEI];
  cout << ", 後手/歩 :" << KOMA_PRINT[rFU] << endl;
  cout << "> その他の駒は先手後手で表示区別無し。" << endl;
#endif

  if(0){ // 古い初期化方法方
#include "koma_ugoki.cc"

    KOMA_EFFECT = new int *[KOMA_END + 1];

    for (int i = 0; i <= KOMA_END; i++)
      KOMA_EFFECT[i] = NULL;

    for (int i = KOMA_START, j = 0; i <= KOMA_END; i++, j++)
      KOMA_EFFECT[i] = koma_ugoki[j];

    if (SIZE != 9)
      {
	cerr << "ERROR in Board.cc: Error SIZE != 9" << endl;
	exit (1);
      }
  }else { // // 新しい初期化方法方
#include "koma_ugoki2.cc"
    /* 盤が9x9 以外の場合があるので、動的に計算 */
    int hisya = 0
      , kaku = 0, kyou = 0;
#ifdef GEN_GOTE // 後手有り
    int r_kyou = 0;
#ifdef KANRYAKU
      // 簡易版: 縦
    int tate = 0;
#endif
#endif
    if (SIZE != 9){
    for(int i = 1, j=0; i < SIZE; i++, j++){
      // 飛車
      koma_ugoki[HISYA - KOMA_START][hisya][0] = i; koma_ugoki[HISYA - KOMA_START][hisya][1] = 0; hisya++;
      koma_ugoki[HISYA - KOMA_START][hisya][0] = -i;koma_ugoki[HISYA - KOMA_START][hisya][1] = 0; hisya++;
      koma_ugoki[HISYA - KOMA_START][hisya][0] = 0; koma_ugoki[HISYA - KOMA_START][hisya][1] = i; hisya++;
      koma_ugoki[HISYA - KOMA_START][hisya][0] = 0; koma_ugoki[HISYA - KOMA_START][hisya][1] = -i; hisya++;

      // 角
      koma_ugoki[KAKU - KOMA_START][kaku][0] = i; koma_ugoki[KAKU - KOMA_START][kaku][1] = i; kaku++;
      koma_ugoki[KAKU - KOMA_START][kaku][0] = i; koma_ugoki[KAKU - KOMA_START][kaku][1] = -i; kaku++;
      koma_ugoki[KAKU - KOMA_START][kaku][0] = -i;koma_ugoki[KAKU - KOMA_START][kaku][1] = i;kaku++;
      koma_ugoki[KAKU - KOMA_START][kaku][0] = -i;koma_ugoki[KAKU - KOMA_START][kaku][1] = -i; kaku++;

      // 香車
      koma_ugoki[KYOU - KOMA_START][kyou][0] = i; koma_ugoki[KYOU - KOMA_START][kyou][1] = 0; kyou++;

#ifdef GEN_GOTE // 後手有り
      // 後手 香車
      koma_ugoki[rKYOU - KOMA_START][r_kyou][0] = -i; koma_ugoki[rKYOU - KOMA_START][r_kyou][1] = 0;r_kyou++;

#ifdef KANRYAKU
      // 簡易版: 縦
      koma_ugoki[TATE - KOMA_START][tate][0] = i; koma_ugoki[TATE - KOMA_START][tate][1] = 0;tate++;
      koma_ugoki[TATE - KOMA_START][tate][0] = -i; koma_ugoki[TATE - KOMA_START][tate][1] = 0;tate++;
#endif
#endif


    }
    koma_ugoki[HISYA - KOMA_START][hisya][0] = 0; koma_ugoki[HISYA - KOMA_START][hisya][1] = 0;
    koma_ugoki[KAKU - KOMA_START][kaku][0] = 0; koma_ugoki[KAKU - KOMA_START][kaku][1] = 0;
    koma_ugoki[KYOU - KOMA_START][kyou][0] = 0; koma_ugoki[KYOU - KOMA_START][kyou][1] = 0;
#ifdef GEN_GOTE // 後手有り
    koma_ugoki[rKYOU - KOMA_START][r_kyou][0] = 0; koma_ugoki[rKYOU - KOMA_START][r_kyou][1] = 0;
#ifdef KANRYAKU
    koma_ugoki[TATE - KOMA_START][tate][0] = 0; koma_ugoki[TATE - KOMA_START][tate][1] = 0;
#endif
#endif
    }
    // メモリサイズ計算
    int mem_count = 0;
    int ugoki_len[KOMA_END + 1];

    for (int i = KOMA_START, j = 0; i <= KOMA_END; i++, j++){
      ugoki_len[i] = 0;
      for(int k = 0; !(koma_ugoki[j][k][0] == 0 && koma_ugoki[j][k][1] == 0); k++)
	ugoki_len[i] ++;	
      mem_count += (ugoki_len[i] + 1); // 最後に0終端なので+1
    }

    if(debug)
      cout << "mem_count = " << mem_count << endl;

    // PC表現(X,Y) -> 拡張盤(Array)へ変換
    KOMA_EFFECT = new int *[KOMA_END + 1];
    memset(KOMA_EFFECT, 0, sizeof(int*) * (KOMA_END+1));

    int* tmp2 = new int[mem_count];
    memset(tmp2, 0, sizeof(int) * mem_count);

    for (int i = KOMA_START, j = 0; i <= KOMA_END; i++, j++){
      KOMA_EFFECT[i] = tmp2;
      tmp2 += (ugoki_len[i] + 1);// 最後に0終端なので+1

      for(int k = 0; k < ugoki_len[i]; k++){
	KOMA_EFFECT[i][k] =  - XY_START_ARRAY_E;
	KOMA_EFFECT[i][k] += XY_to_Array_e(koma_ugoki[j][k][0], koma_ugoki[j][k][1]);
      }
    }

    // 駒の動きをSortする。
    for (int i = KOMA_START, j = 0; i <= KOMA_END; i++, j++){
      int *t = KOMA_EFFECT[i];

      if(debug)
	cout << "KOMA = " << KOMA_PRINT[i] << endl;

      if(debug){
	cout << " presort = [";
	for(int k = 0; k < ugoki_len[i] ; k++){
	  cout << t[k] << ",";
	}
	cout << "]" << endl;
      }
      
      if(ugoki_len[i] >1)
	qsort(t, ugoki_len[i], sizeof(int), cmpint);
      
      if(debug){
	cout << " aftsort = [";
	for(int k = 0; k < ugoki_len[i] ; k++){
	  cout << t[k] << ",";
	}
	cout << "]" << endl;
      }
    }
  }

#ifdef IKIDOKORO_NASHI
  cout << "行き所の無い駒禁止。\n";

  for(int i = 0; i <= KOMA_END; i++){
    for(int j = 0; j < OFFSETn2; j++)
      BOARD_NG[i][j] = 0;
  }

  for(int y = 0; y < SIZE; y++)
    for(int x = 0; x < SIZE; x++){
      int array_e = XY_to_Array_e(x, y);
      if(x == 0){
	BOARD_NG[rFU][array_e]=1;
	BOARD_NG[rKYOU][array_e]=1;
	BOARD_NG[rKEI][array_e] = 1;
      }
      if(x == 1){
	BOARD_NG[rKEI][array_e] = 1;
      }

      if(x == 7){
	BOARD_NG[KEI][array_e] = 1;
      }

      if(x == 8){
	BOARD_NG[FU][array_e]=1;
	BOARD_NG[KYOU][array_e]=1;
	BOARD_NG[KEI][array_e] = 1;
      }
    }
#endif  

#ifdef COUNT_KOMAITI
  cout << "大駒位置移動時のみ表示\n";
#endif
}

void
Board::Print ()
{
  char line[] = "--";

  cout << "+";
  for (int i = 0; i < SIZE; i++)
    cout << line;
  cout << "+" << endl;;

  for (int i = SIZE - 1; i >= 0; i--)
    {
      cout << "|";
      for (int j = 0; j < SIZE; j++)
	{
	  cout << KOMA_PRINT[b[XY_to_Array_e (i, j)]];
	}
      cout << "|" << endl;
    }

  cout << "+";
  for (int i = 0; i < SIZE; i++)
    cout << line;
  cout << "+" << endl;;
}
void
Board::PrintLine ()
{
  for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
	{
	  cout << KOMA_PRINT[b[XY_to_Array_e (i, j)]];
	}
    }
  cout << endl;
}

void
Board::PrintLine_e ()
{
  for (int i = 0; i < OFFSET; i++)
    {
      for (int j = 0; j < OFFSET; j++)
	{
	  cout << KOMA_PRINT[b[XeYe_to_Array_e (i, j)]];
	}
    }
  cout << endl;
}

void
Board::Print_e ()
{
  char line[] = "--";
  char pline[] = "==";

  for (int j = 0; j < OFFSET; j++)
    {
      if (j == BANPEI_SIZE || j == (SIZE + BANPEI_SIZE))
	cout << "+";
      cout << pline;
    }
  cout << endl;

  for (int i = OFFSET - 1; i >= 0; i--)
    {
      for (int j = 0; j < OFFSET; j++)
	{
	  if (j == BANPEI_SIZE || j == (SIZE + BANPEI_SIZE))
	    cout << "|";
	  cout << KOMA_PRINT[b[XeYe_to_Array_e (i, j)]];
	}
      cout << endl;

      if (i == BANPEI_SIZE || i == (SIZE + BANPEI_SIZE) || i == 0)
	{
	  for (int j = 0; j < OFFSET; j++)
	    {
	      if (j == BANPEI_SIZE || j == (SIZE + BANPEI_SIZE))
		cout << "+";
	      cout << line;
	    }
	  cout << endl;
	}
    }
}

#ifndef COUNT_KOMAITI
void
Board::PrintLast (int koma_nokori, int masu_nokori)
{
  if(koma_nokori < Board::best_koma_nokori)
    Board::best_koma_nokori = koma_nokori;

  if (koma_nokori == 0)
    {
      found_count++;
      if (masu_nokori >= 0)
	cout << "%%FOUND, no = " << found_count << ", masu_nokori=" <<
	  masu_nokori << endl;
      else
	cout << "%%FOUND, no = " << found_count << endl;
    }
  else
    cout << "%%NOKORI=" << koma_nokori << endl;

  Print ();
  cout << "%%\n";
}
#endif /* !COUNT_KOMAITI */

#ifdef COUNT_KOMAITI

/*
  非常に解が多い場合のテスト用。

  debug: 

Youso hisya2_kaku1_ou1_youso = {
  {{HISYA,2},{KAKU,1},{OH,1},{YOUSO_TERMINAL, 0}},
  "簡略版/飛2/角1/王1/簡略版"
};

};


*/

#ifdef EXT_BAN_2
#errro "Not impliment"
#endif

static Board COUNT, COUNT_save;
static int64_t COUNT_b_total = 0;

/*
  koma_nokori
  masu_nokori, 但し -1, size*sizeは特殊扱い
*/

void
Board::PrintLast (int koma_nokori, int masu_nokori) 
{
  if(koma_nokori > 0){
    cerr << "Not Impliment\n";
    exit(1);
  }

  // 常に0のはず。
  Board::best_koma_nokori = 0;

  // 最後のフラッシュ
  if(COUNT_b_total >= 2 && masu_nokori == (SIZE*SIZE)){
    cout << "%%UNIQ, total = " << COUNT_b_total  << endl;
    COUNT.Print ();
    cout << "%%\n";
    return; 
  }

  found_count++;

  if(found_count == 1){//初回通過時のみ。
    for(int i = 0; i < OFFSETn2; i++){
      COUNT.b[i] = b[i];
      if(COUNT.b[i] < KOMAITI_CHANGE){
	COUNT.b[i] = EMPTY;
      }
    }
  }

  // 大駒の移動を検出
  for(int i = 0; i < OFFSETn2; i++){
      COUNT_save.b[i] = COUNT.b[i];
  }

  int oogoma_change = 0;

  for(int i=0; i < OFFSETn2; i++){
    if(b[i] >= KOMA_START || COUNT.b[i] >= KOMA_START){
      if(b[i] != COUNT.b[i]) {
	COUNT.b[i] = KOMAITI_CHANGE;
	if(b[i] == HISYA || b[i] == KAKU)
	  oogoma_change = 1;
      }
    }
  }
  
  if(oogoma_change == 0)
    { // 大駒が移動しなかった
      COUNT_b_total++;

      if(COUNT_b_total == 2){
	cout << "MEMO: PRINT SKIP (COUNT_KOMAITI)\n";
      }
    }
  else
    { // 大駒が移動した
      cout << "%%UNIQ, total = " << COUNT_b_total  << endl;
      COUNT_save.Print ();
      cout << "%%\n";

      for(int i = 0; i < OFFSETn2; i++){
	COUNT.b[i] = b[i];
	if(b[i] < KOMAITI_CHANGE)
	  COUNT.b[i] = EMPTY;
      }

      // すでに見付かっているから
      COUNT_b_total = 1;
    }

  if(COUNT_b_total == 1){
    if (masu_nokori >= 0){
      cout << "%%FOUND, no = " << found_count << ", masu_nokori=" <<
	masu_nokori << endl;
    } else {
      cout << "%%FOUND, no = " << found_count << endl;
    }
    Print ();
    cout << "%%\n";
  }
  cout.flush();
}
#endif /* COUNT_KOMAITI */


 /*
    組み合わせ生成関連の関数
  */

//  youso_srcをコピーして、FUと-1の間にEMPTYを挿入する。
//  EMPTYの数は盤面の数にそろえる。
int
youso_ins_empty (int leng, Youso * src, Youso * dst)
{
  int debug = 0;
  int koma_count = 0;		//駒の数
  int i;
  for (i = 0; src->y[i][0] != YOUSO_TERMINAL; i++)
    {
      dst->y[i][0] = src->y[i][0];
      dst->y[i][1] = src->y[i][1];

      if (src->y[i][0] >= KOMA_START)
	koma_count += src->y[i][1];
    }

  dst->y[i][0] = EMPTY;
  dst->y[i][1] = leng - koma_count;

  dst->y[i + 1][0] = YOUSO_TERMINAL;
  dst->y[i + 1][1] = 0;

  if (debug)
    {
      for (i = 0; dst->y[i][0] != YOUSO_TERMINAL; i++)
	{
	  cout << "koma=" << dst->y[i][0] << ", kazu = " << dst->
	    y[i][1] << endl;
	}
    }
  strcpy (dst->m, src->m);

  cout << "leng = " << leng << endl;
  cout << "koma = " << koma_count << endl;
  cout << "masu limit = " << MASU_LIMIT << endl;
#ifdef BOARD
  cout << "board class = " << BOARD << endl;
#endif
#ifdef SEARCH
  cout << "search function = " << SEARCH << endl;
#endif

  return koma_count;
}

void
print_youso (const Youso & youso)
{
  cout << "Koma list Comment: " << youso.m << endl;
  cout << "koma list = ";
  for (int i = 0; youso.y[i][0] != YOUSO_TERMINAL; i++)
    {
      cout << Board::KOMA_PRINT[youso.y[i][0]] << "x" << youso.
	y[i][1] << ", ";
    }
  cout << endl;
}

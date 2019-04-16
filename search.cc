#include "Board.h"
#include "sample.h"

#define  PRINT_STEP 1000000000 // 定時プリントのタイミング

#include "gen_kumi.cc"

int
main ()
{
  cout << "search function = 1\n";

  Youso youso = test1_youso;	// See: sample.h

  Youso youso2;

  int leng = Board::SIZE * Board::SIZE;
  int koma_count = 0;		//駒の数

  // yousoをコピーして、FUと-1の間にEMPTYを挿入する。
  koma_count = youso_ins_empty (leng, &youso, &youso2);

  Board::init ();
  Board list;

  print_youso (youso2);
  cout << "PRINT_STEP = " << PRINT_STEP << endl;
  cout << endl;
  gen_kumi (leng, youso2.y, list, 0, koma_count);

  cout << "KUMIAWASE = " << Board::found_count << endl;
}

#include "select.h"

/*
  全ての駒のEFFECTが正しい事を確認。
*/

int main()
{
  
  //Board::flag_print_english = true;
  Board::flag_print_gote_rev_coler = true;

  Board::init();

  for(int c = KOMA_START; c <= KOMA_END; c++){
    BOARD_CLASS start;
    start.Set(Board::SIZE/2,Board::SIZE/2, (KOMA)c);
    //start.Print_e();
    start.Print_e();
  }
  for(int c = KOMA_START; c <= KOMA_END; c++){
    BOARD_CLASS start;
    start.Set(0,0, (KOMA)c);
    start.Print_e();
  }
}

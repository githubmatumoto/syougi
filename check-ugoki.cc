#include "select.h"

/*
  全ての駒のEFFECTが正しい事を確認。
*/

int main(int argc, char **argv)
{
  pars_args(argc, argv);

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

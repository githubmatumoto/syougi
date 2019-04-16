#include "select.h"

/*
  模範回答例を試しに食わしてエラーにならない事を確認。

*/

void add(BOARD_CLASS &b, KOMA list[])
{
  int i, list_pos;
  for(i = 0, list_pos=0; i < Board::SIZE*Board::SIZE; i++){
    if(b.Set_Array(i, list[list_pos]) > 0)
      list_pos++;

    //b.Print();

    if(list[list_pos]==EMPTY)
      break;
  }

  b.Print();
  if(i >= Board::SIZE*Board::SIZE){
    cout << "FAIL" << endl;
  }else{
    cout << "GOOD" << endl;
  }
}

int main()
{
  Board::init();
  BOARD_CLASS start;

  KOMA list[] = {OH, KIN, FU, KIN, OH, 
	       HISYA, 
	       FU, FU, FU, FU, KYOU,
	       KAKU, FU, KEI, FU, GIN, KYOU,
	       FU, FU, FU, FU, GIN,
	       KAKU, FU, KEI, FU, GIN, KYOU,
	       FU, FU, FU, FU, KYOU,
	       HISYA,
	       KEI, KEI, GIN, KIN, FU, KIN,
	       EMPTY};

  // ちょとかえてる
  KOMA list2[] = {OH, KIN, FU, KIN, OH, 
	       HISYA, 
	       FU, FU, FU, FU, KYOU,
	       KAKU, FU, KEI, FU, GIN, KYOU,
	       FU, FU, FU, FU, GIN,
	       KAKU, FU, KEI, FU, GIN, KYOU,
	       FU, FU, FU, FU, KYOU,
	       HISYA,
		  KEI, KEI, KIN, KIN, GIN,FU,
	       EMPTY};

  //add(start, list2);
  add(start, list);

#ifdef GEN_GOTE
  KOMA rlist[] = {OH, rKIN, rFU, rKIN, OH, 
		 HISYA, 
		 rKYOU, rFU, rFU, rFU, rFU,
		 rKYOU, rGIN, rFU, rKEI, rFU, KAKU,
		 rGIN, rFU, rFU, rFU, rFU,
		 rKYOU, rGIN, rFU, rKEI, rFU, KAKU,
		 rKYOU, rFU, rFU, rFU, rFU,
		 HISYA,
		 rKIN, rFU, rKIN, rGIN, rKEI, rKEI,
		 EMPTY};

  BOARD_CLASS start2;
  add(start2, rlist);
#endif
}

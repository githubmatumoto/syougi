#if BOARD != 3
#error "ERROR"
#endif

#if IKIDOKORO_NASHI
#error "NG: IKIDOKORO_NASHI"
#endif

static void __attribute__ ((noinline))
gen_kumi_fu (const int leng, BOARD_CLASS & list, int koma_nokori,
	     int masu_nokori)
{
  int set_fu[koma_nokori + 1];
  int set_fu_c = 0;

  //すき間に歩をどんどん置いていく
  for (int list_pos = 0; list_pos < leng; list_pos++)
    {
      if (list.Get_Array (list_pos) == EMPTY)
	{
	  int ret = list.Set_Array (list_pos, FU);
	  if (ret == 0)
	    {			//EMPTYだけど駒は置けなかった。
	      masu_nokori--;	//マスを減らす。 <- search7で追加
	    }
	  else
	    {
	      set_fu[set_fu_c++] = list_pos;
	      masu_nokori -= ret;
	      koma_nokori--;

	      if (koma_nokori == 0)
		break;
	    }
	  if (masu_nokori < koma_nokori)
	    break;
	}
    }

  if (koma_nokori <= PRINT_KOMA_NOKORI) {
#if defined(GEN_GOTE) && defined(MASU_NOKORI)
    if(masu_nokori > 0)
#endif
      list.PrintLast (koma_nokori, masu_nokori);
  }

  for (int i = 0; i < set_fu_c; i++)
    list.UnSet_Array (set_fu[i], FU);

  if(koma_nokori < Board::best_koma_nokori){
    Board::best_koma_nokori = koma_nokori;
  }
}

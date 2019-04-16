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
  const int size = Board::SIZE;
  const int banpei = Board::BANPEI_SIZE;
  const int off = Board::OFFSET;

#ifdef PRINT_FU
  int save_koma_nokori = koma_nokori;
  int save_masu_nokori = masu_nokori;
#endif

  //すき間に歩をどんどん置いていく
  for (int y_e = banpei; y_e < (size + banpei); y_e++)
    {
      int array_e_offset = y_e * off + banpei;
      for (int x = 0; x < size; x++)
	{

	  if (list.Get_Array_e (array_e_offset + x) != EMPTY)
	    continue; // 駒を置けない

	  //次のマスに駒が置けるかをさしおいて、残りマスを減らす
	  // search6.cc以前ではこの処理でマスを減らしてない。
	  masu_nokori--;

	  // 次のマスに移動
	  x++;

	  // 次のマスに駒が無いか?
	  int next = list.Get_Array_e (array_e_offset + x);
	  if (next <= KOMA_START)
	    {
	      // 駒を置くのを成功
	      koma_nokori--;

	      // 次のマスがEMPTYならEFFECTに変化するので残りマスを減らす
	      if (next == EMPTY)
		masu_nokori--;

	      if (koma_nokori == 0)
		goto LoopOut;
	    }
	  if (masu_nokori < koma_nokori)
	    goto LoopOut;
	}
    }

LoopOut:
  if(koma_nokori < Board::best_koma_nokori){
    Board::best_koma_nokori = koma_nokori;
  }
   
  if (koma_nokori > PRINT_KOMA_NOKORI)
    return;

#if defined(GEN_GOTE) && defined(MASU_NOKORI)
  if(masu_nokori == 0)
    return;
#endif

#ifdef PRINT_FU
  gen_kumi_fu_aux (leng, list,  save_koma_nokori, save_masu_nokori);
#else
  list.PrintLast (koma_nokori, masu_nokori);
#endif
}

#if BOARD != 3
#error "ERROR"
#endif

static void
gen_kumi2 (const int leng, int youso[][2],
	   BOARD_CLASS & list, int list_pos, int koma_nokori, int masu_nokori)
{
  //cout << "DEBUG0\n";

  //cout << "koma_nokori = " << koma_nokori << endl;
  //cout << "masu_nokori = " << masu_nokori << endl;

  // 置く事が出来るマスより、残りの駒が多くなった。
  if ((masu_nokori-MASU_LIMIT) < koma_nokori)
    return;

  //cout << "DEBUG1\n";
  //cout << "koma_nokori = " << koma_nokori << endl;
  //cout << "masu_nokori = " << masu_nokori << endl;


  if (youso[0][0] == EMPTY)
    {
      list.PrintLast (0, masu_nokori);
      return;
    }

  //cout << "DEBUG2\n";

  // 現在置いてい駒が残りゼロになったので、次の駒に移る */
  if (youso[0][1] == 0)
    {
      // 現在置いている数字が残りゼロになったので、次の数字に移る 
      // youso+1 -> youso[1][0]と同じ意味。
      gen_kumi2 (leng, youso + 1, list, 0, koma_nokori, masu_nokori);
      return;
    }

  //cout << "DEBUG3\n";

  // 頭出し
  for (; list_pos < leng; list_pos++)
    if (list.Get_Array (list_pos) == EMPTY)
      break;

  // 盤面に空いている所無し。
  if (list_pos == leng)
    return;

  //定時表示
  PrintStep (list, PRINT_STEP);

  int ret = 0;

  if ((ret = list.Set_Array (list_pos, (KOMA) youso[0][0])) > 0)
    {
      // 駒をひとつ置いて再帰
      youso[0][1]--;

      int  k = koma_nokori-1;
      if(k < Board::best_koma_nokori)
	Board::best_koma_nokori = k;

      gen_kumi2 (leng, youso, list, list_pos + 1, k, masu_nokori - ret);

      youso[0][1]++;

      list.UnSet_Array (list_pos, (KOMA) youso[0][0]);
    }

  // 駒をおかずに再帰。
  gen_kumi2 (leng, youso, list, list_pos + 1, koma_nokori, masu_nokori);
}

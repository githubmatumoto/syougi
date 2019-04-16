static void
gen_kumi (const int leng, int youso[][2],
	  Board & list, int list_pos, int koma_nokori)
{
  if (youso[0][0] == EMPTY)
    {
      list.PrintLast (0, -1);
      return;
    }

  if (youso[0][1] == 0)
    {
      // 現在置いている数字が残りゼロになったので、次の数字に移る 
      // youso+1 -> youso[1][0]と同じ意味。
      gen_kumi (leng, youso + 1, list, 0, koma_nokori);
      return;
    }

  // 頭出し
  for (; list_pos < leng; list_pos++)
    if (list.Get_Array (list_pos) == EMPTY)
      break;

  // 盤面に空いている所無し。
  if (list_pos == leng)
    return;

  //定時表示
  PrintStep (list, PRINT_STEP);

  Board list2 = list;
  if (list2.Set_Array (list_pos, (KOMA) youso[0][0]))
    {
      // 駒をひとつ置いて再帰
      youso[0][1]--;

      int  k = koma_nokori-1;
      if(k < Board::best_koma_nokori)
	Board::best_koma_nokori = k;

      gen_kumi (leng, youso, list2, list_pos + 1, k);

      //駒を戻す
      youso[0][1]++;
    }


  // 駒をおかずに再帰。
  gen_kumi (leng, youso, list, list_pos + 1, koma_nokori);
}

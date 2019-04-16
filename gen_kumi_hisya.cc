
#if BOARD != 3
#error "ERROR"
#endif

#ifdef PRESET_KOMA
#error "ERROR: Cannot work PRESET_KOMA"
#endif

static void
gen_kumi_hisya (const int leng, int youso[][2],
		BOARD_CLASS & list, const int list_pos,
		const int koma_nokori, const int masu_nokori)
{
  int debug = 0;

#ifdef TIME_TEST
  cout << "MESS: TIME_TEST START\n";
#endif

#ifdef TIME_TEST2    
  // TIME_TEST2では飛車はすでに並べている
  if (youso[0][0] == HISYA || youso[0][1] == 0)
    {
      gen_kumi_pre_fu (leng, youso + 1, list, 0, koma_nokori, masu_nokori);
      return;
    }
#endif

  if (youso[0][0] != HISYA || youso[0][1] != 2)
    {
      cerr << "ERROR: HISYA NOMI\n";
      return;
    }

  const int size = Board::SIZE;
  const int half_size = (size - 1) / 2;

  if(size%2 == 0){
    cerr << "ERROR: KISUU GENTEI\n"; // 奇数のみ。
    return;
  }

  youso[0][1] = 0;

  /*
鏡像配慮。
----------
A  |C|  B
----------
  */

  if (debug)
    cout << "HISYA HAICHI: A, [A,B,C]\n";

  for(int y = 0; y < half_size; y++){
    for(int x = 0; x < size; x++){
      int no1_array = list.XY_to_Array(x, y);// 1枚目の駒位置, A
      int ret1 = list.Set_Array(no1_array, HISYA);
      if (ret1 <= 0)
	continue;

      // 2枚目の駒位置, [A,C,B] 

      // A, C
      for (int no2_array  = no1_array +1; no2_array < (half_size+1) * size; no2_array++) 
	{
	  int ret2 = list.Set_Array (no2_array, HISYA);
	  if (ret2 <= 0)
	    continue;

	  if(debug){
	    list.PrintLast (0, -1);
	  } else{
	    gen_kumi_pre_fu (leng, youso + 1, list, 0,
			     koma_nokori - 2,
			     masu_nokori - ret1 - ret2);
	  }
	  list.UnSet_Array (no2_array, HISYA);
	}
      
      // Bは鏡面なので注意
      for (int no2_array  = no1_array +1; no2_array < half_size * size; no2_array++) 
	{
	  int no2_x = list.Array_to_X(no2_array);
	  int no2_y = list.Array_to_Y(no2_array);
	  no2_y = size - no2_y -1; // 鏡面

	  int ret2 = list.Set (no2_x, no2_y, HISYA);
	  if (ret2 <= 0)
	    continue;

	  if(debug){
	    list.PrintLast (0, -1);
	  } else{
	    gen_kumi_pre_fu (leng, youso + 1, list, 0,
			     koma_nokori - 2,
			     masu_nokori - ret1 - ret2);
	  }
	  list.UnSet (no2_x, no2_y, HISYA);

	}
      list.UnSet_Array (no1_array, HISYA);

#ifdef TIME_TEST
      if(y == 1 && x == 0)
	goto loopout;
#endif
    }
  }

#ifdef TIME_TEST
 loopout:
  cout << "MESS: TIME_TEST END\n";
#endif

  youso[0][1] = 2;
}


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

#ifndef GEN_GOTE
  cout <<"ERROR: 後手アリのみ\n";
  return;
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
  const int size2 = size * size;

  if(size%2 == 0){
    cerr << "ERROR: KISUU GENTEI\n"; // 奇数のみ。
    return;
  }

  youso[0][1] = 0;

  /*
    鏡像(左右および上下)と180度回転を排除

    ---------
    G  |H|  I
    ---------
    D  |E|  F
    ---------
    A  |B|  C
    ---------
  */

  int flag[size][size][size][size]; /* no1_x, no1_y, no2_x, no2_y */
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      for(int k = 0; k < size; k++){
	for(int l = 0; l < size; l++){
	  flag[i][j][k][l] = 0;
	}
      }
    }
  }

  for(int no1_y = 0; no1_y <= half_size; no1_y++){
    for(int no1_x = 0; no1_x <= half_size; no1_x++){
      /* 上記 2重ループで 1枚目の駒の A, B, D, Eの領域を生成*/

      int no1_array = list.XY_to_Array(no1_x, no1_y);// 1枚目の駒位置, A, B, D, E
      int ret1 = list.Set_Array(no1_array, HISYA);
      if (ret1 <= 0)
	continue;
	
      for(int no2_array = no1_array+1; no2_array < size2; no2_array++){
	{
	  const int no2_x = list.Array_to_X(no2_array);
	  const int no2_y = list.Array_to_Y(no2_array);

	  if(debug)
	    cout << "\nBASE: [" << no1_x << ", " << no1_y << "]["<< no2_x << ", " << no2_y << "]" << endl;

	  int x1, y1, x2, y2;

	/* 左右鏡像
	   ---------
	   I  |H|  G
	   ---------
	   F  |E|  D
	   ---------
	   C  |B|  A
	   ---------
	*/
	  x1 = no1_x; y1 = size - no1_y -1;
	  x2 = no2_x; y2 = size - no2_y -1;

	  if(debug)
	    cout << "LEFT: [" << x1 << ", " << y1 << "]["<< x2 << ", " << y2 << "]" << endl;

	  if(flag[x1][y1][x2][y2])
	    continue;

	/* 上下鏡像 
	   ---------
	   A  |B|  C
	   ---------
	   D  |E|  F
	   ---------
	   G  |H|  I
	   ---------
	*/
	  x1 = size - no1_x -1; y1 = no1_y;
	  x2 = size - no2_x -1; y2 = no2_y;

	  if(debug)
	    cout << "JYOU: [" << x1 << ", " << y1 << "]["<< x2 << ", " << y2 << "]" << endl;

	  if(flag[x1][y1][x2][y2])
	    continue;

	/* 180度回転
	   ---------
	   C  |B|  A
	   ---------
	   F  |E|  D
	   ---------
	   I  |H|  G
	   ---------
	*/
	  x1 = size - no1_x -1; y1 = size - no1_y -1;
	  x2 = size - no2_x -1; y2 = size - no2_y -1;

	  if(debug)
	    cout << "ROTA: [" << x1 << ", " << y1 << "]["<< x2 << ", " << y2 << "]" << endl;

	  if(flag[x1][y1][x2][y2])
	    continue;

	  flag[no1_x][no1_y][no2_x][no2_y] = 1;

	  /* 必須 鏡像や回転の時に no1_array < no2_array の条件が崩れる事がある。 */
	  flag[no2_x][no2_y][no1_x][no1_y] = 1;

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
      }
      list.UnSet_Array (no1_array, HISYA);
    }
#ifdef TIME_TEST
    // no1_y == 0 のみ実行
    break;
#endif
  }

#ifdef TIME_TEST
  cout << "MESS: TIME_TEST END\n";
#endif

  if(debug){
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size; j++){
	for(int k = 0; k < size; k++){
	  for(int l = 0; l < size; l++){
	    if(flag[i][j][k][l] == 0)
	      cout << "NONE: [" << i << ", " << j << "]["<< k << ", " << l << "]" << endl;
	  }
	}
      }
    }
  }

  youso[0][1] = 2;
}

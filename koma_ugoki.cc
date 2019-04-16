  static int koma_ugoki[][33] =	// 隙間だらけの配列
  {
    // HISHA
    {1, 2, 3, 4, 5, 6, 7, 8, -1, -2, -3, -4, -5, -6, -7, -8,
     OFFSET, OFFSET * 2, OFFSET * 3, OFFSET * 4, OFFSET * 5, OFFSET * 6,
     OFFSET * 7, OFFSET * 8,
     -OFFSET, -OFFSET * 2, -OFFSET * 3, -OFFSET * 4, -OFFSET * 5, -OFFSET * 6,
     -OFFSET * 7, -OFFSET * 8, 0},
    // KAKU
    {OFFSET + 1, OFFSET * 2 + 2, OFFSET * 3 + 3, OFFSET * 4 + 4,
     OFFSET * 5 + 5, OFFSET * 6 + 6, OFFSET * 7 + 7, OFFSET * 8 + 8,
     OFFSET - 1, OFFSET * 2 - 2, OFFSET * 3 - 3, OFFSET * 4 - 4,
     OFFSET * 5 - 5, OFFSET * 6 - 6, OFFSET * 7 - 7, OFFSET * 8 - 8,
     -OFFSET + 1, -OFFSET * 2 + 2, -OFFSET * 3 + 3, -OFFSET * 4 + 4,
     -OFFSET * 5 + 5, -OFFSET * 6 + 6, -OFFSET * 7 + 7, -OFFSET * 8 + 8,
     -OFFSET - 1, -OFFSET * 2 - 2, -OFFSET * 3 - 3, -OFFSET * 4 - 4,
     -OFFSET * 5 - 5, -OFFSET * 6 - 6, -OFFSET * 7 - 7, -OFFSET * 8 - 8, 0},
    // OU -> 左側を先に変更
    {-OFFSET - 1, -OFFSET, -OFFSET + 1, -1, 1, OFFSET - 1, OFFSET, OFFSET + 1,
     0},
    // KYOU 
    {1, 2, 3, 4, 5, 6, 7, 8, 0},
    // KIN
    {-OFFSET, -OFFSET + 1, -1, 1, OFFSET, OFFSET + 1, 0},
    // GIN -> 左側を先に変更
    {-OFFSET - 1, -OFFSET + 1, 1, OFFSET - 1, OFFSET + 1, 0},
    // KEI -> 左側を先に変更
    {-OFFSET + 2, OFFSET + 2, 0},
    // FU
    {1, 0}
#ifdef GEN_GOTE // 後手有り
    // rKYOU 
    ,{-1, -2, -3, -4, -5, -6, -7, -8, 0},
    // rKIN
    {-OFFSET -1, -OFFSET , -1, 1, OFFSET-1, OFFSET, 0},
    // rGIN 
    {-OFFSET -1, -OFFSET +1, -1, OFFSET - 1, OFFSET + 1, 0},
    // rKEI
    {-OFFSET - 2, OFFSET - 2, 0},
    // rFU
    {-1, 0}
#ifdef  KANRYAKU
    // TATE
    ,{1, 2, 3, 4, 5, 6, 7, 8, -1, -2, -3, -4, -5, -6, -7, -8, 0},
    // ISHI
    {0, 0},
    // JYU
    {-OFFSET , -1, 1, OFFSET, 0},
#endif
#endif
  };

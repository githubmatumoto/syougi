#if BOARD != 3
#error "ERROR"
#endif

/*
  配列preinit_posに駒を置く位置を入れる。位置はPC表現(array)。
 終端は-1

 yousoは復元しない。

 返り値: -1 : 失敗
 返り値: 0 : 成功

 注意:

   例えば 同種のX枚ある駒のX-1枚だけの初期化とかの場合、
   次に呼び出すgen_kumi*関数はlist_posの位置計算が微妙な事になるので、
   同種の駒は全て同時にpreset_komaで初期化した方が良い。
*/
static int
preset_koma (int youso[][2],
	     BOARD_CLASS & list, int *koma_nokori, int *masu_nokori, 
	     int preset_pos[][2])
{
  if(preset_pos[0][0] == -1){
    return 0;
  }

  // 置く事が出来るマスより、残りの駒が多くなった。
  if (*masu_nokori < *koma_nokori)
    return -1;

  // 現在置いてい駒が残りゼロになったので、次の駒に移る */
  if (youso[0][1] == 0)
    return preset_koma (youso + 1, list, koma_nokori, masu_nokori, preset_pos);

  int ret = 0;
  if ((ret = list.Set (preset_pos[0][0], preset_pos[0][1], (KOMA) youso[0][0])) == 0)
    return -1;

  // 駒をひとつ置いて再帰
  youso[0][1]--;

  (*koma_nokori)--;
  (*masu_nokori) -= ret;
  return preset_koma (youso, list, koma_nokori,
		    masu_nokori, preset_pos+1);
}

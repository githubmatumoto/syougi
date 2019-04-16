#include "select.h"
#include "sample.h"
#include "searchXX.h"

#if defined(TIME_TEST2) || defined(PRESET_KOMA)
#include "preset_koma.cc"
#endif

int
main ()
{
  //Youso youso = org_last_kyou_fu_youso; // See: sample.h
  Youso youso = kyou_nashi_youso;	// これを通常使う

  //Youso youso = hisya_2_mai_youso;	// 飛車２枚のみ。

  //Youso youso = kyou_nashi_ishi_youso; // 香車無しで, 石1個, 後手歩が11個, 先手歩が11個/後手有
  //Youso youso = kan_hisya_kaku_ishinashi_fu_youso;
  //Youso youso = kan_org_last_ishi_youso;
  //Youso youso =  kan_hisya_kaku_jyu_fu_youso_r;
  //Youso youso =  kan_hisya_kaku_jyu_fu_kei_youso_r;
  //Youso youso = org_last_kei_kyou_youso_r;
  //Youso youso = org_last_kei_kyou_youso;
  //Youso  youso = org_last_kei_kyou_youso_r;
  //Youso  youso = hisya_kaku_kin_fu_kei_youso;
  //Youso  youso = kan_hisya_kaku_jyu_fu14_youso_r;
  //Youso  youso = last_fu_10_kei_kyou_youso_r;
  //Youso  youso = last_fu_10_kei_kyou_youso_r;
  //Youso  youso = hisya_kaku_fu32_youso;
  //Youso youso = kan_hisya_kaku_ishi_fu_youso ;
  //Youso youso = last_fu10_kei_kyou_youso_r;
  //Youso youso = org_youso_r;
  //Youso youso = kan_hisya_kaku_jyu_fu_kei_youso_r;
  //Youso youso = kan_hisya_ishi_fu_youso;
  //Youso youso = hisya_kaku_ou4_youso;
  //Youso youso = hisya2_kaku1_ou1_youso ;
  //Youso youso = kan_hisya_kaku_jyu_fu_kei_youso_r;
  //Youso youso =last_fu_11_kei_kyou_youso_r;
  Youso youso2;

  int leng = Board::SIZE * Board::SIZE;
  int koma_count = 0;		//駒の数

  // yousoをコピーして、FUと-1の間にEMPTYを挿入する。
  koma_count = youso_ins_empty (leng, &youso, &youso2);

  Board::init ();
  BOARD_CLASS list;

  print_youso (youso2);
  cout << "PRINT_STEP = " << PRINT_STEP << endl;
  cout << endl;

  int koma_nokori = koma_count;
  int masu_nokori = leng;

#if defined(TIME_TEST2) || defined(PRESET_KOMA)
  //PreSetPos pre = hisya_kaitou;
  PreSetPos pre = hisya_kaku_kaitou;

#ifdef TIME_TEST2
  cout << "TIME_TEST2: 初期状態: " << pre.m << endl;
#endif
#ifdef PRESET_KOMA
  cout << "PRESET_KOMA: 初期状態: " << pre.m << endl;
#endif

  cout << endl;

  if(preset_koma(youso2.y, list, &koma_nokori, &masu_nokori, pre.p) < 0){
#ifdef TIME_TEST2
    cout << "ERROR: Bad initial TIME_TEST\n";
#endif
#ifdef PRESET_KOMA    
    cout << "ERROR: Bad initial PRESET_KOMA\n";
#endif
    exit(1);
  }

#endif

  gen_kumi_wap (leng, youso2.y, list, 0, koma_nokori, masu_nokori);

#ifdef COUNT_KOMAITI
  list.PrintLast(0, leng); // 最後のflush
#endif

  cout << "KUMIAWASE = " << Board::found_count << endl;
}

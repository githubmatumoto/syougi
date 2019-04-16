/*
  search5:
  search4.ccとほぼ同じだが、表示を変更

  search4.ccのコメント引用:
  search2.ccと比較して、歩を例外扱い。最後の要素がかならず歩
  である必要がある。歩は順列生成をして置いていかない。置ける
  所にどんどん置いていって、残りますが無くなったらあきらめる。
  歩を置いている時にbest_koma_nokoriが更新されても !!NEW!!と
   表示されない。

  search6:
  飛車の鏡像を生成しない。
  飛車がかならず最初の要素である必要がある。

  search7:
  歩を置いている段階で、
  EMPTYに歩を置く時に失敗してもマスの残りを減らす(masu_nokori--をする。)

  search8:
  search7と比較して、
  歩を置いている関数をfor loopに展開する。
  歩を置いてもclass Boardを直接更新しない。

  search9:
  search8のgen_ku_pre_fuのループをちょっと改善

  search10: search6の飛車の鏡面生成をしないルーチン + search2(歩を特殊処理しない)
            後から必要になったので、飛び番号。

search36.cc: search6と同じで後手対応,後手の鏡面や180度回転などを生成しない。
search37.cc: search7と同じで, 同上
search38.cc: search8と同じで, 同上
search39.cc: search9と同じで, 同上
search40.cc: search10と同じで, 同上

*/

#if BOARD != 3
#error "ERROR"
#endif

#ifdef TIME_TEST2
#define PRINT_KOMA_NOKORI  0 // TIME_TESTではずらっと出るとうざい。
#else
//#define PRINT_KOMA_NOKORI  4 // この数字以下の駒残りだと表示
#define PRINT_KOMA_NOKORI  0
#endif

#ifndef PRINT_STEP
#define PRINT_STEP 500000000 // 定時プリントのタイミング
#endif

#if SEARCH == 2
#undef PRINT_STEP
#define PRINT_STEP 1000000000
#endif


#ifdef TIME_TEST2
#ifdef TIME_TEST
#error "Bad Define"
#endif
#endif

#if SEARCH == 2 || SEARCH == 32 

#include "gen_kumi2.cc"
#endif


#if SEARCH == 5
#include "gen_kumi_fu1.cc"
#include "gen_kumi_pre_fu.cc"
#endif

#if SEARCH == 6
#include "gen_kumi_fu1.cc"
#include "gen_kumi_pre_fu.cc"
#include "gen_kumi_hisya.cc"
#endif

#if SEARCH == 36
#include "gen_kumi_fu1.cc"
#include "gen_kumi_pre_fu.cc"
#include "gen_kumi_hisya2.cc"
#endif

#if SEARCH == 7
#include "gen_kumi_fu2.cc"
#include "gen_kumi_pre_fu.cc"
#include "gen_kumi_hisya.cc"
#endif

#if SEARCH == 37
#include "gen_kumi_fu2.cc"
#include "gen_kumi_pre_fu.cc"
#include "gen_kumi_hisya2.cc"
#endif

#if SEARCH == 8

#ifdef PRINT_FU
// 表示謡用の関数としてsearch7のを転用
#define gen_kumi_fu gen_kumi_fu_aux
#include "gen_kumi_fu2.cc"
#undef gen_kumi_fu
#endif

#include "gen_kumi_fu3.cc"

#include "gen_kumi_pre_fu.cc"
#include "gen_kumi_hisya.cc"
#endif

#if SEARCH == 38

#ifdef PRINT_FU
// 表示謡用の関数としてsearch7のを転用
#define gen_kumi_fu gen_kumi_fu_aux
#include "gen_kumi_fu2.cc"
#undef gen_kumi_fu
#endif

#include "gen_kumi_fu3.cc"

#include "gen_kumi_pre_fu.cc"
#include "gen_kumi_hisya2.cc"
#endif

#if SEARCH == 9

#ifdef PRINT_FU
// 表示謡用の関数としてsearch7のを転用
#define gen_kumi_fu gen_kumi_fu_aux
#include "gen_kumi_fu2.cc"
#undef gen_kumi_fu
#endif

#include "gen_kumi_fu3.cc"

#include "gen_kumi_pre_fu2.cc"
#include "gen_kumi_hisya.cc"
#endif

#if SEARCH == 39

#ifdef PRINT_FU
// 表示謡用の関数としてsearch7のを転用
#define gen_kumi_fu gen_kumi_fu_aux
#include "gen_kumi_fu2.cc"
#undef gen_kumi_fu
#endif

#include "gen_kumi_fu3.cc"

#include "gen_kumi_pre_fu2.cc"
#include "gen_kumi_hisya2.cc"
#endif

#if SEARCH == 10
#include "gen_kumi2.cc"
#define gen_kumi_pre_fu gen_kumi2
#include "gen_kumi_hisya.cc"
#undef gen_kumi_pre_fu
#endif

#if SEARCH == 40
#include "gen_kumi2.cc"
#define gen_kumi_pre_fu gen_kumi2
#include "gen_kumi_hisya2.cc"
#undef gen_kumi_pre_fu
#endif


static inline void
gen_kumi_wap (const int leng, int youso[][2],
	      BOARD_CLASS & list, int list_pos,
	      const int koma_nokori, const int masu_nokori)
{
#if SEARCH >= 6
  gen_kumi_hisya (leng, youso, list, 0, koma_nokori, masu_nokori);
#elif SEARCH == 5
  gen_kumi_pre_fu (leng, youso, list, 0, koma_nokori, masu_nokori);
#elif SEARCH == 2
  gen_kumi2 (leng, youso, list, 0, koma_nokori, masu_nokori);
#else
#error "Bad "  
#endif
}

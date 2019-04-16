/* 順列生成関数関連 */

#define YOUSO_TERMINAL (-1)

// 並べるのに使う駒の一覧
// see: sample.h
struct Youso{
#ifdef GEN_GOTE // 後手有り
  int y[18][2];
#else // 後手無し
  int y[12][2];
#endif
  char m[100];
};
int youso_ins_empty(int leng, Youso *src, Youso *dst);
void print_youso(const Youso &dst);

// 駒を事前に数枚並べておく時の位置
struct PreSetPos{
#ifdef GEN_GOTE // 後手有り
  int p[18][2];
#else // 後手無し
  int p[12][2];
#endif
  char m[100];
};


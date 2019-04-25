#  このMakefileはファイルの依存関係をきちんと記載してないので
# プログラムを編集したらmake cleanをすること。

CFLAGS=-Wall -O3
#
#
# -DTIME_TEST: search6/7,8のみ
# 飛車を飛車を左側1列と2列目で1つの合計10枚のみ並べる。
#CFLAGS := $(CFLAGS) -DTIME_TEST

# -DTIME_TEST2: search2.cc以降
# gen_kumi_hisya/hisya2を使う関数でのみ動作する。
# 飛車/角を解答例の位置にすでにならべる。
#CFLAGS := $(CFLAGS) -DTIME_TEST2

# -DPRESET_KOMA: search2.cc以降, 
# gen_kumi_hisya/hisya2を使う関数ではエラーになる。
#
# 駒をsearchXX.ccのmainの所で定義したPreSetPosの定義に従って並べる。
#CFLAGS := $(CFLAGS) -DPRESET_KOMA

# 廃止(2019/4/19): プログラム引数
# -DIKIDOKORO_NASHI
# 行き所の無い駒は禁止
#CFLAGS := $(CFLAGS) -DIKIDOKORO_NASHI

# -DPRINT_FU : search8以降
# search8以降は歩兵を置く時にClass Board3を更新しないため、
# 解が見付かった時のprint時に歩兵が「□」のままである。
# このflagを定義すると、表示のために「歩」が入った盤面を再生成する。
# 遅くなるので、全patternのsearchの時はつかわないほうが良い。
# --> 実測したら有為な差はなさげ。。
# MEMO(2019/4/19): マクロをプログラム引数に変更しようかと思ったが
# CPPのinclude + define 技があったので無理。
CFLAGS := $(CFLAGS) -DPRINT_FU

# 廃止(2019/4/19): プログラム引数
# 後手のコードを生成
#CFLAGS := $(CFLAGS) -DGEN_GOTE

# マスが残っている場合のみ表示。-DMASU_NOKORI
# GEN_GOTEを同時に定義した場合のみ有効
#
#
#CFLAGS := $(CFLAGS) -DGEN_GOTE -DMASU_NOKORI

# -DMASU_LIMIT=数字  
#  探索途中のマスの残りの見切りで使う数字。
#CFLAGS := $(CFLAGS) -DMASU_LIMIT=5

# 簡略版のコードを生成。-DKANRYAKU
# Ref: http://www.ktr.to/Game/Java/kaisetsu.html
#
# GEN_GOTEを同時に定義した場合のみ有効
#CFLAGS := $(CFLAGS) -DGEN_GOTE -DKANRYAKU

# 最初に見付かった時と、大駒が動いた時のみ表示
# 大駒が動いた時は動かなかった駒はそのまま表示し、動いた駒を△で表示。
# -DCOUNT_KOMAITI
#
# 解が非常に多い場合はPRINT_STEPが途中に挟まる場合があるので、注意。
#CFLAGS := $(CFLAGS) -DCOUNT_KOMAITI

#CC=g++ 
#CC=g++ -Wall -O3 -DTIME_TEST
CC=g++ $(CFLAGS)
#
#CC=g++-4.8.1 $(CFLAGS)


###################################

ALL=search search2 search5 search6 search7 search8 search9 search36 search37 search38 search39 search10 search40 \
check-ugoki check-ugoki-2 check-ugoki-3 check-mohan check-mohan-2 check-mohan-3

all: $(ALL)


check-ugoki: check-ugoki.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=1

check-ugoki-2: check-ugoki.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=2

check-ugoki-3: check-ugoki.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3

check-mohan: check-mohan.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=1

check-mohan-2: check-mohan.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=2

check-mohan-3: check-mohan.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3

search: search.cc Board.cc
	$(CC) $^ -o $@


search2: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=2

search5: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=5

search6: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=6

search7: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=7

search8: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=8

search9: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=9

search10: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=10

search32: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=32

search36: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=36

search37: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=37

search38: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=38

search39: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=39

search40: searchXX.cc Board.cc
	$(CC) $^ -o $@ -DBOARD=3 -DSEARCH=40


clean: 
	-rm a.out *~ $(ALL) $(ALL2)



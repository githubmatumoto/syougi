index.html執筆用に実行したのの実行例

<!--
leng = 81
koma = 40
masu limit = 0
board class = 3
search function = 8
Koma list Comment: 香車無しで歩が22個
koma list = 飛x2, 角x2, 王x2, 金x4, 銀x4, 桂x4, 歩x22, □x41,
PRINT_STEP = 500000000

kawazu/exec13
START: 2014年  5月 10日 土曜日 15:47:13 JST
END  : 2014年  5月 12日 月曜日 17:34:38 JST

KUMIAWASE = 2520
-->


index2.html執筆用に実行したのの実行例

----
<!--
念のため再実行

leng = 81
koma = 40
masu limit = 0
board class = 3
search function = 8
Koma list Comment: 簡略版/飛2/角2/桂4/歩32/簡略版
koma list = 飛x2, 角x2, 桂x4, 歩x32, □x41,
PRINT_STEP = 500000000

kawazu/exec10

START:  2014年  4月 29日 火曜日 21:09:42 JST
END:    2014年  4月 29日 火曜日 21:24:59 JST

KUMIAWASE = 13
OUT: kawazu-exec10.txt
-->

<!--
search8(飛車x2, 角x2, 桂馬x4, 歩兵x32(歩兵最後))だと30分ぐらいで終わる。
念のためsearch10で再実行。こちらは桂馬が最後。

leng = 81
koma = 40
masu limit = 0
board class = 3
search function = 10
Koma list Comment: 飛車x2/角x2/歩x32/桂馬x4
koma list = 飛x2, 角x2, 歩x32, 桂x4, □x41,
PRINT_STEP = 500000000

kawazu/exec2

kawazu: (別プロセスと並列実行)
START: 2014年  4月 23日 水曜日 19:30:44 JST
END:   2014年  6月 23日 月曜日 03:27:24 JST

KUMIAWASE = 13
out : kawzu-exec2.txt 

これはkawazu-exec10.txtと同じ結果のはず。

cat kawazu-exec10.txt | perl ../conv_line.pl | sort > t
cat kawazu-exec2.txt | perl ../conv_line.pl | sort > t2
diff t t2
  -> 問題無し。

-->

kawazu-no2:
<!--
leng = 81
koma = 40
masu limit = 0
board class = 3
search function = 10
Koma list Comment: 飛車x2/角x2/金x6/歩x26/桂馬x4
koma list = 飛x2, 角x2, 金x6, 歩x26, 桂x4, □x41,
PRINT_STEP = 500000000

kawazu/exec3

START: 2014年  4月 24日 木曜日 15:22:34 JST
END:   2014年  4月 29日 火曜日 04:08:29 JST

解は2個

No = 1
+------------------+
|金■歩歩歩歩歩■金|
|■■■■■■■飛■|
|金■歩歩歩歩歩■歩|
|■飛■■■■■■■|
|歩■歩歩歩歩歩■金|
|■■■桂■桂■■■|
|金■歩■歩■歩■歩|
|■■■歩■歩■■桂|
|金■歩角歩角歩■桂|
+------------------+
No = 2
+------------------+
|金■歩歩歩歩歩■金|
|■■■■■■■飛■|
|金■歩歩歩歩歩■歩|
|■飛■■■■■■■|
|歩■歩歩歩歩歩■金|
|■■■桂■桂■■■|
|歩■歩■歩■歩■金|
|桂■■歩■歩■■■|
|桂■歩角歩角歩■金|
+------------------+

-->



kawazu-no3:
<!--
leng = 81
koma = 40
masu limit = 6
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 将棋オリジナル/最後が桂馬/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x9, 歩x9, 桂x2, 軽x2, 香x2, 京x2, □x41,
PRINT_STEP = 500000000

kawazu: (別プロセスと並列実行)
START: 2014年  4月 24日 木曜日 14:34:06 JST
END:   2014年  4月 24日 木曜日 16:21:16 JST

KUMIAWASE = 1264284
-->


<!--そのため、空きマスが6個以上ある配置を対象に検索を行なう。実際は前述の
「石」が6個あると想定してコードを作成する。

飛車角王は上下対象の利き筋であるため、それ以外の駒のみ敵陣を考慮すれば良い。(以降敵陣の駒を先頭にrを付けて
表す。敵陣の「金将」は「r金将」と書く。) 
<BLOCKQUOTE>
飛車x2, 角行x2, 王将x2, 金将x2, 銀将x2, 桂馬x2, 香車x2,  歩兵x9, <BR>
金将x2, r銀将x2, r桂馬x2, r香車x2, r歩兵x9, 石x6
</BLOCKQUOTE>
上記14種類の駒を検討すれば良い。<P>

この盤面の簡略化を考えるために追加で以下の駒を定義する。

<UL>
<LI> 新たな駒を定義
<UL>
<LI> 捨: 上下左右1駒だけ利き筋の駒。別の表現をすれば、飛車で上下左右1マスだけに制限したもの。<BR>
(「捨」は「十」の難しい表記)
</UL>
</UL>
そして、金将x4と王x2の合計6枚を割り当てる。また桂馬は石とみなす。まとめると以下のように簡略化する。
<BLOCKQUOTE>
飛車x2, 角行x2, 拾x6, 歩兵x13, r歩兵x13<BR>
加えて、石x10
</BLOCKQUOTE>-->
<!--

石は空きマス10個とする。
search function = 10
leng = 81
koma = 36
masu limit = 10
board class = 3
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 簡略版/飛車角/捨x6/歩x13/r歩13/MASU_LIMIT=4/簡略版/後手有り
koma list = 飛x2, 角x2, 拾x6, 符x13, 歩x13, □x45,

pluto44:
START: 2014年  4月 22日 火曜日 18:48:04 JST
END:   2014年  4月 22日 火曜日 19:00:09 JST

file: zenkai-kan2.txt.gz

検索の結果296338通りの解
-->
<!-
<BLOCKQUOTE>
飛車x2, 角行x2, 王将x2, 金将x2, 銀将x2, 桂馬x2, 香車x2,  歩兵x9, <BR>
金将x2, r銀将x2, r桂馬x2, r香車x2, r歩兵x9, 石x5
</BLOCKQUOTE>
-->
<!--
leng = 81
koma = 40
masu limit = 5
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 簡略版/飛車角/捨x6/歩x13/r歩13/桂x2/r桂x2/簡略版/後手有り
koma list = 飛x2, 角x2, 拾x6, 符x13, 歩x13, 桂x2, 軽x2, □x41,
PRINT_STEP = 500000000

いっぱいデータが出てくるので、解析を同時にやる。

igisu40:exec2
コマンド: date; ./search40 | perl ../count_komaiti2.pl > out.txt; date
START: 2014年  4月 27日 日曜日 20:34:58 JST
END:   中断

MEMO: perlの方が時間がかかっている気配。。

  -> 中断

-->
<!--
leng = 81
koma = 40
masu limit = 5
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 香車無しで, 最後が桂馬/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x11, 歩x11, 桂x2, 軽x2, □x41,

#pluto44:
#START: 2014年  4月 22日 火曜日 21:18:55 JST
#END:  23日の朝3時ごろログが2Gオーバーでエラー



-->


<!--
leng = 81
koma = 40
masu limit = 5
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 最後が桂馬/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x9, 歩x9, 桂x2, 軽x2, 香x2, 京x2, □x41,

#kawazu: (別プロセスと並列実行)
#START: 2014年  4月 23日 水曜日 18:45:33 JST
#END:   24時間経過後、ログが26G超えたので強制停止

#igisu40/exec3
#$ date; ./search40 | perl ../count_komaiti2.pl > out.txt; date
#
#START: 2014年  4月 27日 日曜日 21:36:00 JST
#END  : -> 中断


再度、大駒移動時コードを有効にして実行。

leng = 81
koma = 40
masu limit = 5
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
大駒位置移動時のみ表示
Koma list Comment: 将棋オリジナル/最後が桂馬/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x9, 歩x9, 桂x2, 軽x2, 香x2, 京x2, □x41,
PRINT_STEP = 500000000


igisu40/exec7

START: 2014年  4月 29日 火曜日 21:29:22 JST
END:   2014年  5月 14日 水曜日 15:46:11 JST

ERROR: intがOverlowしている

KUMIAWASE = -556443597

DOC/igisu40-exec7-bassui.txt  
  -> No.7とNo.8の間でoverflowしているため、角飛車の位置が同じのが出ている。

DOC/igisu40-exec7-uniq.txt
  -> No.7はおそらく値が+2^32が正しい値。

  間違い: Total = 942997194　
  正しい: Total = 5237964490

  間違い: KUMIAWASE = 3738523699
  正しい: KUMIAWASE = 8033490995

kawazu/exec14
START: 2014年  5月 14日 水曜日 17:57:38 JST
END:   2014年  6月 14日 水曜日 13:53:37 JST

overflowしないように修正して再度。
g++4.8.1を使用

KUMIAWASE = 8033490995
  -> igisu40/exec7の修正後の値と同じ

  cat search40.txt  | perl ../conv_printable.pl  > ../DOC/kawazu-exec14-bassui.txt
  cat search40.txt  | perl ../conv_printable2.pl > ../DOC/kawazu-exec14-uniq.txt

  ->  igisu40/exec7のオーバーフローの修正値の予想通りの値になる。

-->

<!--
歩が10枚と想定した簡略盤, 
masu_limitの6のうち4は石x4
leng = 81
koma = 38
masu limit = 6
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 簡略版/飛車角/捨x6/歩x14/r歩14/MASU_LIMIT=4/簡略版/後手有り
koma list = 飛x2, 角x2, 拾x6, 符x14, 歩x14, □x43,
PRINT_STEP = 500000000

kawazu/exec5: 他プロセスと同時実行
START: 2014年  4月 24日 木曜日 17:39:42 JST
END:   2014年  4月 25日 金曜日 17:05:38 JST

KUMIAWASE = 15,670,628  多すぎ。

$ cat search40.txt | perl ../count_komaiti2.pl > out.txt

$ grep Total out.txt   |wc
  -> 139種類

Totalの確認

$ echo "0 " `grep Total out.txt  | awk '{print "+" $3}'` | bc  
KUMIAWASEと同じ事を確認。

集計結果は
   ./DOC/kawazu-exec5.txt

-->
<!--
leng = 81
koma = 42
masu limit = 3
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 歩x10/符x10/最後が桂馬/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x10, 歩x10, 桂x2, 軽x2, 香x2, 京x2, □x39, 
PRINT_STEP = 500000000

kawazu: exec6

START: 2014年  4月 25日 金曜日 19:46:16 JST
END:   2014年  4月 27日 日曜日 15:25:37 JST

KUMIAWASE = 20,870,640

$ cat search40.txt | perl ../count_komaiti2.pl　> out.txt

$ grep Total out.txt   |wc
  -> 10種類

$ echo "0 " `grep Total out.txt  | awk '{print "+" $3}'` | bc  
KUMIAWASEと同じ事を確認。

集計結果は
   ./DOC/kawazu-exec6.txt

-->
<!--
歩が10枚、空きマス5

leng = 81
koma = 41
masu limit = 5
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 最後が歩10/桂馬/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x9, 歩x10, 桂x2, 軽x2, 香x2, 京x2, □x40,
PRINT_STEP = 500000000

kawazu/exec7

START: 2014年  4月 27日 日曜日 22:56:46 JST
END: 2014年  4月 28日 月曜日 00:00:52 JST
  -> 解は無し。
-->
<!--
歩が10枚、空きマス4

leng = 81
koma = 41
masu limit = 4
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 最後が歩10/桂馬/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x9, 歩x10, 桂x2, 軽x2,  香x2, 京x2, □x40,
PRINT_STEP = 500000000

kawzu/exec8
START: 2014年  4月 28日 月曜日 00:13:51 JST
END:  実行中, 中断(5/1. 19:30,), disk溢れ

-->
<!--
行き所無し。
駒は標準。

leng = 81
koma = 40
masu limit = 0
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
行き所の無い駒禁止。
Koma list Comment: 将棋オリジナル/後手有り
koma list = 飛x2, 角x2, 王x2, 香x2, 京x2, 金x2, 琴x2, 銀x2, 吟x2, 桂x2, 軽x2, 符x9, 歩x9, □x41, 
PRINT_STEP = 500000000

igisu40/exec4

START: 2014年  4月 28日 月曜日 21:32:24 JST
END: 解が多そう。中断

-->

<!--
leng = 81
koma = 40
masu limit = 2
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
行き所の無い駒禁止。
Koma list Comment: 将棋オリジナル/後手有り
koma list = 飛x2, 角x2, 王x2, 香x2, 京x2, 金x2, 琴x2, 銀x2, 吟x2, 桂x2, 軽x2, 符x9, 歩x9, □x41, 
PRINT_STEP = 500000000

igisu40/exec5

START: 2014年  4月 28日 月曜日 21:54:39 JST
END:   2014年  6月 18日 水曜日 00:03:36 JST

出力:
KUMIAWASE = 2072875

DOC/igisu40-exec5.txt

-->
<!--
leng = 81
koma = 40
masu limit = 3
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
行き所の無い駒禁止。
Koma list Comment: 将棋オリジナル/後手有り
koma list = 飛x2, 角x2, 王x2, 香x2, 京x2, 金x2, 琴x2, 銀x2, 吟x2, 桂x2, 軽x2, 符x9, 歩x9, □x41,
PRINT_STEP = 500000000

igisu40/exec6

START: 2014年  4月 29日 火曜日 12:09:01 JST
END:   2014年  5月  5日 月曜日 18:32:31 JST

KUMIAWASE = 15291

全てマス残り=3で、4は無し。

出力
 DOC/igisu40-exec6-komaiti2.txt
 DOC/igisu40-exec6.txt.gz

-->

<!--
leng = 81
koma = 41
masu limit = 0
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
行き所の無い駒禁止。
大駒位置移動時のみ表示
Koma list Comment: 最後が/符x9/歩x10/桂馬/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x9, 歩x10, 桂x2, 軽x2, 香x2, 京x2, □x40,
PRINT_STEP = 500000000

igisu40/exec8

START: 2014年  5月  5日 月曜日 22:00:29 JST
END:   (中断: 2014/7/18)


-->

<!--
leng = 81
koma = 41
masu limit = 0
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
行き所の無い駒禁止。
大駒位置移動時のみ表示
Koma list Comment: 最後が/桂x3/軽x2/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x9, 歩x9, 桂x3, 軽x2, 香x2, 京x2, □x40,
PRINT_STEP = 500000000

igisu40/exec9

START: 2014年  5月  5日 月曜日 21:59:58 JST
END:   (中断: 2014/7/18)

<!--
leng = 81
koma = 40
masu limit = 0
board class = 3
search function = 8
Koma list Comment: 飛車x2/角x2/桂馬x4/歩x26
koma list = 飛x2, 角x2, 桂x4, 歩x32, □x41,
PRINT_STEP = 500000000

kawazu/exec9

START: 2014年  4月 29日 火曜日 12:32:46 JST
END  : 実行中 -> 中断。

これはkawazu/exec2の最後が桂馬と比較して早いか確認したが、やっぱり遅い。

-->

<!--
将棋オリジナル。　念のため再試。

leng = 81
koma = 40
masu limit = 0
board class = 3
search function = 10
Koma list Comment: 将棋オリジナル/最後が/桂馬/香車
koma list = 飛x2, 角x2, 王x2, 金x4, 銀x4, 歩x18, 桂x4, 香x4, □x41,
PRINT_STEP = 500000000

kawazu/exec11

START: 2014年  4月 29日 火曜日 15:28:09 JST
END:   2014年  6月 20日 金曜日 00:00:20 JST

KUMIAWASE = 1860

出力:
kawazu-exec11.txt

なおzenkai2.txtと比較して出力の順番が異なる模様。
cat ../TeX/zenkai2.txt | perl ../conv_line.pl| sort > t
cat kawazu-exec11.txt | perl ../conv_line.pl | sort > t2
diff t t2 
  -> 問題無し
-->

<!--
leng = 81
koma = 44
masu limit = 0
board class = 3
search function = 40
後手有り。表示の都合で以下のように表記
> 後手/香 :京, 後手/金 :琴, 後手/銀 :吟, 後手/桂 :軽, 後手/歩 :符
> その他の駒は先手後手で表示区別無し。
Koma list Comment: 最後が歩x11/符x11/最後が桂馬/香車/後手有
koma list = 飛x2, 角x2, 王x2, 金x2, 琴x2, 銀x2, 吟x2, 符x11, 歩x11, 桂x2, 軽x2, 香x2, 京x2, □x37,
PRINT_STEP = 500000000

kawazu/exec12

START: 2014年  5月  1日 木曜日 20:22:49 JST
END:   2014年  5月 10日 土曜日 19:25:50 JST

KUMIAWASE = 320872

出力
kawazu-exec12.txt.gz
kawazu-exec12-komaiti2.txt

-->

<!--
念のための再試

koma = 40
masu limit = 0
board class = 3
search function = 10
Koma list Comment: 将棋オリジナル/最後が/桂馬/香車
koma list = 飛x2, 角x2, 王x2, 金x4, 銀x4, 歩x18, 桂x4, 香x4, □x41, 
PRINT_STEP = 500000000

TIME_TEST2: 初期状態: 既知の解で飛車2枚/角2枚のみ並べた状態

igisu40/exec10

START: 2014年  5月 15日 木曜日 12:28:42 JST
END:   2014年  5月 15日 木曜日 13:40:38 JST

  -> 1時間11分

KUMIAWASE = 1860

-->
<!--
歩が最後と桂馬香車が最後(igisu/exec10)で速度比較

koma = 40
masu limit = 0
board class = 3
search function = 10
Koma list Comment: 将棋オリジナル
koma list = 飛x2, 角x2, 王x2, 香x4, 金x4, 銀x4, 桂x4, 歩x18, □x41, 
PRINT_STEP = 500000000

TIME_TEST2: 初期状態: 既知の解で飛車2枚/角2枚のみ並べた状態

igisu40/exec11

START: 2014年  5月 15日 木曜日 15:09:09 JST
END:   2014年  5月 15日 木曜日 18:25:40 JST

  -> 3時間16分

KUMIAWASE = 1860


-->

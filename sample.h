// yousoは再帰中に破壊される。

// prefixがorg_ のは駒が省略などされてない。

// 飛車, 角, 王は先手後手の区別無し。
// 実装の都合上、search5以降は最後はFUである必要あり。rFUは不可。
// 実装の都合上、search7以降は最初はKAKUである必要あり。

#ifdef  GEN_GOTE // 後手有り

Youso org_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KYOU,2},{rKYOU,2},{KIN,2},{rKIN,2},
   {GIN,2},{rGIN,2},{KEI,2},{rKEI,2},{rFU,9},{FU,9},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル/後手有り"
};

Youso org_kaku_youso_r = {
  {{KAKU,2},{HISYA,2},{OH,2},{KYOU,2},{rKYOU,2},{KIN,2},{rKIN,2},
   {GIN,2},{rGIN,2},{KEI,2},{rKEI,2},{rFU,9},{FU,9},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル/角が先/後手有"
};

Youso org_last_kyou_fu_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {KEI,2},{rKEI,2},{KYOU,2},{rKYOU,2},{rFU,9},{FU,9},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル/最後が、後手香,先手香,後手歩,先手歩 / 後手有"
};


Youso kyou_nashi_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {KEI,2},{rKEI,2},{rFU,11},{FU,11},{YOUSO_TERMINAL, 0}},
  "香車無しで, 後手歩が11個, 先手歩が11個/後手有"
};

Youso kyou_nashi_last_kei_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {rFU,11},{FU,11},{KEI,2},{rKEI,2},{YOUSO_TERMINAL, 0}},
  "香車無しで, 最後が桂馬/後手有"
};

Youso org_last_kei_kyou_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {rFU,9},{FU,9},{KEI,2},{rKEI,2},{KYOU,2},{rKYOU,2},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル/最後が桂馬/香車/後手有"
};

Youso last_fu10_kei_kyou_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {rFU,9},{FU,10},{KEI,2},{rKEI,2},{KYOU,2},{rKYOU,2},{YOUSO_TERMINAL, 0}},
  "最後が歩10/桂馬/香車/後手有"
};

Youso kyou_nashi_fu10_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {KEI,2},{rKEI,2},{rFU,11},{FU,10},{YOUSO_TERMINAL, 0}},
  "香車無しで, 後手歩が11個, 先手歩が1個不足10個/後手有"
};

Youso last_fufu_10_kei_kyou_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {rFU,10},{FU,10},{KEI,2},{rKEI,2},{KYOU,2},{rKYOU,2},{YOUSO_TERMINAL, 0}},
  "歩x10/符x10/最後が桂馬/香車/後手有"
};

Youso last_fu_11_kei_kyou_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {rFU,11},{FU,11},{KEI,2},{rKEI,2},{KYOU,2},{rKYOU,2},{YOUSO_TERMINAL, 0}},
  "最後が歩x11/符x11/最後が桂馬/香車/後手有"
};

Youso last_fu_10_kei_kyou_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {rFU,9},{FU,10},{KEI,2},{rKEI,2},{KYOU,2},{rKYOU,2},{YOUSO_TERMINAL, 0}},
  "最後が/符x9/歩x10/桂馬/香車/後手有"
};

Youso last_kei3_kyou_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {rFU,9},{FU,9},{KEI,3},{rKEI,2},{KYOU,2},{rKYOU,2},{YOUSO_TERMINAL, 0}},
  "最後が/桂x3/軽x2/香車/後手有"
};

#ifdef KANRYAKU
Youso kanr_org_youso = {
  {{TATE,2},{ISHI,6},{FU,32},{YOUSO_TERMINAL, 0}},
  "簡略版オリジナル, 縦x2, 石x6, 歩x32/簡略版"
};

Youso kan_org_last_ishi_youso = {
  {{TATE,2},{FU,32},{ISHI,6},{YOUSO_TERMINAL, 0}},
  "簡略版オリジナル/last石, 歩x32/簡略版"
};

Youso kan_org_last_ishi_youso_r = {
  {{TATE,2},{rFU,16},{FU,16},{ISHI,6},{YOUSO_TERMINAL, 0}},
  "簡略版オリジナル/last石, 歩x16, r歩x16/簡略版"
};

Youso kan_tate6_last_ishi_youso_r = {
  {{TATE,6},{rFU,6},{FU,6},{ISHI,6},{YOUSO_TERMINAL, 0}},
  "簡略版オリジナル/last石, 歩x6, r歩x6/簡略版"
};

Youso kan_ishinashi_youso = {
  {{TATE,2},{FU,32},{YOUSO_TERMINAL, 0}},
  "簡略版/石無し/簡略版"
};

Youso kan_hisya_ishi_fu_youso = {
  {{HISYA,2},{ISHI,6},{FU,32},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車/石/歩/簡略版"
};

Youso kan_hisya_kaku_kei_fu_youso = {
  {{HISYA,2},{KAKU,2},{KEI,4},{FU,32},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角桂馬, 歩x32/簡略版"
};

Youso kan_hisya_kaku_ishi_fu_youso = {
  {{HISYA,2},{KAKU,2},{ISHI,4},{FU,32},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角,石4, 歩x32/簡略版"
};


Youso kan_hisya_kaku_jyu_fu_youso_r = {
  {{HISYA,2},{KAKU,2},{JYU, 6},{rFU, 13},{FU,13},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角/捨x6/歩x13/r歩13/MASU_LIMIT=4/簡略版/後手有り"
};

/*
  石の代わりにMASU_LIMIT=4 という事。
 */
Youso kan_hisya_kaku_jyu_fu14_youso_r = {
  {{HISYA,2},{KAKU,2},{JYU, 6},{rFU, 14},{FU,14},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角/捨x6/歩x14/r歩14/MASU_LIMIT=4/簡略版/後手有り"
};

Youso kan_hisya_kaku_jyu_fu_kei_youso_r = {
  {{HISYA,2},{KAKU,2},{JYU, 6},{rFU, 13},{FU,13},{KEI,2},{rKEI,2},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角/捨x6/歩x13/r歩13/桂x2/r桂x2/簡略版/後手有り"
};

Youso kan_hisya_kaku_ishi_fu_youso_r = {
  {{HISYA,2},{KAKU,2},{ISHI,5},{rFU,16},{FU,16},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角,石x5,歩x13,r歩13/簡略版/後手有"
};

Youso kan_kyou_nashi_ishi_youso_r = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,2},{rKIN,2},{GIN,2},{rGIN,2},
   {KEI,2},{rKEI,2},{rFU,11},{ISHI,1},{FU,11},{YOUSO_TERMINAL, 0}},
  "香車無しで, 石x1, 後手歩が11個, 先手歩が11個/後手有"
};

/* 簡略番 index2.html用 */

Youso tate8_fu5_youso = {
  {{TATE,8},{FU,5},{YOUSO_TERMINAL, 0}},
  "簡略番/index2.html/縦x8, 歩x5"
};

Youso tate8_ish6_fu2_youso = {
  {{TATE,8},{ISHI,6},{FU,2},{YOUSO_TERMINAL, 0}},
  "簡略番/index2.html/縦x8, 石x6, 歩x2"
};

Youso tate7_ish6_fu7_youso = {
  {{TATE,7},{ISHI,6},{FU,7},{YOUSO_TERMINAL, 0}},
  "簡略番/index2.html/縦x7, 石x6, 歩x7"
};

Youso tate6_ish6_fu12_youso = {
  {{TATE,6},{ISHI,6},{FU,12},{YOUSO_TERMINAL, 0}},
  "簡略番/index2.html/縦x7, 石x6, 歩x12"
};


#endif /* KANRYAKU */

#else  // 後手無し

Youso org_youso = {
  {{HISYA,2},{KAKU,2},{OH,2},{KYOU,4},{KIN,4},{GIN,4},{KEI,4},{FU,18},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル"
};

Youso org_kaku_youso = {
  {{KAKU,2},{HISYA,2},{OH,2},{KYOU,4},{KIN,4},{GIN,4},{KEI,4},{FU,18},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル/角が先"
};

Youso org_rev_youso = {
  {{FU,18},{KEI,4},{GIN,4},{KIN,4},{KYOU,4},{OH,2},{KAKU,2},{HISYA,2},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル/逆置き"
};

Youso org_last_kyou_fu_youso = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,4},{GIN,4},{KEI,4},{KYOU,4},{FU,18},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル/最後が、香,歩"
};

Youso org_last_kei_kyou_youso = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,4},{GIN,4},
   {FU,18},{KEI,4},{KYOU,4},{YOUSO_TERMINAL, 0}},
  "将棋オリジナル/最後が/桂馬/香車"
};

Youso hisya_kaku_fu_kei_youso = {
  {{HISYA,2},{KAKU,2},{FU,32},{KEI,4},{YOUSO_TERMINAL, 0}},
  "飛車x2/角x2/歩x32/桂馬x4"
};

Youso hisya_kaku_kin_fu_kei_youso = {
  {{HISYA,2},{KAKU,2},{KIN,6},{FU,26},{KEI,4},{YOUSO_TERMINAL, 0}},
  "飛車x2/角x2/金x6/歩x26/桂馬x4"
};

Youso hisya_fu_kaku_kei_youso = {
  {{HISYA,2},{FU,32},{KAKU,2},{KEI,4},{YOUSO_TERMINAL, 0}},
  "飛車x2/歩x32/角x2/桂馬x4"
};


Youso kyou_nashi_youso = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,4},{GIN,4},{KEI,4},{FU,22},{YOUSO_TERMINAL, 0}},
  "香車無しで歩が22個"
};

#endif

Youso hisya_2_mai_youso = {
  {{HISYA,2},{YOUSO_TERMINAL, 0}},
  "飛車2枚/飛車の配置生成確認用/歩がないので一部で利用不可"
};

Youso hisya_2_kaku_2_youso = {
  {{HISYA,2},{KAKU,2},{YOUSO_TERMINAL, 0}},
  "飛車2/角2/歩がないので一部で利用不可"
};



Youso fu10_youso = {
  {{HISYA,2},{KAKU,2},{OH,2},{KYOU,4},{KIN,4},{GIN,4},{KEI,4},{FU,10},{YOUSO_TERMINAL, 0}},
  "歩が10個/動作確認に良い"
};

Youso fu6_youso = {
  {{HISYA,2},{KAKU,2},{OH,2},{KYOU,4},{KIN,4},{GIN,4},{KEI,4},{FU,6},{YOUSO_TERMINAL, 0}},
  "歩が10個/動作確認に良い"
};


Youso test1_youso = {
  {{HISYA,4},{KAKU,4},{OH,9},{YOUSO_TERMINAL, 0}},
  "飛車/4, 角/4, 王9/動作確認に良い。"
};

Youso test2_youso = {
  {{HISYA,2},{KAKU,6},{FU,27},{YOUSO_TERMINAL, 0}},
  "飛車/4, 角/6, 歩27/動作確認に良い。"
};

Youso ue_first_keinashi_youso = {
  {{HISYA,2},{KAKU,2},{OH,2},{KIN,4},{KEI,4},{GIN,4},{FU,22},{YOUSO_TERMINAL, 0}},
  "香車を歩とみなす + KEIとGINを入れ替え"
};

Youso hisya_kaku_fu32_youso = {
  {{HISYA,2},{KAKU,2},{FU,32},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角/歩x32/MASU_LIMIT=4/簡略版"
};

Youso hisya_kaku_fu28_youso = {
  {{HISYA,2},{KAKU,2},{FU,28},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角/歩x28/簡略版"
};

Youso hisya_kaku_ou4_youso = {
  {{HISYA,2},{KAKU,2},{OH,4},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角/王x4/簡略版"
};

Youso hisya_kaku_ou1_youso = {
  {{HISYA,2},{KAKU,2},{OH,1},{YOUSO_TERMINAL, 0}},
  "簡略版/飛車角/王/簡略版"
};

Youso hisya2_kaku1_ou1_youso = {
  {{HISYA,2},{KAKU,1},{OH,1},{YOUSO_TERMINAL, 0}},
  "簡略版/飛2/角1/王1/簡略版"
};

Youso hisya_kaku_kei_fu_youso = {
  {{HISYA,2},{KAKU,2},{KEI,4},{FU,32},{YOUSO_TERMINAL, 0}},
  "簡略版/飛2/角2/桂4/歩32/簡略版"
};

//  駒を事前に数枚並べておく時の位置
PreSetPos hisya_kaitou = {
  {{5,1}, {7,7}, {-1, -1}},
  "既知の解で飛車２枚のみ並べた状態"};

PreSetPos hisya_kaku_kaitou = {
  {{5,1}, {7,7}, {0,3}, {0,5}, {-1, -1}},
  "既知の解で飛車2枚/角2枚のみ並べた状態"};

PreSetPos tate8_pos = {
  {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0},{6,0},{7,0},{-1, -1}},
  "簡略番/index2.html/縦x8"};

PreSetPos tate7_pos = {
  {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0},{6,0},{-1, -1}},
  "簡略番/index2.html/縦x7"};

PreSetPos tate6_pos = {
  {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {-1, -1}},
  "簡略番/index2.html/縦x6"};

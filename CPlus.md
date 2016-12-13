## C＋で詰まったところ

1. インスタンスの作成と削除
	1. インスタンス化メモリの確保 
	'''
	インスタンス化(メモリの確保)
	Vector *position = new Vector(0,0,0);
	'''

	1. メモリ解放
	'''
	解放
	delete u;
	'''

1. ヘッダーファイルの使い方
	1. 宣言ファイルの基本
		1. 宣言のみ
		1. クラスの指定が必要
		1. public: privateもここで設定


1. 設計
	1. ボール一つ一つがVectorを持つ


1. Vecotr
'''
//Vector3テスト場所
//メモリの利用
Vector *u = new Vector(1,2,3);
Vector *v = new Vector(4,1,3);
cout<<"u="<<*u<<"\n";
cout<<"v="<<*v<<"\n";
cout<<"-v="<<-*v<<"\n";
cout<<"u+v="<<*u + *v<<"\n";
cout<<"u-v="<<*u - *v<<"\n";
cout<<"u*v="<<*u * *v<<"\n";

*u+=Vector(1,1,3);
*v-=Vector(1,1,3);
cout<<"u+(1,1)="<<*u<<"\n";
cout<<"v-(1,1)="<<*v<<"\n";

//メモリ解放

delete v;

'''

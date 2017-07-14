/************************************************************
http://qiita.com/jkr_2255/items/b2c488c466e76f7069b1
	ふつう、C言語で動的確保をしようと思えばmalloc～freeの流れですが、標準関数ではないものの多くの環境にalloca、あるいは_allocaという関数があります。
	この関数の特徴としては、「メモリ領域をスタックに取る」ということがあります。そのため、
		- 使い終わった後のfreeの必要がない（というより、してはならない）
		- スコープを抜ければ自動で解放される
		- 返り値としてこのメモリ領域へのポインタを返してはいけない
		- オーバーヘッドが少ない (ヒープは遅い)
		- アセンブラで埋め込み展開されるような環境もある（alloca関数へのポインタを取れない）
		- 巨大な領域を取るとスタックオーバーフローで死ぬ
	というような特徴があります。
	
	この前使った場面では、実行時までサイズが決まらない配列を確保する必要があったのですが、その配列自体は外からアクセスする必要がなく、
	そして処理全体に対するmallocのオーバーヘッドがかなりのものになる、という状況だったので、「必要な長さが小さな時にはallocaに切り替える」ようにしたところ、
	3割程度高速化した、ということがありました。
************************************************************/
#include <stdio.h>
#include <string.h>
#include <alloca.h>


/************************************************************
************************************************************/

int main()
{
	char* p = (char*)alloca(100 * sizeof(char));
	
	strcpy(p, "saijo");
	
	printf("%s\n", p);
	
	return 0;
}


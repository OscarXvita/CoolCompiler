// CoolLexer.cpp : 定义控制台应用程序的入口点。
//

#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define Digital_Range Rfc('0'),Rfc('9')
#define Up_char_Range Rfc('A'),Rfc('Z')
#define Down_char_Range Rfc('a'),Rfc('z')
#define All 0,99
using namespace std;
const int maxll = 512;
const int maxm = 1e05;
char cur[maxll];
int NUM = 0;
bool st_comments;
ofstream OUT;
struct  ele {
	ele *next[100];
	int no;//记录状态 若为0则为非终止状态 为-2则为待判断是否是指定的关键词
}pool[maxm];
int Rfc(char a)//对所读取的字符进行映射
{
	if (a == ' ' || a == '\n' || a == '\0') return 0;
	return a - 31;
}
int tot = -1;
struct AutoMachine {
	ele *root;
	char Buffer[260];
	int ll_b = 0;
	AutoMachine()//初始化
	{

		root = &pool[++tot];
		root->next[0] = root;
		memset(Buffer, 0, sizeof(Buffer));
	}
	ele *newNode()//建立新的结点
	{
		ele *tem = &pool[++tot];
		tem->next[0] = tem;
		return tem;
	}
	void default_link(ele *cur, int down, int up, ele *to)
	{
		for (int i = down; i <= up; i++) cur->next[i] = to;
	}
	void Build_up()
	{
		default_link(root, Digital_Range, root + 2);//建立标识符以及关键词的识别分支
		default_link(root, Down_char_Range, root + 1);
		default_link(root, Up_char_Range, root + 17);
		root->next[Rfc('_')] = root + 1;
		root->next[Rfc('\'')] = root + 8;
		root->next[Rfc('\"')] = root + 10;

		default_link(root + 1, Digital_Range, root + 1);
		default_link(root + 1, Up_char_Range, root + 1);
		default_link(root + 1, Down_char_Range, root + 1);
		(root + 1)->next[Rfc('_')] = root + 1;
		(root + 1)->no = -2;

		default_link(root + 2, Digital_Range, root + 2);//建立常数的判断分支
		(root + 2)->next[Rfc('.')] = root + 7;
		(root + 2)->no = 3;
		default_link(root + 7, Digital_Range, root + 6);
		(root + 7)->no = 3;
		default_link(root + 6, Digital_Range, root + 6);
		(root + 6)->no = 3;

		default_link(root + 8, All, root + 9);//转义字符的处理等待解决 建立普通字符的识别分支
		(root + 9)->next[Rfc('\'')] = root + 15;
		(root + 15)->no = 1;

		default_link(root + 10, All, root + 11);//Ê¶±ð×Ö·û´´·ÖÖ§
		default_link(root + 11, All, root + 11);
		(root + 10)->next[Rfc('\"')] = root + 16;
		(root + 11)->next[Rfc('\"')] = root + 16;
		(root + 16)->no = 2;

		default_link(root + 17, Digital_Range, root + 17);
		default_link(root + 17, Up_char_Range, root + 17);
		default_link(root + 17, Down_char_Range, root + 17);
		(root + 17)->no = 4;
		(root + 17)->next[Rfc('_')] = root + 17;

		tot += 20;
	}
	void Build(char *Word, int no)//对于给定的KT表与PT表 建立识别状态图
	{
		ele *tem = root;
		int ll = strlen(Word);
		for (int i = 0; i < ll; i++)
		{
			int x = Rfc(Word[i]);
			if (tem->next[x] == NULL) {
				tem->next[x] = newNode();
				tem = &pool[tot];
			}
			else tem = tem->next[x];;
		}
		tem->no = no;
	}
	int Find(char *Word)//-1 equal to fail 用于判断当前输入的字符串对应的是关键词或是iT标识符
	{
		ele *cur = root;
		int ll = strlen(Word);
		for (int i = 0; i < ll; i++)
		{
			if (cur->next[Rfc(Word[i])] == NULL) return 0;
			else cur = cur->next[Rfc(Word[i])];
		}
		return cur->no;
	}
	int Working(char *Words, AutoMachine &Key)//工作的主函数 Words为输入的函数 Key为KT字符串识别所用的trie树
	{
		ele *cur = root;
		int ll_b = 0;
		int x = 0;;
		memset(Buffer, 0, sizeof(Buffer));
		while (*Words != '\0' && (*Words == '\t' || *Words == ' '))
		{
			Words++;
			x++;
		}
		if (*Words == '(' && *(Words + 1) == '*')
		{
			st_comments = true;
			x += 2; Words += 2;
		}
		while (st_comments == true && *Words != '\0')
		{
			if (*Words == '*' && *(Words + 1) == ')')
			{
				st_comments = false;
				Words += 2;
				x += 2;
				return x;
			}
			else
			{
				Words++;
				x++;
			}
		}
		if (strlen(Words) == 0 || st_comments) return x;
		if (*Words == '-' && *(Words + 1) == '-')
		{
			while (*Words != '\0')
			{
				Words++;
				x++;
			}
			return x;
		}
		while (1)
		{
			if (*Words== '\0' || cur->next[Rfc(*Words)] == NULL) {
				if (cur == root) {
					OUT << "#" << NUM << " ";
					OUT << "-1";
					OUT.close();
					exit(-1);
				}
				else {
					if (cur->no > 0)
					{
						OUT << "#" << NUM << " " << cur->no;
						Buffer[ll_b] = '\0';
						if (cur->no <= 4)
							OUT << " " << Buffer;
						OUT << endl;
					}
					if (cur->no == -2) {
						while (Buffer[ll_b - 1] == '\t' || Buffer[ll_b - 1] == '\n' || Buffer[ll_b - 1] == ' ') ll_b--;
						Buffer[ll_b] = '\0';
						int tmp_no = Key.Find(Buffer);
						OUT << "#" << NUM << " " << tmp_no;
						if (tmp_no == 0)
							OUT << " " << Buffer;
						OUT << endl;
					}
					if (cur->no == 0) {
						OUT << "#" << NUM << " ";
						OUT << "-1";
						OUT.close();
						exit(-2);
					}
					break;
				}
			}
		//	cout<<ll_b<<endl;
			cur = cur->next[Rfc(*Words)];
		//	cout<<ll_b<<endl;
			Buffer[ll_b++] = *Words;//若其可能为iT标识符或KT字符串，则对其创建备份以方便进行识别
			Words++;
			x++;
		}
		return x;
	}
};
int main(int n, char* argv[])
{
	string out_file = "lexer_result.txt";
	string in_file = "tmp.txt";

	switch (n)
	{
	case 1:
	{
		printf("Usage: CoolLexer FILEIN FILEOUT\n");
		printf("No input arguments. Fallback to tmp.txt and lexer_result.txt\n");
		break;
	}
	case 3:
	{
		out_file = argv[2];
		in_file = argv[1];
		break;
	}

	default:
	{
		printf("Wrong number of argument\n");
		printf("Usage: CoolLexer FILEIN FILEOUT\n");
		exit(1);
	}
	}

	ifstream IN;
	//OUT.open("lexer_result.txt");//将结果输出于result.txt
	OUT.open(out_file);//将结果输出于result.txt


	AutoMachine Key;

	memset(pool, 0, sizeof(pool));

	freopen("KT.txt", "r", stdin);//导入KT表，并建立对应的识别状态

	int no;

	while (scanf("%s%d", cur, &no) != EOF) Key.Build(cur, no);

	fclose(stdin);

	freopen("PT.txt", "r", stdin);//导入PT表，并建立对应的识别状态

	AutoMachine G;

	G.Build_up();

	while (scanf("%s%d", cur, &no) != EOF) G.Build(cur, no);

	fclose(stdin);

	//IN.open("tmp.txt");//读入待识别的源代码 并进行工作
	IN.open(in_file);
	if (IN.good())
	{


		st_comments = false;
		while (!IN.eof())
		{
			++NUM;
			IN.getline(cur, 500);
			char *tmp = cur;
			int ll = strlen(cur);
			if (ll == 0) continue;
			while (tmp - cur < ll) {
				tmp += G.Working(tmp, Key);
			}
		}
	}
	else
	{
		printf("ERROR: CANNOT OPEN INPUT FILE.");

	}
	IN.close();
	//OUT<<endl<<endl;
	//OUT<< "#"<< NUM<< " 10086";
	OUT.close();
	return 0;
}

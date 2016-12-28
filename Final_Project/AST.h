#ifndef AST_H_INCLUDED
#define AST_H_INCLUDED
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#include <cstdlib>
#include <vector>
using namespace std;
static const int pre_init_num = 1e05+10;
static int type_cnt(0);//用于给新加入的类型编号，同时记录类型表当中的数目
static int method_cnt(0);//用于给新加入的方法编号，同时记录全局当中方法的总数量
static int type_width[pre_init_num];//记录类型的字长
static map<string , int> type_map;
map<string , int> Const_string_value;//建立常量表，第二属性是其位长
map<string ,int > Const_value;//建立常量表，第二属性是位长
int Quad_no = 0;
string pra_name_tmp[20];
void add_const_value(string x)
{
    map<string, int>::iterator It;
    It = Const_value.find(x);
    if(It == Const_value.end())
        Const_value.insert(pair<string,int>(x,4));
    return;
}
void add_const_string(string x)
{
    map<string, int>::iterator It;
    It = Const_string_value.find(x);
    if(It == Const_string_value.end())
        Const_string_value.insert(pair<string,int>(x,x.size()-2));
    return;
}
struct Quad
{
    int no;
    string Action;//四元式所要进行的动作
    string First;//四元式当中的第一个操作数,为空时则为 "_"
    string Second;//四元式当中的第二个操作数， 为空时则为 "_"
    string Result;//四元式当中存储结果的位置
    Quad(int x,string _action = "", string _first = "", string _second = "", string _result = ""): no(x), Action(_action), First(_first), Second(_second), Result(_result){}
    void Out()
    {
        cout<<no<<":(  "<<Action<<"  , "<<First<<"  , "<<Second<<"  , "<<Result<<" )"<<endl;
    }
};

struct TypeNode//记录类型
{
    int son_cnt;
    //TypeNode *son[30];
    TypeNode *fa;
    vector<Quad> Init_Q;
    map<string , int> attribute_table;//第二属性记录的是其偏移地址
    map<string , string> attribute_type_table;//记录变量的类型
    map<string , int> method_table;//第二属性记录的是其在全局函数当中的编号，即记录位置，以方便后期处理
    int att_offset;
    int type_ref;
    string Tname;
    TypeNode()
    {
        son_cnt=0;
        fa = NULL;
        //memset(son, 0, sizeof(son));
        att_offset=0;
    }
    void Copy_initial(TypeNode *tmp);//复制初始化时的四元式
    void Build_son(TypeNode *tmp);//建立AST中的子结点
    void Copy_attribute_table(TypeNode *tmp);//从tmp结点中，复制其特征表
    bool Add_attribute(string Name, string Type);//添加特征，同时检查现用的特征表当中是否已经存在相应的同名的特征名
    bool Add_method(string Name, int pra_num, int* a, int Return_type);//添加方法名 若以存在同名的则检查是否满足重载规则,不满足-5\
    a存储的是每个参数类型的编号
    int Find_method(string Name);//没找到则返回-1
}pool[pre_init_num];

struct VarNode // 记录类型
{
    TypeNode* Type;
    int begin_offset;
    VarNode(): Type(0), begin_offset(0) {}
};

struct MethodNode
{
    TypeNode* Belong;//方法归属于哪个类
    int pra_num;//参数的数目
    string Name;
    string pra_NAME[20];
    TypeNode* pra_type[20];//各参数的类型
    TypeNode* Return_type;//返回值得类型

}method_pool[pre_init_num];

struct Var_linker
{
    TypeNode *T;
    int offset;
    Var_linker(TypeNode* x=NULL, int y=0): T(x),offset(y) {}
};

struct Div_scope
{
    Div_scope* pre_Div;//指向上一级Div的指针若为空， 说明其上一级即为类块
    int begin_offset;
    int tmp_length;//当前所占用的内存空间，记录下以方便退出的时候对其进行释放
    map< string, Var_linker*> tmp_var_table;//存储在当前块之中申明的变量，以及其相对的存储空间的位移大小
    map<int ,int > Const_value;//建立常量表，第二属性是其在符号表当中的位置
    map<string , int > Const_string_value;//建立常量表，第二属性是其在符号表当中的位置
    TypeNode* fa;
    Div_scope(): pre_Div(NULL), begin_offset(0), tmp_length(0), fa(NULL)
    {
        tmp_var_table.clear();
    }
    ~Div_scope()
    {
        map< string, Var_linker*>::iterator It;
        It=tmp_var_table.begin();
        while(It!=tmp_var_table.end())
        {
            free(It->second);
            It++;
        }
        tmp_var_table.clear();
        Const_value.clear();
    }
    int Find_var(string Name);//查找一个变量是否已经存在，当前不存在则去更外围的去查询，如果并不存在则返回-1 否则返回其偏移地址
    string Find_var_type(string Name);//返回其类型
    void Add_var(string Name, string Type);//在当前域之中添加名为NAME，类型为TYPE的变量
    int Find_const_value(int value);//查询一个常量是否已经存在，如果已经存在则返回其在常量表当中的偏移量，否则添加
    void Add_const_value(int x);//在常量表当中添加相应常量
};


TypeNode* Find_type(string Name);//查询一个类型是否被事先定义过，如果未被定义过则报错-2，定义过则返回其在类型映射表当中的位置
int Add_type(string Name);//在类型表当中插入相应名字的类型，如果被重定义过则报错-3，否则在映射表当中添加相应条目
void Enter_new_scope();//进入一个新的定义域
void Define_var(string Name);
bool check_fa_type(string x, string y);//检查名称为x的类是否存在名字为y的父类

TypeNode* Find_type(string Name)
{
    map<string, int> ::iterator tmp;
    tmp = type_map.find(Name);
    if(tmp == type_map.end())
    {
        //非法定义，该类型事先未被定义过
        return NULL;
    }
    return pool+tmp->second;
}
int Add_type(string Name)
{
    map<string, int> :: iterator tmp;
    tmp = type_map.find(Name);
    if(tmp != type_map.end())
    {
        //已被重定义过
        exit(-3);
    }
    type_map.insert(pair<string, int> (Name, type_cnt));
    pool[type_cnt].Tname = Name;
    return type_cnt++;
}
void TypeNode::Build_son(TypeNode *tmp)
{
    tmp->fa =this;
    //this->son[ ++this->son_cnt ] = tmp;
    tmp->Copy_attribute_table(this);
    tmp->Copy_initial(this);
}

void TypeNode::Copy_initial(TypeNode *tmp)
{
    int cnt = tmp->Init_Q.size();
    for(int i=0; i<cnt; i++)
    {
        this->Init_Q.push_back(tmp->Init_Q[i]);
    }
}

void TypeNode::Copy_attribute_table(TypeNode* tmp)
{
    map <string, int> :: iterator It;
    It=tmp->attribute_table.begin();
    while(It != tmp->attribute_table.end())
    {
        this->attribute_table.insert(*It);
        this->att_offset += It->second;
        ++It;
    }
    map <string, string> :: iterator Z;
    Z = tmp->attribute_type_table.begin();
    while(Z != tmp->attribute_type_table.end())
    {
        this->attribute_type_table.insert(*Z);
        ++Z;
    }
}
bool TypeNode::Add_attribute(string Name,string Type)
{
    map <string, int> :: iterator It;
    It = this->attribute_table.find(Name);
    if(It != this->attribute_table.end())
    {
        //说明当前特征名已存在，非法
        return false;
    }
    this->attribute_table.insert(pair <string, int> (Name, this->att_offset));
    this->attribute_type_table.insert(pair <string, string> (Name, Type));
    It=type_map.find(Type);
    att_offset += type_width[ It->second ];
    return true;
}
bool TypeNode::Add_method(string Name, int pra_num, int* a, int Return_type)
{
    map< string, int> :: iterator It;
    It = this->method_table.find(Name);
    TypeNode *tmp=this;
    while( tmp!=NULL && tmp->method_table.find(Name) == tmp->method_table.end())//首先检查其是否满足重载的条件
    {
        tmp = tmp->fa;
    }
    if(tmp != NULL)
    {
        It = tmp->method_table.find(Name);
        int no = It->second;
        if( method_pool[no].pra_num != pra_num) return false;
        for(int i=0; i<pra_num ;i++)
            if( a[i] !=  method_pool[no].pra_type[i] - pool) return false;
        if( Return_type != method_pool[no].Return_type - pool) return false;
    }
    MethodNode* cur= &method_pool[ method_cnt];
    cur->Belong = this;
    cur->pra_num = pra_num;
    cur->Name = Name;
    for(int i=0; i<pra_num; i++)
    {
        cur->pra_type[i] = pool+a[i];
        cur->pra_NAME[i] = pra_name_tmp[i];
    }
    if(Return_type>=0)
    cur->Return_type = pool + Return_type;
    else cur->Return_type = NULL;
    this->method_table[Name] = method_cnt;
    ++method_cnt;
}

int TypeNode::Find_method(string Name)
{
    TypeNode *tmp = this;
    while(tmp != NULL)
    {
        if(tmp->method_table.find(Name) != tmp->method_table.end()) return tmp->method_table.find(Name)->second;
        tmp = tmp->fa;
    }
    return -1;
}

int Div_scope::Find_const_value(int value)
{
    map<int ,int >::iterator It;
    It = this->Const_value.find(value);
    if(It == this->Const_value.end())
    {
        this->Add_const_value(value);
        return this->tmp_length-4;
    }
    else return It->second+begin_offset;
}

void Div_scope::Add_const_value(int x)
{
    this->Const_value.insert( pair< int ,int > (x, this->tmp_length));
    this->tmp_length += 4;
}
int Div_scope::Find_var(string Name)
{
    map< string, Var_linker*>::iterator It;
    Div_scope* cur_scope = this;
    //cout<<Name<<endl;
    while(cur_scope!=NULL && cur_scope->tmp_var_table.find(Name) == cur_scope->tmp_var_table.end()) cur_scope = cur_scope->pre_Div;//当前域查找不到则去更外围的域去查询
    if( cur_scope != NULL && (It=cur_scope->tmp_var_table.find(Name)) != cur_scope->tmp_var_table.end()) return cur_scope->begin_offset + It->second->offset;
    TypeNode *tmp = this->fa;
    if( tmp->attribute_table.find(Name) != tmp->attribute_table.end())
        return this->fa->att_offset + tmp->attribute_table.find(Name)->second;
    return -1;
}
string Div_scope::Find_var_type(string Name)
{
    map< string, Var_linker*>::iterator It;
    Div_scope* cur_scope = this;
    while(cur_scope!=NULL && cur_scope->tmp_var_table.find(Name) == cur_scope->tmp_var_table.end()) cur_scope = cur_scope->pre_Div;//当前域查找不到则去更外围的域去查询
    if( cur_scope != NULL &&(It=cur_scope->tmp_var_table.find(Name)) != cur_scope->tmp_var_table.end()) return It->second->T->Tname;
    TypeNode *tmp = this->fa;
    if( tmp->attribute_table.find(Name) != tmp->attribute_table.end())
        return tmp->attribute_type_table.find(Name)->second;
    return "";
}
void Div_scope::Add_var(string Name, string Type)
{
    map< string, int>::iterator It;
    It=type_map.find(Type);
    if(It == type_map.end()) exit(-6);//不存在当前类
    Var_linker* v = new Var_linker( &pool[ It->second ], this->tmp_length);
    this->tmp_length+= type_width[ It->second];
    this->tmp_var_table[Name] = v;
}
int pra_tmp[10];

void Init_AST()
{
    Add_type("Object");
    pool[0].fa=NULL;
    type_width [0] = 0;
    pool[0].Add_method("abort", 0, pra_tmp, 1);
    pool[0].Add_method("type_name", 0, pra_tmp, 2);
    pool[0].Add_method("copy", 0, pra_tmp, -1);

    Add_type("Int");
    type_width[1] = 4;
    pool[0].Build_son(pool+1);

    Add_type("String");
    type_width[2] = 256;
    pool[0].Build_son(pool+2);
    pool[2].Add_method("length", 0, pra_tmp, 1);
    pra_name_tmp[0] = "s";
    pra_tmp[0] = 2;
    pool[2].Add_method("concat", 1, pra_tmp, 2);
    pra_tmp[0]= 1;
    pra_name_tmp[0] = "i";
    pra_tmp[1] = 1;
    pra_name_tmp[1] = "l";
    pool[2].Add_method("substr", 2, pra_tmp, 2);

    Add_type("Bool");
    type_width[3] = 1;
    pool[0].Build_son(pool+3);

    Add_type("IO");
    pool[0].Build_son(pool+4);
    pra_tmp[0]=2;
    pra_name_tmp[0] = "x";
    pool[4].Add_method("out_string", 1, pra_tmp, -1);
    pra_tmp[0]=1;
    pra_name_tmp[0] = "x";
    pool[4].Add_method("out_int", 1, pra_tmp, -1);
    pool[4].Add_method("in_string", 0, pra_tmp, 2);
    pool[4].Add_method("in_int", 0, pra_tmp, 1);
}

bool check_fa_type(string x, string y)//x 是否为 y的子类
{
    TypeNode *tmpx, *tmpy;
    map<string, int> ::iterator It;
    It = type_map.find(x);
    tmpx = pool + It->second;
    It = type_map.find(y);
    if(It == type_map.end()) return false;
    tmpy = pool + It->second;
    while(tmpx != NULL)
    {
        if(tmpx == tmpy) return true;//沿着继承树向上去寻找是否存在这个类
        tmpx = tmpx->fa;
    }
    return false;
}
string LCA_type(string x_type, string y_type)//求出x与y的最近公共祖先
{
    TypeNode *tmpx, *tmpy;
    bool visit[pre_init_num];
    memset(visit, false, sizeof(visit));
    map<string, int> ::iterator It;
    It = type_map.find(x_type);
    tmpx = pool + It->second;
    while(tmpx != NULL)
    {
        visit[tmpx - pool] = true;
        tmpx = tmpx->fa;
    }
    It = type_map.find(y_type);
    tmpy = pool + It->second;
    while(tmpy != NULL)
    {
        if(visit[tmpy - pool])
        {
            return tmpy->Tname;
        }
        tmpy = tmpy ->fa;
    }
    return "";
}
#endif // AST_H_INCLUDED

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
static int type_cnt(0);//���ڸ��¼�������ͱ�ţ�ͬʱ��¼���ͱ��е���Ŀ
static int method_cnt(0);//���ڸ��¼���ķ�����ţ�ͬʱ��¼ȫ�ֵ��з�����������
static int type_width[pre_init_num];//��¼���͵��ֳ�
static map<string , int> type_map;
map<string , int> Const_string_value;//�����������ڶ���������λ��
map<string ,int > Const_value;//�����������ڶ�������λ��
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
    string Action;//��Ԫʽ��Ҫ���еĶ���
    string First;//��Ԫʽ���еĵ�һ��������,Ϊ��ʱ��Ϊ "_"
    string Second;//��Ԫʽ���еĵڶ����������� Ϊ��ʱ��Ϊ "_"
    string Result;//��Ԫʽ���д洢�����λ��
    Quad(int x,string _action = "", string _first = "", string _second = "", string _result = ""): no(x), Action(_action), First(_first), Second(_second), Result(_result){}
    void Out()
    {
        cout<<no<<":(  "<<Action<<"  , "<<First<<"  , "<<Second<<"  , "<<Result<<" )"<<endl;
    }
};

struct TypeNode//��¼����
{
    int son_cnt;
    //TypeNode *son[30];
    TypeNode *fa;
    vector<Quad> Init_Q;
    map<string , int> attribute_table;//�ڶ����Լ�¼������ƫ�Ƶ�ַ
    map<string , string> attribute_type_table;//��¼����������
    map<string , int> method_table;//�ڶ����Լ�¼��������ȫ�ֺ������еı�ţ�����¼λ�ã��Է�����ڴ���
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
    void Copy_initial(TypeNode *tmp);//���Ƴ�ʼ��ʱ����Ԫʽ
    void Build_son(TypeNode *tmp);//����AST�е��ӽ��
    void Copy_attribute_table(TypeNode *tmp);//��tmp����У�������������
    bool Add_attribute(string Name, string Type);//���������ͬʱ������õ����������Ƿ��Ѿ�������Ӧ��ͬ����������
    bool Add_method(string Name, int pra_num, int* a, int Return_type);//��ӷ����� ���Դ���ͬ���������Ƿ��������ع���,������-5\
    a�洢����ÿ���������͵ı��
    int Find_method(string Name);//û�ҵ��򷵻�-1
}pool[pre_init_num];

struct VarNode // ��¼����
{
    TypeNode* Type;
    int begin_offset;
    VarNode(): Type(0), begin_offset(0) {}
};

struct MethodNode
{
    TypeNode* Belong;//�����������ĸ���
    int pra_num;//��������Ŀ
    string Name;
    string pra_NAME[20];
    TypeNode* pra_type[20];//������������
    TypeNode* Return_type;//����ֵ������

}method_pool[pre_init_num];

struct Var_linker
{
    TypeNode *T;
    int offset;
    Var_linker(TypeNode* x=NULL, int y=0): T(x),offset(y) {}
};

struct Div_scope
{
    Div_scope* pre_Div;//ָ����һ��Div��ָ����Ϊ�գ� ˵������һ����Ϊ���
    int begin_offset;
    int tmp_length;//��ǰ��ռ�õ��ڴ�ռ䣬��¼���Է����˳���ʱ���������ͷ�
    map< string, Var_linker*> tmp_var_table;//�洢�ڵ�ǰ��֮�������ı������Լ�����ԵĴ洢�ռ��λ�ƴ�С
    map<int ,int > Const_value;//�����������ڶ����������ڷ��ű��е�λ��
    map<string , int > Const_string_value;//�����������ڶ����������ڷ��ű��е�λ��
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
    int Find_var(string Name);//����һ�������Ƿ��Ѿ����ڣ���ǰ��������ȥ����Χ��ȥ��ѯ��������������򷵻�-1 ���򷵻���ƫ�Ƶ�ַ
    string Find_var_type(string Name);//����������
    void Add_var(string Name, string Type);//�ڵ�ǰ��֮�������ΪNAME������ΪTYPE�ı���
    int Find_const_value(int value);//��ѯһ�������Ƿ��Ѿ����ڣ�����Ѿ������򷵻����ڳ������е�ƫ�������������
    void Add_const_value(int x);//�ڳ������������Ӧ����
};


TypeNode* Find_type(string Name);//��ѯһ�������Ƿ����ȶ���������δ��������򱨴�-2��������򷵻���������ӳ����е�λ��
int Add_type(string Name);//�����ͱ��в�����Ӧ���ֵ����ͣ�������ض�����򱨴�-3��������ӳ����������Ӧ��Ŀ
void Enter_new_scope();//����һ���µĶ�����
void Define_var(string Name);
bool check_fa_type(string x, string y);//�������Ϊx�����Ƿ��������Ϊy�ĸ���

TypeNode* Find_type(string Name)
{
    map<string, int> ::iterator tmp;
    tmp = type_map.find(Name);
    if(tmp == type_map.end())
    {
        //�Ƿ����壬����������δ�������
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
        //�ѱ��ض����
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
        //˵����ǰ�������Ѵ��ڣ��Ƿ�
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
    while( tmp!=NULL && tmp->method_table.find(Name) == tmp->method_table.end())//���ȼ�����Ƿ��������ص�����
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
    while(cur_scope!=NULL && cur_scope->tmp_var_table.find(Name) == cur_scope->tmp_var_table.end()) cur_scope = cur_scope->pre_Div;//��ǰ����Ҳ�����ȥ����Χ����ȥ��ѯ
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
    while(cur_scope!=NULL && cur_scope->tmp_var_table.find(Name) == cur_scope->tmp_var_table.end()) cur_scope = cur_scope->pre_Div;//��ǰ����Ҳ�����ȥ����Χ����ȥ��ѯ
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
    if(It == type_map.end()) exit(-6);//�����ڵ�ǰ��
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

bool check_fa_type(string x, string y)//x �Ƿ�Ϊ y������
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
        if(tmpx == tmpy) return true;//���ż̳�������ȥѰ���Ƿ���������
        tmpx = tmpx->fa;
    }
    return false;
}
string LCA_type(string x_type, string y_type)//���x��y�������������
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

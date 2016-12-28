#include <iostream>
#include <cstdio>
#include <queue>
#include "syntax.h"
using namespace std;
void Out_table()
{
    freopen("Symbol_table.txt", "w",stdout);
    printf("Class_name\tFather_class\tWidth\n");
    for(int i=0; i<type_cnt ;i++)
    {
        cout<<pool[i].Tname<<"\t\t";
        if(pool[i].fa != NULL)
            cout<<pool[i].fa->Tname<<"\t\t";
        else cout<<"_____\t\t";
        cout<<type_width[i]<<endl;
        map<string,int>::iterator Ii=pool[i].attribute_table.begin();
        map<string, string>::iterator Is=pool[i].attribute_type_table.begin();
        if(Ii != pool[i].attribute_table.end())
        {
            cout<<"\tVar_table\n\tName\tType\tBegin_offset\n";
            while(Ii!=pool[i].attribute_table.end())
            {
                cout<<"\t"<<Ii->first<<"\t"<<Is->second<<"\t"<<Ii->second<<endl;
                Ii++;
                Is++;
            }
        }
    }
    printf("---------------------------\nConst_value_table:\nValue\tWidth\n");
    map<string,int>::iterator It=Const_value.begin();
    while(It != Const_value.end())
    {
        cout<<It->first<<"\t"<<It->second<<endl;
        It++;
    }
    printf("---------------------------\nConst_string_table:\nstring\tWidth\n");
    It=Const_string_value.begin();
    while(It != Const_string_value.end())
    {
        cout<<It->first<<"\t"<<It->second<<endl;
        It++;
    }
    printf("---------------------------\nMethod_table:\nName\t\tType\n");
    for(int i=0;i<method_cnt; i++)
    {
        cout<<method_pool[i].Belong->Tname<<"."<<method_pool[i].Name<<"\t";
        if(method_pool[i].Return_type!=NULL)
            cout<<method_pool[i].Return_type->Tname<<endl;
        else cout<<"SELF_TYPE"<<endl;
        if(method_pool[i].pra_num)
        {
            cout<<"\t";
        cout<<"parameter_table\n\tName\tType\n";
        for(int j=0; j<method_pool[i].pra_num; j++)
            cout<<"\t"<<method_pool[i].pra_NAME[j]<<"\t"<<method_pool[i].pra_type[j]->Tname<<endl;
        }
    }

    fclose(stdout);
}
int main()
{
    freopen("lexer_result.txt", "r" ,stdin);
    Token_Q.push( Getdata() );
    Token_Q.push( Getdata() );
    Init_AST();
    cur = Token_Q.front();
    Token_Q.pop();
    Token_Q.push( Getdata() );
    Error_info x;
    //freopen("Quad.txt","w",stdout);
    x=F_P();
    //fclose(stdout);
    if(x.line_num>0) cout<<x.line_num<<" "<<x.Error_detail;

    Out_table();fclose(stdout);
    fclose(stdin);
    return 0;
}

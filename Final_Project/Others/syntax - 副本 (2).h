#ifndef SYNTAX_H_INCLUDED
#define SYNTAX_H_INCLUDED
#include <string>
#include <cstdio>
#include <stack>
#include "AST.h"
#include <vector>
#include "KelukinSupport.h"
#define default_synatax_error Error_info(cur.line_num, "syntax error!")
#define check_error if(tmp_Error.line_num>0) return tmp_Error
#define _GET_NEXT_DATA cur = Token_Q.front(); Token_Q.pop(); Token_Q.push( Getdata() );
using namespace std;
int tmp_var_num=0;
int tmp_flag=1;
struct Token
{
    int line_num;
    int token_id;
    string info;
    Token(int x=0, int y=0, string z=""): line_num(x), token_id(y), info(z) {};
};
queue< Token > Token_Q;
stack< string > Var_Q;
vector<Quad> V_Q;
int num_Quad=0;//用于V_Q中导航

void GeQ(string action, string x,string y, string z, int num, int flag = 1)
{
    if(flag)
    {
        V_Q.push_back(Quad(++Quad_no, action, x, y, z));
        num_Quad ++ ;
    }
}

char t_c[2123];
Token cur;
Token Getdata()//从词法分析器产生的中间文件当中去读取数据
{
    int token_id=-1;
    int line_num=-1;
    //if(cin.eof())
    string tmp_info = "";
    scanf("#%d%d", &line_num, &token_id);
    if(token_id <= 4)
    {
        getchar();
        getline(cin,tmp_info);
        //getchar();
    }
    else getchar();
    return Token(line_num, token_id, tmp_info);
}
struct Error_info
{
    int line_num;
    string Error_detail;
    Error_info(int x=-1, string y=""): line_num(x), Error_detail(y){};
};
Error_info F_P();
Error_info F_C();
Error_info F_C_tmp();
Error_info F_IN();
Error_info F_F();
Error_info F_F_tmp();
Error_info F_FP();
Error_info F_Z();
Error_info F_FM();
Error_info F_FM_tmp();
Error_info F_E();
Error_info F_G();
Error_info F_H();
Error_info F_H_tmp();
Error_info F_I();
Error_info F_I_tmp();
Error_info F_J();
Error_info F_J_tmp();
Error_info F_K();
Error_info F_L();
Error_info F_N();
Error_info F_M();
Error_info F_M_tmp();
Error_info F_CA();
Error_info F_CA_tmp();
Error_info F_LE();
Error_info F_EP();
Error_info F_EP_tmp();

string cur_type_name;
string cur_id_name;
string cur_id_type;
int pra_cnt;
int check_pra_num;
Div_scope *cur_scope;
string let_sum_type= "";
stack<string> ST_for_let;
stack<int> CK_pr;
Error_info tmp_Error;
Error_info F_P()
{
    if(cur.token_id == 10086) return Error_info();
    else return F_C();
}
Error_info F_C()
{
    if( cur.token_id!= 9) return default_synatax_error;
    _GET_NEXT_DATA;
    if(cur.token_id != 4) return default_synatax_error;
    Add_type( cur.info );
    cur_type_name = cur.info;
    _GET_NEXT_DATA;
    tmp_Error= F_IN();
    check_error;
    if( cur.token_id != 67) return default_synatax_error;
    _GET_NEXT_DATA;
    tmp_Error= F_F();
    check_error;

    if( cur.token_id != 68) return default_synatax_error;
    _GET_NEXT_DATA;
    if( cur.token_id != 52) return default_synatax_error;
    _GET_NEXT_DATA;
    type_width[ type_cnt-1 ] = pool[ type_cnt-1 ].att_offset;//计算其所占的内存空间大小
    tmp_Error = F_C_tmp(); check_error;
    return Error_info();
}
Error_info F_C_tmp()
{
    if( cur.token_id != 10086) return F_C();
    return Error_info();
}
Error_info F_IN()
{
    if( cur.token_id == 15)
    {
        _GET_NEXT_DATA;
        if(cur.token_id != 4) return Error_info( cur.line_num, "You should give a type name here!");
        if(cur.info == "Int" || cur.info == "String" || cur.info == "Bool")
            return Error_info(cur.line_num, "This type could not be inherited");
            //cout<<cur.info<<endl;
        Find_type(cur.info)->Build_son( Find_type(cur_type_name) );
        _GET_NEXT_DATA;
    }
    else
    {
        Find_type("Object")->Build_son( Find_type(cur_type_name) );
    }
    return Error_info();
}
Error_info F_F()
{
    if(cur.token_id != 0) return default_synatax_error;
    cur_id_name = cur.info;
    _GET_NEXT_DATA;
    tmp_Error=F_F_tmp();check_error;
    return Error_info();
}


Error_info F_F_tmp()
{
    if(cur.token_id != 65 && cur.token_id != 51) return default_synatax_error;
    if(cur.token_id == 65)
    {
        string tmp_method_name = cur_type_name + "." +cur_id_name;
        Quad(++Quad_no,"function",tmp_method_name,"__","__").Out();
        V_Q.clear();
        _GET_NEXT_DATA;
        cur_scope = new( Div_scope);//建立新的定义域， 首先将参数压入栈中
        cur_scope->begin_offset = pool[ type_cnt-1].att_offset;
        cur_scope ->fa = pool+(type_cnt-1);

        pra_cnt=0; //统计传入的参数的数目
        tmp_Error = F_FM();
        check_error;
        if(cur.token_id!= 66) return default_synatax_error;
        _GET_NEXT_DATA;
        if(cur.token_id != 51) return default_synatax_error;
        _GET_NEXT_DATA;
        if(cur.token_id != 4) return Error_info( cur.line_num, "You should give a type name here!");
        string tmp = cur.info;
        if(cur.info != "SELF_TYPE")
            Find_type(cur_type_name) ->Add_method(cur_id_name, pra_cnt, pra_tmp, Find_type(cur.info) - pool);
        else Find_type(cur_type_name) ->Add_method(cur_id_name, pra_cnt, pra_tmp, -1);
        _GET_NEXT_DATA;
        if( cur.token_id != 67 ) return default_synatax_error;
        _GET_NEXT_DATA;
        tmp_Error = F_E();check_error;
        if(tmp!="SELF_TYPE"&& tmp!= cur_id_type) return Error_info( cur.line_num, "Wrong return type;");
        if(tmp == "SELF_TYPE" && cur_id_type!=cur_type_name)return Error_info( cur.line_num, "Wrong return type;");

        //string x = Var_Q.top();Var_Q.pop();
        GeQ("return","__","__", "___", ++Quad_no, tmp_flag);

        if( cur.token_id != 68 ) return default_synatax_error;
        _GET_NEXT_DATA;
        if( cur.token_id != 52 ) return default_synatax_error;
        _GET_NEXT_DATA;

        Quad(++Quad_no,"End_function",tmp_method_name,"__","__").Out();
        while(!Var_Q.empty()) Var_Q.pop();
    }
    else
    {
        _GET_NEXT_DATA;
        if(cur.token_id != 4) return default_synatax_error;
        TypeNode *tmp = Find_type( cur.info );
        if(tmp == NULL ) return Error_info(cur.line_num, "This Type has not been defined!");
        if( !Find_type(cur_type_name) ->Add_attribute( cur_id_name, cur.info))
            return Error_info( cur.line_num, "This attribute has been defined!");
        _GET_NEXT_DATA;
        tmp_Error = F_Z();
        check_error;
        if( cur.token_id != 52 ) return default_synatax_error;
        _GET_NEXT_DATA;
    }
    tmp_Error = F_FP();
    check_error;
    return Error_info();
}

Error_info F_Z()
{
    if(cur.token_id == 53)
    {
        _GET_NEXT_DATA;
        string tmp_type_name = cur_id_type;
        tmp_Error = F_E();
        check_error;
        if(!check_fa_type(cur_id_type, tmp_type_name))
        {
            cout<<cur_id_type<<" "<<tmp_type_name<<endl;
            return Error_info(cur.line_num, "Illegal assignment!");
        }
    }
    return Error_info();
}

Error_info F_FP()
{
    if( cur.token_id == 0)
    {
        tmp_Error = F_F();
        check_error;
    }
    return Error_info();
}

Error_info F_FM()
{
    if(cur.token_id == 66) return Error_info();
    if( cur.token_id != 0) return default_synatax_error;

        string Name, Type;
        Name = cur.info;
        _GET_NEXT_DATA;
        if(cur.token_id != 51) return default_synatax_error;
        _GET_NEXT_DATA;
        if(cur.token_id != 4) return default_synatax_error;
        TypeNode* tmp = Find_type( cur.info );
        if( tmp == NULL) return Error_info(cur.line_num, "This Type has not been defined!");
        pra_tmp[ pra_cnt] = Find_type( cur.info ) - pool;
        pra_name_tmp[pra_cnt++] = Name;
        Type = cur.info;
        cur_scope ->Add_var( Name, Type);
        _GET_NEXT_DATA;
    tmp_Error = F_FM_tmp(); check_error;
    return Error_info();
}

Error_info F_FM_tmp()
{
    if(cur.token_id == 66) return Error_info();
    if( cur.token_id != 72) return default_synatax_error;
    _GET_NEXT_DATA;
    tmp_Error = F_FM();
    check_error;
    tmp_Error = F_FM_tmp();
    check_error;
    return Error_info();
}

Error_info F_E()
{
    if( cur.token_id == 0 && Token_Q.front().token_id == 53)//赋值语句
    {
        //check_pra_num--;
        if(cur_scope -> Find_var(cur.info) == -1) return Error_info(cur.line_num, "This variable is not defined.");
        cur_id_type = cur_scope ->Find_var_type(cur.info);
        if(cur_id_type == "") return Error_info(cur.line_num, "This var has not been defined here!");
        string tmp_type = cur_id_type;
        _GET_NEXT_DATA;
        _GET_NEXT_DATA;
        tmp_Error = F_E();check_error;
        if(!check_fa_type(cur_id_type, tmp_type))
        {
            cout<< cur_id_type<<" "<<tmp_type<<endl;
            return Error_info(cur.line_num, "This assignment is illegal!");
        }
        string x=Var_Q.top();Var_Q.pop();
        string y=Var_Q.top();Var_Q.pop();
        GeQ("<-", x, "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);
        return Error_info();
    }
    if( cur.token_id == 66)
    {
        return Error_info();
    }
    tmp_Error = F_G(); check_error;
    return Error_info();
}

Error_info F_G()
{
    if( cur.token_id == 26)// not G
    {
        _GET_NEXT_DATA;
        tmp_Error = F_G(); check_error;
        if(cur_id_type != "Bool") return Error_info(cur.line_num, "Here should be a Boolean!");
        string x=Var_Q.top();Var_Q.pop();
        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("not", x, "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);
        return Error_info();
    }
    tmp_Error = F_H(); check_error;
    return Error_info();
}

Error_info F_H()
{
    tmp_Error = F_I(); check_error;
    tmp_Error = F_H_tmp(); check_error;
    return Error_info();
}

Error_info F_H_tmp()
{
    if( cur.token_id >=61 && cur.token_id <64) //比较式子
    {
        _GET_NEXT_DATA;
        if(cur_id_type != "Int") return Error_info(cur.line_num, "Here should be an integer to be compared!");
        tmp_Error = F_I(); check_error;
        if(cur_id_type != "Int") return Error_info(cur.line_num, "Here should be an integer to be compared!");
        cur_id_type = "Bool";

        string x=Var_Q.top();Var_Q.pop();
        string y=Var_Q.top();Var_Q.pop();
        string z = "tmp"+int_to_string(++tmp_var_num);
        string a;
        if(cur.token_id == 62)  a="<";
        else    a = "<=";
        GeQ(a,y,x,z, ++Quad_no ,tmp_flag);
        Var_Q.push(z);

        tmp_Error = F_H_tmp(); check_error;
    }
    else
        if(cur.token_id == 64)
    {
        _GET_NEXT_DATA;
        if(cur_id_type != "Int" &&cur_id_type != "String" && cur_id_type != "Bool")
            return Error_info(cur.line_num, "Here should be a basic class!");
        string tmp = cur_id_type;
        tmp_Error = F_I(); check_error;
        if(cur_id_type != tmp)
        {
            return Error_info( cur.line_num, "The class of two operator var should be the same");
        }
        cur_id_type = "Bool";

        string x=Var_Q.top();Var_Q.pop();
        string y=Var_Q.top();Var_Q.pop();
        string z = "tmp"+int_to_string(++tmp_var_num);
        string a = "=";
        GeQ(a, y, x, z, ++Quad_no ,tmp_flag);
        Var_Q.push(z);

        tmp_Error = F_H_tmp(); check_error;
    }
    return Error_info();
}

Error_info F_I()
{
    tmp_Error = F_J(); check_error;
    tmp_Error = F_I_tmp(); check_error;
    return Error_info();
}

Error_info F_I_tmp()
{
    if( cur.token_id == 56 || cur.token_id == 57)// +J | - J
    {
        if(cur_id_type != "Int") return Error_info(cur.line_num, "Here should be an integer to be calculated!");
        _GET_NEXT_DATA;
        tmp_Error = F_J(); check_error;
        if(cur_id_type != "Int") return Error_info(cur.line_num, "Here should be an integer to be calculated!");
        cur_id_type = "Int";

        string x=Var_Q.top();Var_Q.pop();
        string y=Var_Q.top();Var_Q.pop();
        string z = "tmp"+int_to_string(++tmp_var_num);
        string a;
        if(cur.token_id == 56)  a="+";
        else    a = "-";
        GeQ(a,y,x,z, ++Quad_no ,tmp_flag);
        Var_Q.push(z);

        tmp_Error = F_I_tmp(); check_error;
    }
    return Error_info();
}

Error_info F_J()
{
    tmp_Error = F_K(); check_error;
    tmp_Error = F_J_tmp(); check_error;
    return Error_info();
}

Error_info F_J_tmp()
{
    if( cur.token_id == 58 || cur.token_id == 59)// *K | / K
    {
        if(cur_id_type != "Int") return Error_info(cur.line_num, "Here should be an integer to be calculated!");
        _GET_NEXT_DATA;
        tmp_Error = F_K(); check_error;
        if(cur_id_type != "Int") return Error_info(cur.line_num, "Here should be an integer to be calculated!");
        cur_id_type = "Int";

        string x=Var_Q.top();Var_Q.pop();
        string y=Var_Q.top();Var_Q.pop();
        string z = "tmp"+int_to_string(++tmp_var_num);
        string a;
        if(cur.token_id == 56)  a="*";
        else    a = "/";
        GeQ(a,y,x,z, ++Quad_no ,tmp_flag);
        Var_Q.push(z);

        tmp_Error = F_J_tmp(); check_error;
    }
    return Error_info();
}

Error_info F_K()
{
    if( cur.token_id == 16)
    {
        _GET_NEXT_DATA;
        tmp_Error = F_K(); check_error;

        string x=Var_Q.top();Var_Q.pop();
        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("isvoid", x, "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);

        cur_id_type = "Bool";
    }
    else
    {
        tmp_Error = F_L(); check_error;
    }
    return Error_info();
}

Error_info F_L()
{
    if( cur.token_id == 60)//~L
    {
        _GET_NEXT_DATA;
        tmp_Error = F_L(); check_error;
        if(cur_id_type != "Int") return Error_info(cur.line_num, "Here should be an integer to be calculated!");

        string x=Var_Q.top();Var_Q.pop();
        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("~", x, "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);

        cur_id_type = "Int";
    }
    else
    {
        tmp_Error = F_M(); check_error;
    }
    return Error_info();
}

Error_info F_M()
{
    tmp_Error = F_N(); check_error;
    tmp_Error = F_M_tmp(); check_error;
    return Error_info();
}

Error_info F_M_tmp()
{
   // string tmp_type_name= cur_type_name;
   string tmp_method_name = Var_Q.top();
    if( cur.token_id == 55)
    {
        _GET_NEXT_DATA;
        if(cur.token_id != 4) default_synatax_error;
        if( !check_fa_type(cur_id_type, cur.info) ) return Error_info(cur.line_num, "This given type is illegal!");
        cur_id_name = cur.info;
        tmp_method_name = tmp_method_name + "@" +cur.info;
        _GET_NEXT_DATA;
        if(cur.token_id != 54) default_synatax_error;
    }
    if( cur.token_id == 54)
    {
        _GET_NEXT_DATA;
        if(cur.token_id != 0) default_synatax_error;
        MethodNode *tm;
        TypeNode * ty;
        ty = pool + type_map.find(cur_id_type)->second;
        if(ty->method_table.find(cur.info) == ty->method_table.end()) return Error_info(cur.line_num, "this method is nod defined in given type!");
        tm = method_pool + ty->method_table.find(cur.info)->second;

        tmp_method_name = tmp_method_name + "." + cur.info;

        CK_pr.push(check_pra_num);
        check_pra_num = tm->pra_num;
        string tmp_method_type;
        if(tm->Return_type != NULL)
        tmp_method_type = tm->Return_type->Tname;
        else tmp_method_type = cur_id_type;
        _GET_NEXT_DATA;
        if(cur.token_id != 65) default_synatax_error;
        _GET_NEXT_DATA;
        if(cur.token_id != 66) check_pra_num--;//用来检查参数的数目是否正确
        //参数检查待做
        tmp_Error = F_E(); check_error;
        string x= Var_Q.top();Var_Q.pop();
        GeQ("addpar", "__", "__", x, ++Quad_no, tmp_flag);

        tmp_Error = F_EP(); check_error;
        if(cur.token_id != 66) default_synatax_error;
        if(check_pra_num != 0) return Error_info( cur.line_num, "The amount of parameter is wrong!");
        check_pra_num = CK_pr.top(); CK_pr.pop();
        _GET_NEXT_DATA;
        cur_id_type = tmp_method_type;

        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("call", tmp_method_name, "__", y, ++Quad_no, tmp_flag);
        Var_Q.pop();
        Var_Q.push(y);

        tmp_Error = F_M_tmp(); check_error;
    }
    return Error_info();
}

Error_info F_N()
{
    if(cur.token_id == 65)
    {
        _GET_NEXT_DATA;
        tmp_Error = F_E();check_error;
        if(cur.token_id != 66) default_synatax_error;
        _GET_NEXT_DATA;
        return Error_info();
    }
    if( cur.token_id == 0)
    {
        if(Token_Q.front().token_id == 65)
        {
            string tmp_method_name = cur.info;
            TypeNode *T = pool +type_map.find(cur_type_name)->second;
            int no = T->Find_method( tmp_method_name);
            if(no<0) return Error_info(cur.line_num, "This method is not defined in that type!");
            MethodNode *tm = method_pool +no;
            CK_pr.push(check_pra_num);
            check_pra_num = method_pool[ no ].pra_num;
            _GET_NEXT_DATA;
            _GET_NEXT_DATA;
            if(cur.token_id != 66) check_pra_num--;
            tmp_Error = F_E(); check_error;

            string x= Var_Q.top();Var_Q.pop();
            GeQ("addpar", "__", "__", x, ++Quad_no, tmp_flag);

            tmp_Error = F_EP(); check_error;
            if(cur.token_id != 66) default_synatax_error;
            _GET_NEXT_DATA;
            if(tm->Return_type != NULL)
            cur_id_type = tm->Return_type->Tname;
            else cur_id_name = cur_type_name;

            string y = "tmp"+int_to_string(++tmp_var_num);
            GeQ("call", tmp_method_name, "__", y, ++Quad_no, tmp_flag);
            Var_Q.push(y);

            return Error_info();
        }
        else
        {
            //匹配ID
            if(cur_scope -> Find_var(cur.info) == -1) return Error_info(cur.line_num, "This variable is not defined.");
            cur_id_type = cur_scope ->Find_var_type(cur.info);
            Var_Q.push(cur.info);
            //cout<<cur.info<<":"<<cur_id_type<<endl;
            _GET_NEXT_DATA;
            return Error_info();
        }
    }
    if( cur.token_id == 2)//string
    {
        cur_id_type = "String";
        add_const_string(cur.info);
        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("<-", cur.info, "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);
        _GET_NEXT_DATA;
        return Error_info();
    }
    if( cur.token_id == 3)//integer
    {

        cur_id_type = "Int";
        add_const_value(cur.info);
        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("<-", cur.info, "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);
        _GET_NEXT_DATA;
        return Error_info();
    }
    if( cur.token_id == 11 || cur.token_id == 27)//true or false
    {
        cur_id_type = "Bool";
        if(cur.token_id == 11)
            cur.info = "false";
        else
            cur.info = "true";

        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("<-", cur.info, "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);

        _GET_NEXT_DATA;
        return Error_info();
    }
    if( cur.token_id == 24)// new
    {
        _GET_NEXT_DATA;
        if(cur.token_id != 4) default_synatax_error;
        TypeNode *tmp = Find_type(cur.info);
        if(tmp == NULL) return Error_info(cur.line_num, "This Type has not been defined!");
        cur_id_type = cur.info;

        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("new", cur.info, "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);

        _GET_NEXT_DATA;
        return Error_info();
    }
    if( cur.token_id == 13)//if
    {
        GeQ("if", "__", "__", "__", ++Quad_no, tmp_flag);
        _GET_NEXT_DATA;
        tmp_Error = F_E(); check_error;
        GeQ("j=", Var_Q.top(), "false", "__", ++Quad_no, tmp_flag);
        Var_Q.pop();
        int no=num_Quad;
        if(cur_id_type != "Bool")
        if(cur.token_id != 20) return default_synatax_error;
        _GET_NEXT_DATA;
        tmp_Error = F_E(); check_error;
        GeQ("j", "__", "__", "__", ++Quad_no, tmp_flag);
        V_Q[no].Result = int_to_string(Quad_no+1);
        no = Quad_no;
        string tmp_type1 = cur_type_name;
        if(cur.token_id != 10) return default_synatax_error;
        _GET_NEXT_DATA;
        tmp_Error = F_E(); check_error;
        V_Q[no].Result = int_to_string(Quad_no+1);
        string tmp_type2 = cur_type_name;
        if(cur.token_id != 12) return default_synatax_error;
        cur_type_name = LCA_type(tmp_type1, tmp_type2);

        GeQ("end_if", "__", "__", "__", ++Quad_no, tmp_flag);

        _GET_NEXT_DATA;

        return Error_info();
    }
    if( cur.token_id == 21)//while
    {
        _GET_NEXT_DATA;
        GeQ("while", "__", "__", "__", ++Quad_no, tmp_flag);
        int pp = Quad_no;
        GeQ("j=", Var_Q.top(), "false", "__", ++Quad_no, tmp_flag);
        Var_Q.pop();
        int no=num_Quad;

        tmp_Error = F_E(); check_error;
        GeQ("j", "__", "__", int_to_string(pp), ++Quad_no, tmp_flag);
        V_Q[no].Result = int_to_string(Quad_no+1);
        no = Quad_no;

        if(cur_id_type != "Bool") return Error_info(cur.line_num, "Here should be a Boolean!");
        if(cur.token_id != 18) return default_synatax_error;
        _GET_NEXT_DATA;
        tmp_Error = F_E(); check_error;
        if(cur.token_id != 19) return default_synatax_error;
        cur_id_type = "Object";
        _GET_NEXT_DATA;

        return Error_info();
    }
    if( cur.token_id == 67)//{E}
    {
        _GET_NEXT_DATA;
        tmp_Error = F_E(); check_error;
        if(cur.token_id != 52) return default_synatax_error;
        _GET_NEXT_DATA;
        tmp_Error = F_EP_tmp(); check_error;
        if(cur.token_id != 68) return default_synatax_error;
        _GET_NEXT_DATA;

        return Error_info();
    }

    if( cur.token_id == 17)//let
    {
        Div_scope* tmp_scope = new Div_scope;
        tmp_scope->pre_Div = cur_scope;
        tmp_scope->begin_offset = cur_scope->tmp_length;
        tmp_scope -> fa = cur_scope->fa;
        cur_scope = tmp_scope;
        string Name,T;
        _GET_NEXT_DATA;
        if(cur.token_id != 0) return default_synatax_error;
        Name = cur.info;
        _GET_NEXT_DATA;
        if(cur.token_id != 51) return default_synatax_error;
        _GET_NEXT_DATA;
        if(cur.token_id != 4) return default_synatax_error;
        T = cur.info;
        TypeNode *tmp = Find_type(cur.info);
        if(tmp == NULL) return Error_info(cur.line_num, "This Type has not been defined!");
        //cout<<Name<<":"<<T<<endl;
        cur_scope ->Add_var(Name, T);
        cur_id_type = T;
        _GET_NEXT_DATA;
        tmp_Error = F_Z(); check_error;
        tmp_Error = F_LE(); check_error;

        if(cur.token_id != 14) return default_synatax_error;
        _GET_NEXT_DATA;
        tmp_Error = F_E(); check_error;
        tmp_scope = cur_scope->pre_Div;
        delete(cur_scope);
        cur_scope = tmp_scope;
        return Error_info();
    }

    if( cur.token_id == 22)//case
    {
        _GET_NEXT_DATA;

        tmp_Error = F_E(); check_error;

        ST_for_let.push(let_sum_type);
        let_sum_type = "";
        if(cur.token_id != 25) return default_synatax_error;
        _GET_NEXT_DATA;

        tmp_Error = F_CA(); check_error;

        if(cur.token_id != 23) return default_synatax_error;
        _GET_NEXT_DATA;

        cur_id_type = let_sum_type;
        let_sum_type = ST_for_let.top(); ST_for_let.pop();
        return Error_info();
    }
    if( cur.token_id == 29)
    {
        cur_id_type = cur_type_name;

        string y = "tmp"+int_to_string(++tmp_var_num);
        GeQ("<-", "self", "__", y, ++Quad_no, tmp_flag);
        Var_Q.push(y);

        _GET_NEXT_DATA;
        return Error_info();
    }
    return default_synatax_error;
}

Error_info F_CA()
{
    if( cur.token_id == 0)
    {
        Div_scope* tmp_scope = new Div_scope;
        tmp_scope->pre_Div = cur_scope;
        tmp_scope->begin_offset = cur_scope->tmp_length;
        tmp_scope -> fa = cur_scope->fa;
        cur_scope = tmp_scope;//创建新的定义域
        string tmp_var_name = cur.info;

        _GET_NEXT_DATA;
        if(cur.token_id != 51) return default_synatax_error;
        _GET_NEXT_DATA;
        if(cur.token_id != 4) return default_synatax_error;
        TypeNode *tmp = Find_type(cur.info);
        if(tmp == NULL) return Error_info(cur.line_num, "This Type has not been defined!");
        cur_scope ->Add_var(tmp_var_name, cur.info);
        if(cur.token_id != 69) return default_synatax_error;
        _GET_NEXT_DATA;

        tmp_Error = F_E(); check_error;
        if(let_sum_type == "") let_sum_type = cur_id_type;
        else let_sum_type = LCA_type(let_sum_type, cur_id_type);
        if(cur.token_id != 52) return default_synatax_error;
        _GET_NEXT_DATA;
        delete(cur_scope);

        cur_scope = tmp_scope;//退出至原来的定义域
        tmp_Error = F_CA_tmp(); check_error;
        return Error_info();
    }
    return default_synatax_error;
}

Error_info F_CA_tmp()
{
    if( cur.token_id == 0)
    {
        tmp_Error = F_CA(); check_error;

    }
    return Error_info();
}

Error_info F_LE()
{
    if( cur.token_id == 72)
    {
        _GET_NEXT_DATA;

        if(cur.token_id != 0) return default_synatax_error;
        string tmp_var_name = cur.info;
        _GET_NEXT_DATA;
        if(cur.token_id != 51) return default_synatax_error;
        _GET_NEXT_DATA;
        if(cur.token_id != 4) return default_synatax_error;
        TypeNode *tmp = Find_type(cur.info);
        if(tmp == NULL) return Error_info(cur.line_num, "This Type has not been defined!");
        cur_scope ->Add_var(tmp_var_name , cur.info);

        _GET_NEXT_DATA;
        tmp_Error = F_Z(); check_error;
        tmp_Error = F_LE(); check_error;

    }
    return Error_info();
}

Error_info F_EP_tmp()
{
    if( cur.token_id != 68)
    {
        Var_Q.pop();
        tmp_Error = F_E();check_error;
        if(cur.token_id != 52) return default_synatax_error;
        _GET_NEXT_DATA;
        tmp_Error = F_EP_tmp(); check_error;
    }
    return Error_info();
}

Error_info F_EP()
{
    if( cur.token_id == 72)
    {
        _GET_NEXT_DATA;
        check_pra_num--;
        tmp_Error = F_E();check_error;

        string x= Var_Q.top();Var_Q.pop();
        GeQ("addpar", "__", "__", x, ++Quad_no, tmp_flag);

        tmp_Error = F_EP(); check_error;
    }
    return Error_info();
}
#endif // SYNTAX_H_INCLUDED

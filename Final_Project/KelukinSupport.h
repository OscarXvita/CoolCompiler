#ifndef KELUKINSUPPORT_H_INCLUDED
#define KELUKINSUPPORT_H_INCLUDED
string int_to_string(int x)//将数字转换为字符串
{
    int y=0;
    while(x)
    {
        y=y*10+x%10;
        x/=10;
    }
    string z="";
    while(y)
    {
        z+=char('0'+y%10);
        y/=10;
    }
    return z;
}


#endif // KELUKINSUPPORT_H_INCLUDED

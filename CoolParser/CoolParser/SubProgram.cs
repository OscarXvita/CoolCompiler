using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.IO;
using System.Reflection.Emit;
using System.Text;

namespace CoolParser
{
    class SubProgram
    {
        public enum strToToken
        {
            e_typeCname = 4,
            e_class = 9, e_else, e_false, e_fi, e_if, e_in, e_inherits, e_isvoid, e_let,
            e_loop, e_pool, e_then, e_while, e_case, e_easc, e_new, e_of, e_not, e_true, e_main
                , e_self, e_SELF_TYPE, e_colon = 51, e_semicolon, e_la, e_dot, e_at, e_plus, e_minus, e_time, e_div
               , e_tilde, e_lessthan, e_LE, e_EEqual, e_equal, e_lb, e_rb, e_llb, e_lrb,
            e_lbstar, e_rbstar, e_bb, e_comma


        }

        public static int value;

        #region DictionAry Definition
        private readonly Dictionary<string, int> _string2Token = new Dictionary<string, int>
        {
             {"ID", 0},
             {"Char", 1},
             {"String", 2},
             {"Integer", 3},
             {"Type", 4},
            {"class", 9},
            {"else", 10},
            {"false", 11},
            {"fi", 12},
            {"if", 13},
            {"in", 14},
            {"inherits", 15},
            {"isvoid", 16},
            {"let", 17},
            {"loop", 18},
            {"pool", 19},
            {"then", 20},
            {"while", 21},
            {"case", 22 },
            {"esac", 23 },
            {"new", 24 },
            {"of", 25 },
            {"not", 26 },
            {"true", 27 },
            {"Main", 28 },
            {"self", 29 },
            {"SELF_TYPE", 30 },
            {":", 51},
            {";", 52},
            {"<-",53},
            {".", 54},
            {"@", 55},
            {"+", 56},
            {"-", 57},
            {"*", 58},
            {"/", 59},
            {"~", 60},
            {"<", 61},
            {"<=",62},
            {"==",63},
            {"=", 64},
            {"(", 65},
            {")", 66},
            {"{", 67},
            {"}", 68},
            {"=>",69},
            {",", 72},
             {"ERR", -3},

        };
        #endregion
        //class Node
        //{
        //    public Node LeftChild { get; private set; }
        //    public Node RightChild { get; private set; }
        //    public char Label { get; private set; }

        //    public Node(char label, Node left, Node right)
        //    {
        //        Label = label;
        //        LeftChild = left;
        //        RightChild = right;
        //    }
        //}

        public void ProP()
        {

            ProC();

            Console.WriteLine("Completed!");
          
           

            
            var fs = new FileStream("out.txt", FileMode.Create);
            var sw = new StreamWriter(fs);
            foreach (var e in quadList)
            {
                Console.WriteLine(quadList.IndexOf(e)+":"+e.ToString());
                sw.WriteLine(quadList.IndexOf(e)+":"+e.ToString());
            }
           sw.Flush();
            sw.Close();
        
        }

        public int xLine;
        public int ReadPeek()
        {
            try
            {
                xLine = Program.TokenList.Peek().LineNum;
                value = Program.TokenList.Peek().tokens;
                
                return Program.TokenList.Peek().tokens;

            }
            catch (InvalidOperationException e)
            {
                return -3;
            }
        }
        public int ReadDeque()
        {
            Console.WriteLine("MATCHED TOKEN:"+ Program.TokenList.Peek().tokens+","+ Program.TokenList.Peek().GetValue());
            return Program.TokenList.Dequeue().tokens;
        }
        public string ReadValueDeque()
        {
            Console.WriteLine("MATCHED TOKEN:" + Program.TokenList.Peek().tokens + "," + Program.TokenList.Peek().GetValue());
            return Program.TokenList.Dequeue().GetValue();
        }

        public int getTValue(string name)
        {
            int temp;
            _string2Token.TryGetValue(name, out temp);
            return temp;
        }
        public bool checkTerminalN(string terminal)//Only Check, no pop
        {



            if (ReadPeek() == getTValue(terminal))
            {

                //switch (terminal)
                //{
                //    case "ID":
                //    case "Integer":
                //    case "string":
                //        {
                //            Program.SemanticStack.Push(Program.TokenList.Peek().GetValue());
                //            break;
                //        }

                //    case "true":
                //        {
                //            Program.SemanticStack.Push("true");
                //            break;

                //        }
                //    case "false":
                //        {
                //            Program.SemanticStack.Push("false");
                //            break;

                //        }

                //    default:
                //        break;
                //}
                return true;
            }
            else
            {

                return false;
            }
        }
        public bool checkTerminal(string terminal)
        {

            if (ReadPeek() == getTValue(terminal))
            {
                //   Debug.WriteLine("MATCHED: "+terminal);



                ReadDeque();

                return true;
            }
            else
            {

                return false;
            }
        }
        public bool checkTerminalE(string terminal)
        {
            if (ReadPeek() == getTValue(terminal))
            {
                // Debug.WriteLine("MATCHED: " + terminal);
               
                ReadDeque();
                return true;
            }
            else
            {
                if (ReadPeek() == -3)
                {
                    throw new ParserException(string.Format("Error at Line {0}, Token {2} : Supposed Terminal {1}",
                        xLine, terminal, value));
                }

                else
                {
                    throw new ParserException(string.Format("Error at Line {0}, Token {2} : Supposed Terminal {1}",
                   xLine, terminal, Program.TokenList.Peek().GetValue()));
                }


            }


        }

        public class ParserException : Exception
        {
            public ParserException(string message) : base(message)
            {
            }
        }
        public void ProC()
        {
            Console.WriteLine("C");
            checkTerminalE("class");

            ProT();
            ProIN();
            checkTerminalE("{");
            ProF();
            checkTerminalE("}");
            checkTerminalE(";");
            ProCS();

          

        }

        // current state
        // next state
        // final state
        //error 


        public void ProCS()
        {
            Console.WriteLine("CS");
            if (Program.TokenList.Count > 0)
            {
                if (ReadPeek() == getTValue("class"))
                {
                    ProC();
                }
                else
                {
                    Console.WriteLine("ERROR");
                    throw new ParserException(string.Format("Error at Line {0}", Program.TokenList.Peek().LineNum));
                }
            }
            else
            {
                Debug.WriteLine("$");

                return;
            }




        }
        public string ProT()//T	->	（类型名，以大写字母开头的字符串）

        {
            Console.WriteLine("T");
            if (ReadPeek() == getTValue("Type"))
                if (Program.TokenList.Peek().GetValue() != "")
                {
                    if (char.IsUpper(Program.TokenList.Peek().GetValue(), 0))
                    {
                        var name=Program.TokenList.Peek().GetValue();
                        //Debug.WriteLine(Program.TokenList.Peek().GetValue());
                        ReadDeque();
                        return name;
                    }
                    else
                    {
                        throw new ParserException(string.Format("Error at Line {0}: Not Uppercase in Type Name", Program.TokenList.Peek().LineNum));
                    }
                }

                else
                    throw new MissingFieldException(string.Format("Possible Error at Line {0}: Should be a T?", Program.TokenList.Peek().LineNum));
            else
            {
                throw new ParserException(string.Format("Error at Line {0}: Supposed Type Name", Program.TokenList.Peek().LineNum));
            }
          
        }



        public void ProIN()
        {
            Console.WriteLine("IN");
            if (checkTerminal("inherits"))
            {


                ProT();

            }
            else
            {
                Debug.WriteLine("$");

                return;
            }
        }

        public string fsid;
        public void ProF()
        {
            Console.WriteLine("F");
            fsid=ProID();
            ProFS();
            
        }
        public void ProFS()
        {
            Console.WriteLine("FS");
            if (checkTerminal("("))
            {
                Generate("define_method", "__", "__", fsid);
                ProFM();
                checkTerminalE(")");
                checkTerminalE(":");
                ProT();
                checkTerminal("{");
                ProE();
                checkTerminal("}");
                checkTerminal(";");
                Generate("end_define", "__", "__", "__");
                Program.SemanticStack.Clear();
                ProFP();
            }
            else if (checkTerminal(":"))
            {
                ProT();
                ProZ();
                checkTerminal(";");
                ProFP();
            }
            else
            {
                throw new ParserException(string.Format("Error at Line {0}:", Program.TokenList.Peek().LineNum));
            }
           
        }

        public void ProFP()//ERRIR
        {
            Console.WriteLine("FP");
            try
            {
                ProF();
            }
            catch(MissingFieldException)
            {
                Debug.WriteLine("$");

                return;
            }
          
        }
        public void ProZ()
        {
            Console.WriteLine("Z");
            if (checkTerminal("<-"))
            {
                ProE();
            }

            else
            {
                Debug.WriteLine("$");

                return;
            }
        }
        public void ProLEZ()
        {
            Console.WriteLine("Z");
            if (checkTerminal("<-"))
            {
                ProE();
                var y = Program.SemanticStack.Pop();
                var x = Program.SemanticStack.Pop();
                Generate("<-", y, "__", x);
            }

            else
            {
                Debug.WriteLine("$");

                return;
            }
        }
        public void ProFMS()
        {

            Console.WriteLine("FMS");
            if (checkTerminalN(")"))
            {
                return;
            }
            else
            {
                try
                {
                    Debug.WriteLine("Checking if FM FMS will work");
                    checkTerminalE(",");
                    ProFM();

                }
                catch (MissingFieldException)
                {
                    Debug.WriteLine("Not Exception... Change to Null");
                    Debug.WriteLine("$");

                    return;

                }
            }
                
        }
        public void ProFM()
        {
            Console.WriteLine("FM");

            if (checkTerminalN(")"))
            {
                return;
            }
           else
            {
                ProID();
                checkTerminalE(":");
                ProT();
                ProFMS();
            }
        }
        public string ProID()
        {
            Console.WriteLine("ID");

            if (checkTerminalN("ID"))
            {
                return ReadValueDeque();
            }
            else
                throw new MissingFieldException(
                    string.Format("Possible Error at Line {0}: Should be a ID?", Program.TokenList.Peek().LineNum));

            //var x = Program.TokenList.Peek().GetValue().ToCharArray();
            //if (char.IsLower(Program.TokenList.Peek().GetValue(), 0))
            //{
            //    Debug.WriteLine(Program.TokenList.Peek().GetValue());
            //    ReadDeque();
            //}
            //else
            //{
            //    throw new ParserException(string.Format("Error at Line {0}: Not Lowercase in Identifier",
            //        Program.TokenList.Peek().LineNum));
            //}


        }
        public int ProE()
        {
            Program.Token[] s = Program.TokenList.ToArray();
            Console.WriteLine("E");
            if (checkTerminalN("ID"))
                if (s[1].tokens == getTValue("<-"))
                {
                   var id= ProID();

                    checkTerminalE("<-");
                    ProE();
                    var x = Program.SemanticStack.Pop();
                    Generate("<-", x, "__", id);
                    Program.SemanticStack.Push(id);

                    return 1;
                }
                else
                {

                    ProG();


                    return 2;
                }

            else
            {
                if (checkTerminalN(")"))
                {
                    return 0;
                }
                else
                {
                    ProG();
                    return 3;
                }

            }
        }
        public void ProG()
        {
            var temp = ReadPeek();
            Console.WriteLine("G");
            if (checkTerminal("not"))
            {
                ProG();
                var x = Program.SemanticStack.Pop();
              
                var z = getNewVari();
                Generate("not", x, "__", z);
                Program.SemanticStack.Push(z);
            }
            else
            {
                ProH();
            }


        }
        public void ProH()
        {
            Console.WriteLine("H");
            ProI();
            ProHS();
        }

        public void ProHS()
        {
            Console.WriteLine("HS");
            if (checkTerminal("<="))
            {
                ProI();
                var x = Program.SemanticStack.Pop();
                var y = Program.SemanticStack.Pop();
                var z = getNewVari();
                Generate("<=", x, y, z);
                Program.SemanticStack.Push(z);
                ProHS();
            }
            else if (checkTerminal("<"))
            {
                ProI();
                var x = Program.SemanticStack.Pop();
                var y = Program.SemanticStack.Pop();
                var z = getNewVari();
                Generate("<", x, y, z);
                Program.SemanticStack.Push(z);
                ProHS();
            }
            else if (checkTerminal("="))
            {
                ProI();
                var x = Program.SemanticStack.Pop();
                var y = Program.SemanticStack.Pop();
                var z = getNewVari();
                Generate("=", x, y, z);
                Program.SemanticStack.Push(z);
                ProHS();
            }
            else
            {
                Debug.WriteLine("$");

                return;
            }
        }

        public void ProI()
        {
            Console.WriteLine("I");
            ProJ();
            ProIS();
        }
        public void ProIS()
        {
            Console.WriteLine("IS");
            if (checkTerminal("-"))
            {
                ProJ();
                var x = Program.SemanticStack.Pop();
                var y = Program.SemanticStack.Pop();
                var z = getNewVari();
                Generate("-", x, y, z);
                Program.SemanticStack.Push(z);
                ProIS();
            }
            else
            if (checkTerminal("+"))
            {
                ProJ();
                var x = Program.SemanticStack.Pop();
                var y = Program.SemanticStack.Pop();
                var z = getNewVari();
                Generate("+", x, y, z);
                Program.SemanticStack.Push(z);
                ProIS();
            }
            else
            {
                Debug.WriteLine("$");

                return;
            }
        }
        public void ProJ()
        {
            Console.WriteLine("J");
            ProK();
            ProJS();
        }
        public void ProJS()
        {
            Console.WriteLine("JS");
            if (checkTerminal("*"))
            {
                ProK();
                var x = Program.SemanticStack.Pop();
                var y= Program.SemanticStack.Pop();
                var z = getNewVari();
                Generate("*", x, y, z);
                Program.SemanticStack.Push(z);
                ProJS();
            }
            else if (checkTerminal("/"))
            {
                ProK();
                var x = Program.SemanticStack.Pop();
                var y = Program.SemanticStack.Pop();
                var z = getNewVari();
                Generate("/", x, y, z);
                Program.SemanticStack.Push(z);
                ProJS();
            }
            else
            {
                Debug.WriteLine("$");

                return;
            }
        }
        public void ProK()
        {
            Console.WriteLine("K");
            if (checkTerminal("isvoid"))
            {

                ProK();
                var x = Program.SemanticStack.Pop();
                var z = getNewVari();
                Generate("isvoid",x,"__",z);
                Program.SemanticStack.Push(z);
                //Program.SemanticStack.Pop();
                //Program.SemanticStack.Push();
            }
            else
            {
                ProL();
            }

        }
        public void ProL()
        {
            Console.WriteLine("L");
            if (checkTerminal("~"))
            {
                ProL();
                var x = Program.SemanticStack.Pop();
                var z=getNewVari();
                Generate("~",x,"__",z);
                Program.SemanticStack.Push(z);
            }
            else
            {
                ProM();
            }

        }
        public void ProM()
        {
            Console.WriteLine("M");
            ProN();
            ProMS();
        }
        public void ProMS()
        {
            Console.WriteLine("MS");
            if (checkTerminal("@"))
            {
                ProT();
                checkTerminalE(".");
               var tempID= ProID();
                checkTerminal("(");
                var t = ProE();
                string SEM1="";
                if (t != 0)
                {
                    SEM1 = Program.SemanticStack.Pop();
                    Generate("add_par", SEM1, "__", "__");
                }

                ProEP();
                checkTerminal(")");
                var z = getNewVari();
                Generate("call", tempID, "__", z);
                Program.SemanticStack.Push(z);
                ProMS();

            }
            else
                if (checkTerminal("."))
            {
                var tempID = ProID();
                checkTerminalE("(");
                var t = ProE();
                string SEM1="";
                if (t != 0)
                {
                     SEM1 = Program.SemanticStack.Pop();
                    Generate("add_par", SEM1, "__", "__");
                }
                ProEP();
                checkTerminalE(")");
                ProMS();
                var z = getNewVari();
                Generate("call", tempID, "__", z);
                Program.SemanticStack.Push(z);

            }
            else
            {
                Debug.WriteLine("$");
                return;
                // throw new ParserException(string.Format("Error at Line {0}: Supposed @ or .", Program.TokenList.Peek().LineNum));
            }



        }

        public string getNewVari()
        {
            var t = "t" + GeQcount;
            GeQcount++;
            return t;
        }
        public void ProN()
        {
            Console.WriteLine("N");
            if (checkTerminal("("))
            {
                ProE();
                checkTerminalE(")");
            }
            else
            {

                if (checkTerminalN("ID"))
                {

                    Program.Token[] tmp = Program.TokenList.ToArray();
                    if (tmp[1].tokens == getTValue("("))
                    {
                        var tempID=ProID();
                        checkTerminalE("(");
                        var t = ProE();
                        if (t != 0)
                        {
                            var SEM1 = Program.SemanticStack.Pop();
                            Generate("add_par", SEM1, "__", "__");
                        }


                        ProEP();
                        checkTerminalE(")");
                        var z = getNewVari();
                        Generate("call",tempID , "__", z);
                        Program.SemanticStack.Push(z);

                        //if (checkTerminal("("))
                        //{
                        //    ProE();

                        //    //  checkTerminalE(",");
                        //    ProEP();
                        //    checkTerminalE(")");
                        //}
                        //else
                        //{
                        //    return;
                        //}
                    }
                    else
                    {
                        var tempID=  ProID();
                        Program.SemanticStack.Push(tempID);
                    }
                }
                else
                {
                    if (checkTerminalN("Integer"))
                    {
                        var tempID = ReadValueDeque();
                        Program.SemanticStack.Push(tempID);
                    }
                    else if (checkTerminalN("String"))
                    {
                        var tempID = ReadValueDeque();
                        Program.SemanticStack.Push(tempID);
                        // Program.SemanticStack.Push();
                    }
                    else if (checkTerminal("true"))
                    {
                       
                        Program.SemanticStack.Push("true");

                    }
                    else if (checkTerminal("false"))
                    {
                        Program.SemanticStack.Push("false");
                    }
                    else if (checkTerminal("self"))
                    {

                    }
                    else if (checkTerminal("new"))
                    {

                        var tempT=ProT();//(New, Type,___,tmp1)
                        var z = getNewVari();
                        Generate("new",tempT,"__",z);
                        Program.SemanticStack.Push(z);
                        //GenQ("new",a,"_"
                    }
                    else if (checkTerminal("if"))
                    {
                        Generate("if", "__", "__", "__");
                        ProE();
                       var x= Program.SemanticStack.Pop();

                        var lineFill=Generate("j=", x, "false", "__");//wait to fill


                        checkTerminalE("then");
                        ProE();
                        quadList[lineFill].result = (GeqLine + 1).ToString();
                        lineFill = Generate("j", "__", "__", "__");

                        
                        checkTerminalE("else");
                        ProE();
                        quadList[lineFill].result = (GeqLine + 1).ToString();

                        checkTerminalE("fi");
                        Generate("end_if", "__", "__", "__");
                    }
                    else if (checkTerminal("while"))
                    {
                        var temp_w=Generate("while", "__", "__", "__");

                        ProE();
                        var x=Program.SemanticStack.Pop();
                        var temp_x = Generate("j=", x, "false", "__");

                        checkTerminalE("loop");
                        ProE();
                        quadList[temp_x].result = (GeqLine + 1).ToString();
                        checkTerminalE("pool");
                        Generate("j", "__", "__",temp_w.ToString());
                        Generate("end_while", "__", "__", "__");
                    }
                    else if (checkTerminal("{"))
                    {
                        ProE();
                        checkTerminalE(";");
                        ProEPS();
                        checkTerminalE("}");
                    }
                    else if (checkTerminal("let"))
                    {
                        Generate("enter_scope", "__", "__", "__");

                        var id = ProID();
                        Program.SemanticStack.Push(id);
                        checkTerminalE(":");
                        ProT();
                        ProLEZ();
                        

                        ProLE();
                        checkTerminalE("in");
                        ProE();
                        Generate("exit_scope", "__", "__", "__");

                    }
                    else if (checkTerminal("case"))
                    {
                        Generate("case", "__", "__", "__");

                        ProE();
                        checkTerminal("of");
                        ProCA();
                        checkTerminal("esac");
                        foreach (var line in WaitList)
                        {
                            quadList[line].result = GeqLine.ToString();
                        }
                        WaitList.Clear();
                        Generate("exit_case", "__", "__", "__");
                    }
                }

            }
        }

        public void ProNA()
        {
            Console.WriteLine("NA");
        }

        public string tempCA;
        public void ProCA()
        {
            tempCA= Program.SemanticStack.Pop();
            Console.WriteLine("CA");
            ProID();
            checkTerminalE(":");
            var tempT=ProT();
            var linNum=Generate("j_checktype",tempCA,tempT,"__");//place no back
            checkTerminalE("=>");
            ProE();
            //Fill back
            quadList[linNum].result = (GeqLine+1).ToString();
            var waitLine=Generate("j", "__", "__", "__");//wait to jump, return linenow
            WaitList.Add(waitLine);
            checkTerminalE(";");
            
            ProCAS();

        }
        public List<int> WaitList=new List<int>();
        public void ProCAS()
        {
            Console.WriteLine("CAS");
            if (checkTerminalN("ID"))
            {
                ProID();
                checkTerminalE(":");
                var tempT = ProT();
                var linNum = Generate("j_checktype", tempCA, tempT, "__");//place no back
               
                checkTerminalE("=>");
                ProE();
                //Fill back
                quadList[linNum].result = (GeqLine + 1).ToString();
                var waitLine = Generate("j", "__", "__", "__");//wait to jump, return linenow
                WaitList.Add(waitLine);
                checkTerminalE(";");
                ProCAS();
            }
            else
            {
                Debug.WriteLine("$");

                return;
            }
        }

        public void ProLE()
        {
            Console.WriteLine("LE");
            if (checkTerminal(","))
            {
                var id=ProID();
                Program.SemanticStack.Push(id);
                checkTerminal(":");
                ProT();
                ProLEZ();
           
                ProLE();
            }
            else
            {
                Debug.WriteLine("$");

                return;
            }
        }

        public void ProEP()
        {
            Console.WriteLine("EP");
            if (checkTerminal(","))
            {
                ProE();

                var SEM1 = Program.SemanticStack.Pop();
                Generate("add_par", SEM1, "__","__");
              
                ProEP();
            }
            else
            {
                Debug.WriteLine("$");

                return;
            }
        }

        public void ProEPS()
        {
            Console.WriteLine("EPS");
            if (checkTerminalN("}"))
            {
                Debug.WriteLine("$");

                return;
            }
            else
            {

                Program.SemanticStack.Pop();
                ProE();
                checkTerminalE(";");
                ProEPS();
                
            }
          
        }


        public class Quad
        {
            public string op;
            public string arg1;
            public string arg2;
            public string result;

            public  Quad(string Op, string Arg1, string Arg2, string Result)
            {
                this.op = Op;
                this.arg1 = Arg1;
                this.arg2 = Arg2;
                this.result = Result;
            }

            public  override string  ToString()
            {
                return (String.Format("({0},{1},{2},{3})", op, arg1, arg2, result));
            }
        }
        public static List<Quad> quadList=new List<Quad>();
        public static int GeQcount = 0;
        public static int GeqLine = 0;
        public int Generate(string op, string arg1, string arg2, string result)
        {
            
            var q=new Quad(op,arg1,arg2,result);
            quadList.Add(q);
            Debug.WriteLine(String.Format("{4}:({0},{1},{2},{3})", op, arg1, arg2, result,GeqLine));
            GeqLine++;
            var lineNow = GeqLine - 1;
            return lineNow;
        }
        //public void Gequad(OperationType type, string op)
        //{
        //    var t = "t" + (++GeQcount);
        //    switch (type)
        //    {
        //        case OperationType.Arith:
        //            {
        //                switch (op)
        //                {
        //                    case "isvoid":
        //                    case "~":
        //                        {
                                   
        //                            break;
        //                    }
        //                    case "add_par":
        //                        {
        //                            var SEM1 = Program.SemanticStack.Pop();
        //                            Generate(op, SEM1, "__", "__");
                                    
        //                            break;
        //                        }
        //                    case "new":
        //                    {
        //                            Generate(op, SEM1, "__", t.ToString());
        //                            Program.SemanticStack.Push(t.ToString());
        //                            break;

        //                    }
        //                    default:
        //                        break;
        //                }
                           
        //                    //var SEM1 = Program.SemanticStack.Pop();
        //                    //var SEM2 = Program.SemanticStack.Pop();


                            
                          
                        
        //                break;
        //            }
        //        case OperationType.Call:
        //            {
        //                break;

        //            }
        //        case OperationType.Jump:
        //            {
        //                break;
        //            }
        //    }


        //}

        public enum OperationType
        {
            Arith = 0,
            Jump = 1,
            Call = 2

        }

    }
}

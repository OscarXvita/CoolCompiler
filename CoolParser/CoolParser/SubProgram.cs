﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
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
        class Node
        {
            public Node LeftChild { get; private set; }
            public Node RightChild { get; private set; }
            public char Label { get; private set; }

            public Node(char label, Node left, Node right)
            {
                Label = label;
                LeftChild = left;
                RightChild = right;
            }
        }

        public void ProP()
        {

            ProC();

            Console.WriteLine("Completed!");
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
              //  Debug.WriteLine("MATCHED[N]: " + terminal);
                //ReadDeque();
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

            //    if (Program.TokenList.Peek().tokens == (int)strToToken.e_typeCname)
            //    {
            //        ProT();
            //        if (Program.TokenList.Peek().tokens == (int)strToToken.e_in)
            //        {
            //            ProIN();
            //            Program.TokenList.Dequeue();
            //            if (Program.TokenList.Peek().tokens == (int)strToToken.e_llb)
            //            {
            //                ProF();
            //                if (Program.TokenList.Peek().tokens == (int)strToToken.e_lrb)
            //                {
            //                    if (Program.TokenList.Peek().tokens == (int)strToToken.e_semicolon)
            //                    {
            //                        ProCS();

            //                    }
            //                    else
            //                    {
            //                        throw new ParserException(string.Format("Error at Line {0}", Program.TokenList.Peek().LineNum));
            //                    }
            //                }
            //                else
            //                {
            //                    throw new ParserException(string.Format("Error at Line {0}", Program.TokenList.Peek().LineNum));
            //                }
            //            }
            //            else
            //            {
            //                throw new ParserException(string.Format("Error at Line {0}", Program.TokenList.Peek().LineNum));
            //            }
            //        }
            //        else
            //        {
            //            throw new ParserException(string.Format("Error at Line {0}", Program.TokenList.Peek().LineNum));
            //        }

            //    }
            //    else
            //    {
            //        throw new ParserException(string.Format("Error at Line {0}", Program.TokenList.Peek().LineNum));
            //    }
            //}
            // else
            // {
            //     throw new ParserException(string.Format("Error at Line {0}", Program.TokenList.Peek().LineNum));
            // }



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
        public void ProT()//possib
        {
            Console.WriteLine("T");
            if (ReadPeek() == getTValue("Type"))
                if (Program.TokenList.Peek().GetValue() != "")
                {
                    if (char.IsUpper(Program.TokenList.Peek().GetValue(), 0))
                    {
                        //Debug.WriteLine(Program.TokenList.Peek().GetValue());
                        ReadDeque();
                    }
                    else
                    {
                        throw new ParserException(string.Format("Error at Line {0}: Not Uppercase in Type Name", Program.TokenList.Peek().LineNum));
                    }
                }

                else
                    throw new MissingFieldException(string.Format("Possible Error at Line {0}: Should be a T?", Program.TokenList.Peek().LineNum));

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
        public void ProF()
        {
            Console.WriteLine("F");
            ProID();
            ProFS();

        }
        public void ProFS()
        {
            Console.WriteLine("FS");
            if (checkTerminal("("))
            {
                ProFM();
                checkTerminalE(")");
                checkTerminalE(":");
                ProT();
                checkTerminal("{");
                ProE();
                checkTerminal("}");
                checkTerminal(";");
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
        public void ProID()
        {
            Console.WriteLine("ID");

            if (checkTerminal("ID"))
            {

            }
            else
                throw new MissingFieldException(string.Format("Possible Error at Line {0}: Should be a ID?", Program.TokenList.Peek().LineNum));

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
        public void ProE()
        {
            Program.Token[] s = Program.TokenList.ToArray();
            Console.WriteLine("E");
            if (checkTerminalN("ID"))
                if (s[1].tokens == getTValue("<-"))
                {
                    ProID();
                    checkTerminalE("<-");
                    ProE();
                    return;
                }
                else
                {

                    ProG();



                }

            else
            {
                if (checkTerminalN(")"))
                {
                    return;
                }
                else
                {
                    ProG();
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
                ProHS();
            }
            else if (checkTerminal("<"))
            {
                ProI();
                ProHS();
            }
            else if (checkTerminal("="))
            {
                ProI();
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
                ProIS();
            }
            else
            if (checkTerminal("+"))
            {
                ProJ();
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
                ProJS();
            }
            else if (checkTerminal("/"))
            {
                ProK();
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
                ProID();
                checkTerminal("(");
                ProE();
                ProEP();
                checkTerminal(")");
                ProMS();

            }
            else
                if (checkTerminal("."))
            {
                ProID();
                checkTerminalE("(");
                ProE();
                ProEP();
                checkTerminalE(")");
                ProMS();
            }
            else
            {
                Debug.WriteLine("$");
                return;
                // throw new ParserException(string.Format("Error at Line {0}: Supposed @ or .", Program.TokenList.Peek().LineNum));
            }



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
                        ProID();
                        checkTerminalE("(");
                        ProE();
                        ProEP();
                        checkTerminalE(")");
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
                        ProID();

                    }
                }
                else
                {
                    if (checkTerminal("Integer"))
                    {

                    }
                    else if (checkTerminal("String"))
                    {

                    }
                    else if (checkTerminal("true"))
                    {

                    }
                    else if (checkTerminal("false"))
                    {

                    }
                    else if (checkTerminal("self"))
                    {

                    }
                    else if (checkTerminal("new"))
                    {
                        ProT();
                    }
                    else if (checkTerminal("if"))
                    {
                        ProE();
                        checkTerminalE("then");
                        ProE();
                        checkTerminalE("else");
                        ProE();
                        checkTerminalE("fi");
                    }
                    else if (checkTerminal("while"))
                    {
                        ProE();
                        checkTerminalE("loop");
                        ProE();
                        checkTerminalE("pool");
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
                        ProID();
                        checkTerminalE(":");
                        ProT();
                        ProZ();
                        ProLE();
                        checkTerminalE("in");
                        ProE();
                    }
                    else if (checkTerminal("case"))
                    {
                        ProE();
                        checkTerminal("of");
                        ProCA();
                        checkTerminal("esac");
                    }
                }

            }
        }

        public void ProNA()
        {
            Console.WriteLine("NA");
        }
        public void ProCA()
        {
            Console.WriteLine("CA");
            ProID();
            checkTerminalE(":");
            ProT();
            checkTerminalE("=>");
            ProE();
            checkTerminalE(";");
            ProCAS();
        }

        public void ProCAS()
        {
            Console.WriteLine("CAS");
            if (checkTerminalN("ID"))
            {
                ProID();
                checkTerminalE(":");
                ProT();
                checkTerminalE("=>");
                ProE();
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
                ProID();
                checkTerminal(":");
                ProT();
                ProZ();
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
                

                ProE();
                checkTerminalE(";");
                ProEPS();
                
            }
          
        }
    }
}

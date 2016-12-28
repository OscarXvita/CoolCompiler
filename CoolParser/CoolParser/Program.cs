using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net.Mime;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.RegularExpressions;
using static CoolParser.SubProgram;

namespace CoolParser
{
    class Program
    {
       
        public static Stack<string> SemanticStack=new Stack<string>();
        public static Queue<Token> TokenList=new Queue<Token>();
        static void Main(string[] args)
        {
            FileInfo info = new FileInfo("result.txt");
            var tokens=info.OpenText();
            int i = 0;//line counter
            try
            {
                while (!tokens.EndOfStream)
                {
                    string lineNow = tokens.ReadLine();
                   

                    i++;
                    if (lineNow.Trim().Length != 0)
                        ParseAddTokens(lineNow);

                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error! " + ex.Message);
                return;

            }


            try
            {
                SubProgram sub = new SubProgram();
                sub.ProP();
            }
            catch (ParserException e)
            {
                Console.WriteLine(e.Message);
            }

            Console.ReadLine();
        }

        static void ParseAddTokens(string line)
        {

            var space1 = line.IndexOf(" ");
            var space2 = line.IndexOf(" ", space1 + 1);
            Token token = new Token();
            token.LineNum = Convert.ToInt32(line.Substring(0, space1).Remove(0, 1));

            if (space2 != -1)
            {
                //#

                token.tokens = Convert.ToInt32(line.Substring(space1 + 1, space2 - space1 - 1));
               token.SetValue(line.Substring(space2 + 1, line.Length - space2 - 1));
            }
            else
            {
                token.tokens = Convert.ToInt32(line.Substring(space1 + 1, line.Length - space1 - 1));
            }
        
            Debug.WriteLine("Line"+token.LineNum+"\tToken:"+token.tokens+"\tValue:"+token.GetValue());
            TokenList.Enqueue(token);
        }

      

        public class Token
        {
            private string _value;
            private int _tokens;
            private int _lineNum;

            public int LineNum
            {
                get { return _lineNum; }
                set { _lineNum = value; }
            }

            public int tokens
            {
                get { return _tokens; }
                set
                {
                    if (value < 0)
                        throw new FormatException("ILLEGAL TOKEN");
                    else
                    _tokens = value;
                }
            }


            public void SetValue(string value)
            {
             
                _value = value;

            }

            public string GetValue()
            {
                return _value;
            }
            
        }
    }
  
}

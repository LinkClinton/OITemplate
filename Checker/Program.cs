using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using OISharp;

namespace Checker
{
    class Program
    {
        static int N;
        static int M;

        static List<int>[] m;

        static int OutAns;

        static void ReadInput()
        {
            Reader.Initalize(@"C:\OI\Template\Template\T.in");
        }

        static void ReadOutPut()
        {
            Reader.Initalize(@"C:\OI\Template\Template\T.out");
            OutAns = Reader.Int;
        }

        static void Main(string[] args)
        {
            ReadInput();
            ReadOutPut();

            
        }
    }
}

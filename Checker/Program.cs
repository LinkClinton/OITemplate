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
        static int N, M;

        static int[] from;
        static int[] to;
        static int[] t;

        static bool[] Is;
        static int[] cnt;

        static void ReadInput()
        {
            Reader.Initalize(@"C:\OI\Template\Template\T.in");
            N = Reader.Int;
            M = Reader.Int;
            from = new int[M];
            to = new int[M];
            t = new int[M];
            for (int i = 0; i < M; i++)
            {  
                from[i] = Reader.Int;
                to[i]= Reader.Int;
                t[i] = Reader.Int;
            }
            Is = new bool[N + 1];
            cnt = new int[N + 1];
        }

        static void ReadOutPut()
        {
            Reader.Initalize(@"C:\OI\Template\Template\T.out");
            int Ans = Reader.Int;
            for (int i = 1; i <= Ans; i++)
            {
                Is[Reader.Int] = true;
            }
        }

        static void Main(string[] args)
        {
            ReadInput();
            ReadOutPut();

            for (int i = 0; i < M; i++)
            {
                if (t[i] == 0)
                {
                    if (Is[to[i]] == false)
                    {
                        if (Is[i] && cnt[i] == 0) cnt[i]++;
                        else { Console.WriteLine("Failed"); break; }
                    } 
                }else
                {
                    if (Is[to[i]] == true)
                    {
                        if (Is[i] && cnt[i] == 0) cnt[i]++;
                        else { Console.WriteLine("Failed"); break; }
                    }
                }
            }
            Console.WriteLine("OK");
            Console.ReadKey();
        }
    }
}

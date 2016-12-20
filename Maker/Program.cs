using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// Make Data 
/// </summary>
namespace Maker
{
    class Program
    {
        static Random data = new Random();

        static void Main(string[] args)
        {
            OISharp.Writer.Initalize(@"C:\OI\Template\Template\T.in");

            int N = 500;
            int M = 100;
            OISharp.Writer.ShowLine(N + " " + M);

            for (int i = 1; i <= M; i++)
            {
                int u = data.Next(1, N + 1);
                int v = data.Next(1, N + 1);
                while (u == v)
                    u = data.Next(1, N + 1);
                int kind = data.Next(0, 2);
                OISharp.Writer.ShowLine(u + " " + v + " " + kind);
            }

            OISharp.Writer.Flush();

         

        }
    }
}

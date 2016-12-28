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

            int N = 20;
            int M = 50;

            OISharp.Writer.ShowLine(N + " " + M);

            for (int i = 1; i <= M; i++)
            {
                int u = data.Next(1, N);
                int v = data.Next(1, N);
                OISharp.Writer.ShowLine(u + " " + v);
            }

            OISharp.Writer.Flush();

        }
    }
}

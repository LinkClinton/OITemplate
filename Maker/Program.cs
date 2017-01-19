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

            int N = 1000;

            OISharp.Writer.WriteLine(N.ToString());

            OISharp.Data.Tree tree = new OISharp.Data.Tree(N, OISharp.Data.TreeValue.Edge, 1, 10000);

            tree.WriteLine();

            int M = 1000;

            OISharp.Writer.WriteLine(M.ToString());

            for (int i = 1; i <= M; i++)
            {
                int t = data.Next(1, N - 2);
                t = N - 10;
                bool[] vis = new bool[N + 1];
                vis[1] = true;
                OISharp.Writer.Write(t + " ");

                for (int j = 1; j <= t; j++)
                {
                    int v = data.Next(1, N);
                    while (vis[v]) v = data.Next(1, N);
                    vis[v] = true;
                    OISharp.Writer.Write(v + " ");
                }
                OISharp.Writer.WriteLine("");
            }

            OISharp.Writer.Flush();
        }
    }
}

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
            
            int N = 100;

            OISharp.Writer.ShowLine(N.ToString());

            for (int i = 1; i <= N; i++)
            {
                int u = data.Next(1, 10);
                int v = data.Next(1, 10);
                int d = data.Next(1, Math.Min(u, v));
                OISharp.Writer.ShowLine(u + " " + v + " " + d);
            }

            OISharp.Writer.Flush();

        }
    }
}

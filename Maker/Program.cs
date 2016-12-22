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
            int M = 7;
            OISharp.Writer.ShowLine(N + " " + M);
            for (int i = 1; i <= N; i++)
            {
                for (int j = 1; j <= M; j++)
                {
                    OISharp.Writer.Show(data.Next(-500, 500) + " ");
                }
                OISharp.Writer.ShowLine("");
            }

            OISharp.Writer.Flush();

         

        }
    }
}

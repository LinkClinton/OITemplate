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

        static int GetZeroAndOne()
        {
            if (data.Next(1, 1000) >= 995) return 1;
            return 0;
        }

        static void Main(string[] args)
        {
            OISharp.Writer.Initalize(@"C:\OI\Template\Template\T.in");

            OISharp.Writer.WriteLine("1");

            int a = 12;
            int b = 20;
            int c = 20;
            OISharp.Writer.WriteLine(a + " " + b + " " + c);

            for (int i = 1; i <= a; i++)
            {
                for (int j = 1; j <= b; j++)
                {
                    for (int k = 1; k <= c; k++)
                    {
                        OISharp.Writer.Write(GetZeroAndOne() + " ");
                    }
                    OISharp.Writer.WriteLine("");
                }
            }
            OISharp.Writer.Flush();

        }
    }
}

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

            int N = 200;
            int K = 199;

            OISharp.Writer.WriteLine(N + " " + K);

            for (int i = 1; i <= N; i++)
            {
                int value = data.Next(0, 1000);
                if (value <= 100) value = 0;
                OISharp.Writer.Write(value + " ");
            }
            OISharp.Writer.WriteLine("");

            OISharp.Writer.Flush();
        }
    }
}

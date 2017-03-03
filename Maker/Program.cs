using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maker
{
    class Program
    {
        static System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\OI\Template\Template\T.in");
        static Random data = new Random();
        
        static void Main(string[] args)
        {
            int n = 5000;
            int m = 5000;

            file.WriteLine(n + " " + m);

            for (int i = 1; i <= n; i++)
            {
                file.Write(data.Next(1, 100000) + " ");
            }
            file.WriteLine();

            for (int i = 1; i <= m; i++)
            {
                int kind = data.Next(0, 2);
                if (kind == 0)
                {
                    int l = data.Next(1, n - 1);
                    int r = data.Next(l, n);
                    int value = data.Next(1, 100000);
                    file.WriteLine(kind + " " + l + " " + r + " " + value);
                }else
                {
                    int l = data.Next(1, n - 1);
                    int r = data.Next(l, n);
                    file.WriteLine(kind + " " + l + " " + r);
                }
            }
            file.Flush();

        }
    }
}

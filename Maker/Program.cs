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

        static void Swap<T>(ref T x,ref T y)
        {
            T t = x;
            x = y;
            y = t;
        }

        static void Main(string[] args)
        {
            OISharp.Writer.Initalize(@"C:\OI\Template\Template\T.in");

            int N, P, Q;

            N = 5;
            P = 5;
            Q = 5;

            OISharp.Writer.WriteLine(N + " " + P + " " + Q);

            int[] listx = new int[P];
            int[] listy = new int[P];

            for (int i = 1; i < N; i++)
            {
                OISharp.Writer.WriteLine(i + " " + (i + 1));
            }

            for (int i = 0; i < P; i++)
            {
                listx[i] = data.Next(1, N);
                listy[i] = data.Next(1, N);
                while (listx[i] == listy[i])
                {
                    listx[i] = data.Next(1, N);
                    listy[i] = data.Next(1, N);
                }
                if (listx[i] > listy[i]) Swap(ref listx[i], ref listy[i]);
                OISharp.Writer.WriteLine(listx[i] + " " + listy[i] + " " + data.Next(1, 10000));
            }

            for (int i = 0; i < Q; i++)
            {
                int x = data.Next(1, N);
                int y = data.Next(1, N);
                while (x == y)
                {
                    x = data.Next(1, N);
                    y = data.Next(1, N);
                }
                if (x > y) Swap(ref x, ref y);
                int cnt = 0;
                for (int j = 0; j < P; j++)
                {
                    if (listx[j] <= x && listy[j] >= y) cnt++;
                }
                int k = data.Next(1, cnt);
                OISharp.Writer.WriteLine(x + " " + y + " " + k);
            }
            


            OISharp.Writer.Flush();

        }
    }
}

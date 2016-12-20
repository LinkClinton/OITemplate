using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OISharp.Data
{
    public class Permutation : Sequence
    {
        public Permutation(int size)
        {
            Random data = new Random();

            bool[] showed = new bool[size];

            arr = new int[size];

            for (int i = 0; i < size; i++)
            {
                int value = data.Next(0, size);

                while (showed[value] == true)
                    value = data.Next(0, size);

                showed[value] = true;

                arr[i] = value + 1;
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OISharp.Data
{
    public class Sequence
    {
        internal int[] arr;

        internal Sequence()
        {

        }

        public Sequence(int size, int min_value, int max_value)
        {
            arr = new int[size];

            Random data = new Random();

            if (max_value < min_value) max_value = min_value;

            for (int i = 0; i < size; i++)
                arr[i] = data.Next(min_value, max_value + 1);
        }

        public void Show()
        {
            for (int i = 0; i < arr.Length; i++)
                Writer.Show(arr[i] + " ");
        }

        public void ShowLine()
        {
            for (int i = 0; i < arr.Length; i++)
                Writer.ShowLine(arr[i].ToString());
        }

        public int[] Source
        {
            get { return arr; }
        }
    }
}

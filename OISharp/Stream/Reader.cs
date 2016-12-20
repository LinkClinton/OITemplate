using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OISharp
{
    public static class Reader
    {
        static bool IsFile = false;
        static System.IO.StreamReader reader;

        private static int Read()
        {
            if (IsFile) return reader.Read();
            else return Console.Read();
        }

        private static uint URead()
        {
            if (IsFile) return (uint)reader.Read();
            else return (uint)Console.Read();
        }
     
        public static int Int
        {
            get
            {
                int x = 0;
                int f = 1;
                int ch = Read();
                while (ch < '0' || ch > '9')
                {
                    if (ch == '-') f = -1;
                    ch = Read();
                }
                while (ch >= '0' && ch <= '9')
                {
                    x = x * 10 + ch - '0';
                    ch = Read();
                }
                return (int)x * (int)f;
            }
        }

        public static uint UInt
        {
            get
            {
                UInt64 x = 0;
                UInt64 ch = URead();
                while (ch < '0' || ch > '9')
                {
                    ch = URead();
                }
                while (ch >= '0' && ch <= '9')
                {
                    x = x * 10 + ch - '0';
                    ch = URead();
                }
                return (uint)x;
            }
        }

        public static int Char
        {
            get
            {
                Int64 ch = Read();
                while (ch == (int)ConsoleKey.Spacebar || ch == (int)ConsoleKey.Enter)
                {
                    ch = Read();
                }
                return (char)ch;
            }
        }

        public static string String
        {
            get
            {
                string res = "";
                Int64 ch = Read();
                while (ch == (int)ConsoleKey.Spacebar || ch == (int)ConsoleKey.Enter || ch == 10)
                {
                    ch = Read();
                }
                while (ch != (int)ConsoleKey.Spacebar && ch != (int)ConsoleKey.Enter && ch != 10)
                {
                    res += (char)ch;
                    ch = Read();
                }
                return res;
            }
        }

        


        public static void Initalize(string path)
        {
            IsFile = true;
            reader = new System.IO.StreamReader(path);
        }

        public static void Initalize()
        {
            IsFile = false;
        }
    }
}

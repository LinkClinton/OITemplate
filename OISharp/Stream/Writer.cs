using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OISharp
{
    public static class Writer
    {
        private static bool IsFile = false;
        private static System.IO.StreamWriter writer;

        
        public static void Initalize(string path)
        {
            IsFile = true;
            if (System.IO.File.Exists(path))
                System.IO.File.Delete(path);
            writer = new System.IO.StreamWriter(path);
        }

        public static void Initalize()
        {
            IsFile = false;
        }

        public static void Show(string str)
        {
            if (IsFile)
                writer.Write(str);
            else Console.Write(str);
        }

        public static void ShowLine(string str)
        {
            if (IsFile)
                writer.WriteLine(str);
            else Console.WriteLine(str);
        }

        public static void Flush()
        {
            if (IsFile) writer.Flush();
        }
    }
}

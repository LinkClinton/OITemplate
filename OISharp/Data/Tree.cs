using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OISharp.Data
{
    public enum TreeValue
    {
        Edge, Point, None
    }

    public class Tree
    {
        TreeNode[] node;

        TreeValue treekind;

        internal Tree() { }

        public Tree(int size)
        {
            Random data = new Random();

            node = new TreeNode[size];

            for (int i = 0; i < size; i++)
            {
                node[i] = new TreeNode()
                {
                    ID = i + 1,
                    Parent = node[data.Next(0, i)]
                };
            }
        }

        public Tree(int size,TreeValue kind,int min_value,int max_value)
        {
            Random data = new Random();

            node = new TreeNode[size];

            if (max_value < min_value) max_value = min_value;

            for (int i = 0; i < size; i++)
            {
                node[i] = new TreeNode()
                {
                    ID = i + 1,
                    Parent = node[data.Next(0, i)]
                };

                node[i].kind = kind;
                if (kind == TreeValue.Point)
                {
                    node[i].Point = data.Next(min_value, max_value + 1);
                }else if (kind == TreeValue.Edge)
                {
                    node[i].Edge = data.Next(min_value, max_value + 1);
                }
            }

            treekind = kind;
        }

        public TreeValue Kind
        {
            get { return treekind; }
        }
        
        public void Show()
        {
            if (Kind == TreeValue.Point)
                for (int i = 0; i < node.Length; i++)
                    Writer.Show(node[i].Point + " ");

            Writer.ShowLine("");

            for (int i = 0; i < node.Length; i++)
                Writer.ShowLine(node[i].ToString());
        }

        public void ShowLine()
        {
            if (Kind == TreeValue.Point)
                for (int i = 0; i < node.Length; i++)
                    Writer.ShowLine(node[i].Point.ToString());

            for (int i = 0; i < node.Length; i++)
                Writer.ShowLine(node[i].ToString());

        }
        
    }
}

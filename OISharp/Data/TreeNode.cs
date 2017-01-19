using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OISharp.Data
{
    public class TreeNode
    {
        private int id;
        private TreeNode parent;
        private int n_value;

        internal TreeValue kind = TreeValue.None;

        public TreeNode Parent
        {
            get { return parent; }
            set { parent = value; }
        }

        public int Edge
        {
            get { return n_value; }
            set { n_value = value; kind = TreeValue.Edge; }
        }

        public int Point
        {
            get { return n_value; }
            set { n_value = value;kind = TreeValue.Point; }
        }

        public TreeValue Kind
        {
            get { return kind; }
        }

        public bool IsRoot
        {
            get { if (parent == null) return true; return false; }
        }

        public int ID
        {
            get { return id; }
            set { id = value; }
        }

        public void ShowLine()
        {
            if (kind == TreeValue.Edge)
                Writer.WriteLine(id + " " + parent.id + " " + n_value);
            else
                Writer.WriteLine(id + " " + parent.id);
        }

        public override string ToString()
        {
            if (parent == null) return "";
            if (kind == TreeValue.Edge) return id + " " + parent.id + " " + n_value;
            else return id + " " + parent.id;
        }
    }
}

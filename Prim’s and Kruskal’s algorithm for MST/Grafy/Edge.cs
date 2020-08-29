using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Grafy
{
    class Edge
    {
        public double Value { get; private set; }
        public int Point1 { get; private set; }
        public int Point2 { get; private set; }

        public Edge(int pt1, int pt2, double value)
        {
            Point1 = pt1;
            Point2 = pt2;
            Value = value;
        }

        public override string ToString()
        {
            return String.Format("({0}-{1})={2:0.00}", Point1, Point2, Value);
        }
    }
}

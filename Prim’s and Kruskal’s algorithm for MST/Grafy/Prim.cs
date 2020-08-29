using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Grafy
{
    class Prim
    {
        public Edge[] Result { get; private set; }
        public double Span { get; private set; }
        public Edge[] edges { get; private set; }
        public int NumberOfPoints { get; private set; }

        public Prim (Edge[] edges)
        {
            this.edges = edges;
        }

        public void Find(int start)
        {
            CountPoints();
            List<Edge> Queue = new List<Edge> ();
            Result = new Edge[NumberOfPoints-1];
            bool[] visited = new bool[NumberOfPoints] ;
            int v, u;
            v = start;
            visited[v] = true;
            Edge pom;

            for (int i = 0; i < NumberOfPoints - 1; i++)
            {
                foreach (var edge in edges)
                {
                    if (edge.Point1 == v || edge.Point2 == v)
                    {
                        u = (edge.Point1 == v) ? edge.Point2 : edge.Point1;
                        if (!visited[u])
                            Queue.Add(edge);
                    }
                }
                Queue.Sort((p1, p2) => p1.Value.CompareTo(p2.Value));
                do
                {
                    pom = Queue.First();
                    v = pom.Point1;
                    u = pom.Point2;
                    Queue.Remove(pom);

                } while (visited[u] && visited[v]);
                Result[i] = pom;
                Span += pom.Value;
                if (visited[u])
                    visited[v] = true;
                else if (visited[v])
                {
                    visited[u] = true;
                    v = u;
                }          
            }
      
        }

        public void CountPoints()
        {
            NumberOfPoints = 0;
            //zlicza ile punktów jest w grafie
            foreach (var edge in edges)
            {
                if (edge.Point1 > NumberOfPoints)
                    NumberOfPoints = edge.Point1;
                if (edge.Point2 > NumberOfPoints)
                    NumberOfPoints = edge.Point2;
            }
            NumberOfPoints++;
        }
    }
}

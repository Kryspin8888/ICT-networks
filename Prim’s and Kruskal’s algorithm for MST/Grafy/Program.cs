using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Grafy
{
    class Program
    {
        static void Main(string[] args)
        {
            Edge[] edges = new Edge[]
        {
            new Edge(4,6,1), new Edge(4,5,2), new Edge(2,7,3),
            new Edge(0,6,3), new Edge(2,4,4), new Edge(0,1,5),
            new Edge(2,6,5), new Edge(1,5,6), new Edge(5,6,6),
            new Edge(1,7,7), new Edge(1,4,8), new Edge(3,6,8),
            new Edge(0,3,9), new Edge(1,2,9), new Edge(2,3,9),
            new Edge(6,7,9)
        };

            var kruskal = new Kruskal(edges);
            kruskal.Find();
            Console.WriteLine(String.Format("Algorytm Kruskala \nRozpiętość {0:0.00}", kruskal.Span));
            for (int i = 0; i < kruskal.Result.Length; i++)
                Console.WriteLine(kruskal.Result[i]);

            Console.WriteLine("\nAlgorytm Prima");
            int start=0;
            Console.WriteLine("Podaj wierzchołek startowy dla algorytmu Prima");
            try
            {
                start = Convert.ToInt32(Console.ReadLine());
            }
            catch (Exception)
            {
                Console.WriteLine("Nie podales liczby!");
            }
            var prim = new Prim(edges);
            prim.Find(start);
            Console.WriteLine(String.Format("Rozpiętość {0:0.00}", prim.Span));
            for (int i = 0; i < prim.Result.Length; i++)
                Console.WriteLine(prim.Result[i]);

            Console.ReadKey();
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Grafy
{
    class Kruskal
    {
        public Edge[] Result { get; private set; }
        public double Span { get; private set; }
        public Edge[] edges { get; private set; }
        public int NumberOfPoints { get; private set; }

        public Kruskal(Edge [] edges)
        {
            this.edges = edges;
        }

        public void Find()
        {
            CountPoints();
            var sortEdges = edges.OrderBy(a => a.Value);
            //tablica do znaczenia zbiorów
            //ustawia tą samą wartość dla stworzonych zbiorów
            int[] sets = new int[NumberOfPoints];
            Result = new Edge[NumberOfPoints-1];
            int processedEdges = 0;
            foreach (var edge in sortEdges)
            {
                //Kończy gdy wszystkie punkty są wykorzystane
                if (processedEdges == NumberOfPoints - 1)
                    break;
                //Bierzemy pokolei krawędzie z posortowanej tablicy
                //Sprawdzamy najpierw czy punkt nie był wykorzystany lub czy może być wykorzystany jeszcze raz
                if (sets[edge.Point1] == 0 || sets[edge.Point1] != sets[edge.Point2])
                {
                    Result[processedEdges] = edge;
                    Span += edge.Value;
                    processedEdges++;
                    //wyrównuje wartości dla zbioru lub zbiorów jeśli jakiś punkt połączył zbiory
                    if (sets[edge.Point1] != 0 || sets[edge.Point2] != 0)
                    {
                        int set1 = sets[edge.Point1];
                        int set2 = sets[edge.Point2];

                        for (int i = 0; i < NumberOfPoints; i++)
                            if (sets[i] != 0 && (sets[i] == set1 || sets[i] == set2))
                                sets[i] = processedEdges;
                    }
                    //Wyrównuje wartości dla wykorzystanych punktów w tej iteracji
                    sets[edge.Point1] = processedEdges;
                    sets[edge.Point2] = processedEdges;
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

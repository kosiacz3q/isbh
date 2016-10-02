using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISBHHH
{
    public class Algorytm
    {

        public Kontener ko;

        private int TheBest;
        private Kontener Best;


        public Algorytm(Kontener kon)
        {
            ko = kon;
        }

        private Kontener MakeStep()
        {
            int min = ko.Test();
            Kontener best = ko;

            foreach (var x in ko.wartosci)
            {
                int number = ko.wartosci.IndexOf(x);
                for (int i = 0; i < ko.wartosci.Count; i++)
                {
                    if (i == number) continue;
                    Kontener temp = ko.insert(number, i);
                    if (temp.Test() <= min)
                    {
                        best = temp;
                        min = temp.Test();
                    }

                }
            }

            if (best.Test() == ko.Test())
            {
                if (Enumerable.SequenceEqual(best.wartosci, Best.wartosci))
                    Console.WriteLine("\npowtorzenie");

                Random rnd = new Random();
                int size = ko.wartosci.Count();

                swap(rnd.Next() % size, rnd.Next() % size);

                best = ko;
            }

            return best;
        }

        void swap(int from, int to)
        {
            string temp = ko.wartosci[from];
            ko.wartosci[from] = ko.wartosci[to];
            ko.wartosci[to] = temp;
        }


        public Kontener Run()
        {
            TheBest = ko.Test();
            Best = new Kontener(ko);
            for (int i = 0; i < 500; i++)
            {
                Kontener temp = MakeStep();

                int sw = ko.Test();

                if (temp.first != "")
                    ko = temp;
                int iiii = ko.Test();
                
                if (iiii < TheBest)
                {
                    TheBest = iiii;
                    Best = new Kontener(ko);
                    Console.WriteLine();
                    Console.WriteLine(i);
                    Console.WriteLine(TheBest);
                    Console.WriteLine((double)TheBest / 100.0);
                }
            }

            return Best;
        }

    }
}

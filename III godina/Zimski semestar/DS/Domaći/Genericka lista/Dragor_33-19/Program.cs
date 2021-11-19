using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GenerickaLista
{
    class Program
    {
        static void Main(string[] args)
        {
            // > Kamen

            Lista<Kamen> lista1 = new Lista<Kamen>(new Kamen(150));
            lista1.Add(new Kamen(100));
            lista1.Add(new Kamen(50));
            lista1.Add(new Kamen(200));
            lista1.Add(new Kamen(50));

            Console.WriteLine("== Kamen ==\n");
            Test(lista1);

            // > Kamen

            Lista<Pas> lista2 = new Lista<Pas>(new Pas("Zuca"));
            lista2.Add(new Pas("Plavko"));
            lista2.Add(new Pas("Av"));
            lista2.Add(new Pas("Roki"));
            lista2.Add(new Pas("Bak"));

            Console.WriteLine("\n== Pas ==\n");
            Test(lista2);

        }

        static void Test<T>(Lista<T> lista)
        {
            Console.WriteLine("~ for ~");
            for (int i = 0; i < lista.BrojElemenata; i++)
            {
                Console.WriteLine("> " + lista[i].Vrednost);
            }
            Console.WriteLine();

            Console.WriteLine("~ foreach ~");
            foreach (var item in lista.Prolaz())
            {
                Console.WriteLine("> " + item);
            }
            Console.WriteLine();

            
            lista.SelectionSort();

            Console.WriteLine("Sortirano:");
            foreach (var item in lista.Prolaz())
            {
                Console.WriteLine("> " + item);
            }
            Console.WriteLine();
        }
    }
}

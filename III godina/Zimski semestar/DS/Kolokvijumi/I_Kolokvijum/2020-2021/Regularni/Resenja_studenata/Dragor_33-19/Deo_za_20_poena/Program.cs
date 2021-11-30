using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zadatak
{
    class Program
    {
        static void Main(string[] args)
        {
            Skup<Vocka> a = new Skup<Vocka>();
            Skup<Vocka> b = new Skup<Vocka>();
            Skup<Vocka> c;
            Skup<Vocka> d;

            a.Dodaj(new Vocka("Jabuka", 200f));
            a.Dodaj(new Vocka("Jabuka", 150f));
            a.Dodaj(new Vocka("Kruska", 150f));
            a.Dodaj(new Vocka("Banana", 200f));
            a.Dodaj(new Vocka("Sljiva", 50f));

            b.Dodaj(new Vocka("Jabuka", 150f));
            b.Dodaj(new Vocka("Banana", 200f));
            b.Dodaj(new Vocka("Sljiva", 50f));

            d = a - b;
            d.Dodaj(new Vocka("Ananas", 500f));

            c = a + b + d;


            Console.WriteLine("\n- Skup A -");
            foreach (var item in a)
            {
                Console.WriteLine(item);
            }

            Console.WriteLine("\n- Skup B -");
            foreach (var item in b)
            {
                Console.WriteLine(item);
            }

            Console.WriteLine("\n- Skup C -");
            foreach (var item in c)
            {
                Console.WriteLine(item);
            }

            Console.WriteLine("\n- Skup D -");
            foreach (var item in d)
            {
                Console.WriteLine(item);
            }

            Console.WriteLine();
            Console.WriteLine("A je podskup od A: " + a.Podskup(a));
            Console.WriteLine("B je podskup od A: " + a.Podskup(b));
            Console.WriteLine("C je podskup od A: " + a.Podskup(c));
            Console.WriteLine("D je podskup od A: " + a.Podskup(d));

            Console.WriteLine();
            Console.WriteLine("A je jednako sa A: " + (a == a));
            Console.WriteLine("B je jednako sa A: " + (a == b));
            Console.WriteLine("C je jednako sa A: " + (a == c));
            Console.WriteLine("D je jednako sa A: " + (a == d));

        }
    }

    class Vocka : IJednakost<Vocka>
    {
        string naziv;
        float masa;

        public Vocka() 
        {
            naziv = "Jabuka";
            masa = 200f;
        }

        public Vocka(string naziv, float masa)
        {
            this.naziv = naziv;
            this.masa = masa;
        }

        public bool DaLiSuJednaki(Vocka v)
        {
            return naziv == v.naziv && masa == v.masa;
        }

        public override string ToString()
        {
            return naziv + " " + masa + "g";
        }
    }
}

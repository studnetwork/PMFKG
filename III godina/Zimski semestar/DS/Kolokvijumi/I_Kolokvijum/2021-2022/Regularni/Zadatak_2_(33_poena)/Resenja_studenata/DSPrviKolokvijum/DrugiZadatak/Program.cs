using System;
using System.Collections;
using System.Collections.Generic;

namespace DrugiZadatak
{
    class Program
    {
        public static void Main(string[] args)
        {
            Recnik<string, Student> recnik1 = new(), recnik2 = new();
            PromenaBrojaElemenataDelegat eventListener = (int n) =>
            {
                Console.WriteLine("Trenutni broj elemenata je " + n);
            };
            recnik1.PromenaBrojaElemenata+=eventListener;
            recnik2.PromenaBrojaElemenata += eventListener;

            recnik1.Dodaj("4/2020",new Student("Ime4",10, "4/2020", 6.5));
            recnik1.Dodaj("2/2020",new Student("Ime2", 12, "2/2020", 9.8));
            recnik1.Dodaj("1/2020",new Student("Ime1", 20, "1/2020", 9.99));
            recnik1.Dodaj("3/2020",new Student("Ime3", 20, "3/2020", 7.8));
            recnik1.Dodaj("33/2020", new Student("Ime33", 20,"33/2020", 7.8));

            recnik2.Dodaj("5/2020", new Student("Ime5", 20, "5/2020", 6.5));
            recnik2.Dodaj("6/2020", new Student("Ime6", 20, "6/2020", 6.8));
            recnik2.Dodaj("7/2020", new Student("Ime7", 20, "7/2020", 6.9));
            recnik2.Dodaj("8/2020", new Student("Ime8", 20, "8/2020", 7.8));
            recnik2.Dodaj("9/2020", new Student("Ime9", 20, "9/2020", 8.8));

            Console.WriteLine("recnik1[\"4/2020\"]=" + recnik1["4/2020"]);
            recnik1["4/2020"] = new Student("Ime4", 20, "4/2020", 8.5);
            Console.WriteLine("nakon promene recnik1[\"4/2020\"]=" + recnik1["4/2020"]);
            Console.WriteLine("--------------");
            foreach(var r in (recnik1 + recnik2))
            {
                Console.WriteLine(r);
            }

        }
    }
}

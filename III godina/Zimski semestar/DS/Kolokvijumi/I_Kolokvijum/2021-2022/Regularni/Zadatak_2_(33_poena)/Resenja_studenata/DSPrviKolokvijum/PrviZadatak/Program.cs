using System;
using System.Collections;
using System.Collections.Generic;

namespace PrviZadatak
{
    class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Started");
            GenerickaSortiranaLista<Student> lista1=new GenerickaSortiranaLista<Student>();
            GenerickaSortiranaLista<Student> lista2=new GenerickaSortiranaLista<Student>();

            ElementPostojiUListiDelegat<Student> eventListener = (Student student) =>
            {
                Console.WriteLine("Vec postoji student sa prosekom " + student.Prosek);
            };

            lista1.ElementPostojiUListi+=eventListener;
            lista2.ElementPostojiUListi += eventListener;
            lista1.Dodaj(new Student("Ime4", "Prezime4", "4/2020", 6.5));
            lista1.Dodaj(new Student("Ime2", "Prezime2", "2/2020", 9.8));
            lista1.Dodaj(new Student("Ime1", "Prezime1", "1/2020", 9.99));
            lista1.Dodaj(new Student("Ime3", "Prezime3", "3/2020", 7.8));
            lista1.Dodaj(new Student("Ime33", "Prezime33", "33/2020", 7.8));

            lista2.Dodaj(new Student("Ime5", "Prezime5", "5/2020", 6.5));
            lista2.Dodaj(new Student("Ime6", "Prezime6", "6/2020", 6.8));
            lista2.Dodaj(new Student("Ime7", "Prezime7", "7/2020", 6.9));
            lista2.Dodaj(new Student("Ime8", "Prezime8", "8/2020", 7.8));
            lista2.Dodaj(new Student("Ime9", "Prezime9", "9/2020", 8.8));
            Console.WriteLine("-----------\nLista1");
            foreach (var l in lista1)
            {
                Console.WriteLine(l);
            }
            Console.WriteLine("-----------\nLista2");
            foreach (var l in lista2)
            {
                Console.WriteLine(l);
            }
            Console.WriteLine("-----------");
            foreach (var l in lista1+lista2)
            {
                Console.WriteLine(l);
            }
            Console.WriteLine("------------\nPrimer primene -");
            foreach (var l in (lista1 - new Student("Ime1", "Prezime1", "1/2020", 9.99) ) )
            {
                Console.WriteLine(l);
            }
        }
    }
}
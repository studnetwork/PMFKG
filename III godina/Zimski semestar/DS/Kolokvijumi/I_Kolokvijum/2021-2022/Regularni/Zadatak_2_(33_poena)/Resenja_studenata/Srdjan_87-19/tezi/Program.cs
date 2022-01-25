
/*
    Podaci o rešenju
    ----------------
    Predmet: Dizajniranje softvera
    Program: 2019
    Školska godina: 2021-2022
    Kolokvijum: I Zadatak 2 (33p)
    Autor: Srđan Todorović
    
    Podaci o zadatku
    ----------------
    Predmet: Dizajniranje softvera
    Školska godina: 2021-2022
    Kolokvijum: I Zadatak 2 (33p)
    
    Prvo pojavljivanje
    ------------------
    Predmet: Vizuelno programiranje
    Školska godina: 2016-2017
    Kolokvijum: I
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tezi
{
    class Program
    {
        static void Main(string[] args)
        {
            var r1 = new Recnik<string, Student>();
            var r2 = new Recnik<string, Student>();

            Recnik<string, Student>.PromenaBrojaElemenataHandler eh;
            eh = delegate (int brEl) { Console.WriteLine("Tren broj: "+brEl); };

            r1.PromenaBrojaElemenata += eh;
            r2.PromenaBrojaElemenata += eh;


            r1.Dodaj("050598870405", new Student("Stud-A1", "1/2019", 4, 8.51f) );

            r1.Dodaj("050598870406", new Student("Stud-A2", "2/2019", 7, 8.99f));

            r1.Dodaj("050598870407", new Student("Stud-A3", "3/2019", 8, 8.71f));

            r1.Dodaj("050598870408", new Student("Stud-A4", "4/2019", 10, 6.71f));

            r1.Dodaj("050598870409", new Student("Stud-A5", "5/2019", 10, 9.5f));


            r2.Dodaj("150598870405", new Student("Stud-B1", "6/2019", 12, 8.8f));

            r2.Dodaj("150598870406", new Student("Stud-B2", "7/2019", 11, 7.75f));

            r2.Dodaj("150598870407", new Student("Stud-B3", "8/2019", 12, 10f));

            r2.Dodaj("150598870408", new Student("Stud-B4", "9/2019", 11, 6.7f));

            r2.Dodaj("150598870409", new Student("Stud-B5", "10/2019", 10, 9.42f));

            r1["050598870406"] = new Student("Stud-A2", "2/2019", 7, 9f);

            Console.WriteLine("Nakon promene: "+ r1["050598870406"]);

            var sviStudenti = r1 + r2;

            foreach(Student s in sviStudenti)
            {
                Console.WriteLine(s);
            }

            // nije trazeno
            List<string> kljucevi = sviStudenti;

            Console.WriteLine("Lista kljuceva: ");
            foreach (var item in kljucevi)
            {
                Console.WriteLine(item);
            }

            Console.ReadLine();
        }

        public class Student : IEquatable<Student>
        {
            public string indeks { get; set; }
            public string ime { get; set; }
            public int brojPolozenihIspita { get; set; }
            public float prosek { get; set; }

            public Student()
            {
            }

            public Student(string indeks, string ime, int brojPolozenihIspita, float prosek)
            {
                this.indeks = indeks;
                this.ime = ime;
                this.brojPolozenihIspita = brojPolozenihIspita;
                this.prosek = prosek;
            }

            public override string ToString()
            {
                return $"{indeks}, {ime}, {brojPolozenihIspita}, {prosek}";
            }

            public bool Equals(Student other)
            {
                if (indeks == other.indeks)
                    return true;

                return false;
            }
        }
    }
}

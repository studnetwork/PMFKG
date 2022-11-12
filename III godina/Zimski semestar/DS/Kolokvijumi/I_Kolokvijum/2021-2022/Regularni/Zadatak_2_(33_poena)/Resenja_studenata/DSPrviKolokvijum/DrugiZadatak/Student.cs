using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DrugiZadatak
{
    public class Student : IEquatable<Student>
    {
        public string Ime
        {
            get;
            private set;
        }
        public int BrojPolozenihIspita
        {
            get;
            private set;
        }
        public string Indeks
        {
            get;
            private set;
        }
        public double Prosek
        {
            get;
            private set;
        }

        public Student(string ime, int brojPolozenihIspita, string indeks, double prosek)
        {
            Ime = ime;
            BrojPolozenihIspita = brojPolozenihIspita;
            Indeks = indeks;
            Prosek = prosek;
        }

        public override string ToString()
        {
            return "( "+Indeks+", "+Ime+", "+BrojPolozenihIspita+", "+Prosek+" )";
        }

        public bool Equals(Student? other)
        {
            return this.Indeks == other?.Indeks;
        }
    }
}

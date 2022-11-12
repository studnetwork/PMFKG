using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PrviZadatak
{
    public class Student : IUporedivo<Student>
    {
        public string Ime
        {
            get;
            private set;
        }
        public string Prezime
        {
            get;
            private set;
        }
        public string BrojIndeksa
        {
            get;
            private set;
        }
        public double Prosek
        {
            get;
            private set;
        }

        public Student(string ime, string prezime, string brojIndeksa, double prosek)
        {
            Ime = ime;
            Prezime = prezime;
            BrojIndeksa = brojIndeksa;
            Prosek = prosek;
        }

        public int Uporedi(Student t)
        {
            if (Math.Abs(this.Prosek - t.Prosek) < 0.000001)
                return 0;
            if (this.Prosek > t.Prosek)
                return 1;
            return -1;
        }

        public override string ToString()
        {
            return "Student[Ime=" +Ime+" ,Prezime="+Prezime+" ,BrojIndeksa="+BrojIndeksa+" ,Prosek="+Prosek+" ]";
        }
    }
}

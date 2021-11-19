using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GenerickaLista
{
    class Pas : IUporediv<Pas>
    {
        string ime;

        public Pas(string ime)
        {
            this.ime = ime;
        }

        public int Uporedi(Pas pas)
        {
            int a = ime.Length;
            int b = pas.ime.Length;

            return a > b ? 1 : (a < b ? -1 : 0);
        }

        public override string ToString()
        {
            return "Pas " + ime;
        }
    }
}

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tezi
{
    public class Recnik<Kljuc, Vrednost> : IEnumerable
    where Kljuc : class, IEquatable<Kljuc>
    where Vrednost : class, IEquatable<Vrednost>
    {
        public delegate void PromenaBrojaElemenataHandler(int brEl);
        public event PromenaBrojaElemenataHandler PromenaBrojaElemenata;

        List<Par<Kljuc, Vrednost>> parovi;

        public Recnik()
        {
            this.parovi = new List<Par<Kljuc, Vrednost>>();
        }

        public void Dodaj(Kljuc kljuc, Vrednost vrednost)
        {
            for (int i = 0; i < parovi.Count; i++)
            {
                if(parovi[i].kljuc.Equals(kljuc))
                {
                    parovi[i].vrednost = vrednost;
                    return;
                }
            }

            var novPar = new Par<Kljuc, Vrednost>(kljuc, vrednost);

            parovi.Add(novPar);

            if (PromenaBrojaElemenata != null)
                PromenaBrojaElemenata(parovi.Count);
        }

        public IEnumerator GetEnumerator()
        {
            foreach (Par<Kljuc, Vrednost> par in parovi)
            {
                yield return par.vrednost;
            }
        }

        public Vrednost this[Kljuc kljuc]
        {
            get
            {
                var par = parovi.Find((Par<Kljuc, Vrednost> p) => p.kljuc.Equals(kljuc));

                if (par == null)
                    throw new KeyNotFoundException();

                return par.vrednost;
            }
            set
            {
                var par = parovi.Find((Par<Kljuc, Vrednost> p) => p.kljuc.Equals(kljuc));

                if (par == null)
                    throw new KeyNotFoundException();

                par.vrednost = value;
            }
        }

        public static Recnik<Kljuc, Vrednost> operator +(Recnik<Kljuc, Vrednost> r1, Recnik<Kljuc, Vrednost> r2)
        {
            var r = new Recnik<Kljuc, Vrednost>();

            foreach ( Par<Kljuc,Vrednost> par in r1.parovi)
            {
                r.Dodaj(par.kljuc, par.vrednost);
            }

            foreach (Par<Kljuc, Vrednost> par in r2.parovi)
            {
                r.Dodaj(par.kljuc, par.vrednost);
            }

            return r;
        }

        public static implicit operator List<Kljuc>(Recnik<Kljuc,Vrednost> recnik)
        {
            List<Kljuc> kljucevi = new List<Kljuc>();

            foreach(Par<Kljuc, Vrednost> par in recnik.parovi)
            {
                kljucevi.Add(par.kljuc);
            }

            return kljucevi;
        }
    }
}

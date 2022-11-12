using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DrugiZadatak
{
    public delegate void PromenaBrojaElemenataDelegat(int n);
    public class Recnik<Kljuc,Vrednost>:IEnumerable where Kljuc : class, IEquatable<Kljuc> where Vrednost : class, IEquatable<Vrednost>
    {
        private List<Par<Kljuc, Vrednost>> parovi;
        public event PromenaBrojaElemenataDelegat PromenaBrojaElemenata;
        public Recnik()
        {
            parovi = new();
        }
        public void Dodaj(Kljuc kljuc, Vrednost vrednost)
        {
            int indeks = parovi.FindIndex((Par<Kljuc, Vrednost> par) => {
                return kljuc.Equals(par.kljuc);
            });
            if (indeks == -1)
            {
                parovi.Add(new Par<Kljuc, Vrednost>(kljuc, vrednost));
                PromenaBrojaElemenata?.Invoke(parovi.Count);
            }
            else
            {
                parovi[indeks].vredost = vrednost;
            }
        }

        public Vrednost this[Kljuc kljuc]
        {
            get
            {
                int indeks = parovi.FindIndex((Par<Kljuc, Vrednost> par) => {
                    return kljuc.Equals(par.kljuc);
                });
                if (indeks == -1)
                    return null;
                return parovi[indeks].vredost;
            }
            set
            {
                Dodaj(kljuc, value);
            }
        }

        private IEnumerable ProdjiPoParovima()
        {
            foreach(var par in parovi)
            {
                yield return par;
            }
        }
        public IEnumerator GetEnumerator()
        {
            return ProdjiPoParovima().GetEnumerator();
        }

        public static Recnik<Kljuc,Vrednost> operator +(Recnik<Kljuc,Vrednost> recnik1,Recnik<Kljuc,Vrednost> recnik2)
        {
            Recnik<Kljuc, Vrednost> rezlutat = new();
            foreach(var par in recnik1.parovi)
            {
                rezlutat.Dodaj(par.kljuc, par.vredost);
            }
            foreach (var par in recnik2.parovi)
            {
                rezlutat.Dodaj(par.kljuc, par.vredost);
            }
            return rezlutat;
        }
        public static implicit operator List<Kljuc>(Recnik<Kljuc,Vrednost> recnik)
        {
            List<Kljuc> lista = new();
            foreach(var par in recnik.parovi)
            {
                lista.Add(par.kljuc);
            }
            return lista;
        }
    }
}

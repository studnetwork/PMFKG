using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2018_2019_I_kol
{
    public class DvostrukaLista<T> : IEnumerable where T : class, IUporedivo<T>, new()
    {
        class Element<T>
        {
            public T Val { get; set; }
            public Element<T> Sledeci { get; set; }
            public Element<T> Prethodni { get; set; }

            public Element(T val)
            {
                Val = val;
            }
        }

        public delegate bool WhereDelegat(T val);

        public delegate void FunkcijaDodavanja(T val);
        public event FunkcijaDodavanja DodatJeNoviElement;

        Element<T> glava, rep;
        public int BrojElemenata { get; set; }
        
        private void ProveriOpseg(int redniBroj)
        {
            if (redniBroj < 0 || redniBroj >= BrojElemenata)
                throw new IndexOutOfRangeException();
        }

        public void Dodaj( T val )
        {
            Element<T> noviElement = new Element<T>(val);
            if( glava == null )
            {
                glava = noviElement;
                rep = noviElement;
            }
            // proveri da li je nova vrednost ima najvisu poziciju u neopadaajucem poretku
            else if( 0 <= val.Uporedi(rep.Val) )
            {
                rep.Sledeci = noviElement;
                noviElement.Prethodni = rep;
                rep = noviElement;
            }
            else
            {
                Element<T> trenutni = glava;
                while( /*trenutni != null 
                    &&*/ 0 <= val.Uporedi( trenutni.Val ) )
                {
                    trenutni = trenutni.Sledeci;
                }

                // proveri da li je glava
                if( trenutni.Prethodni == null )
                {
                    noviElement.Sledeci = trenutni;
                    trenutni.Prethodni = noviElement;
                    glava = noviElement;
                }
                else
                {
                    noviElement.Prethodni = trenutni.Prethodni;
                    noviElement.Sledeci = trenutni;

                    trenutni.Prethodni.Sledeci = noviElement;
                    trenutni.Prethodni = noviElement;
                }
            }

            BrojElemenata++;

            if( DodatJeNoviElement != null )
                DodatJeNoviElement(val);
        }

        public T this[int redniBroj]
        {
            get
            {
                ProveriOpseg(redniBroj);

                Element<T> trenutni = glava;
                int i = 0;

                while (/*trenutni != null &&*/ i++ < redniBroj)
                    trenutni = trenutni.Sledeci;

                return trenutni.Val;

            }
            private set
            {
                ProveriOpseg(redniBroj);

                Element<T> trenutni = glava;
                int i = 0;

                while (/*trenutni != null &&*/ i++ < redniBroj)
                    trenutni = trenutni.Sledeci;

                trenutni.Val = value;
            }
        }
        public IEnumerator GetEnumerator()
        {
            Element<T> trenutni = glava;

            while (trenutni != null)
            {
                yield return trenutni.Val;
                trenutni = trenutni.Sledeci;
            }
        }

        public IEnumerable ObrnutiPoredak()
        {
            Element<T> trenutni = rep;

            while (trenutni != null)
            {
                yield return trenutni.Val;
                trenutni = trenutni.Prethodni;
            }
        }

        public static DvostrukaLista<T> operator +(DvostrukaLista<T> l1, DvostrukaLista<T> l2)
        {
            DvostrukaLista<T> novaLista = new DvostrukaLista<T>();

            foreach (T element in l1)
            {
                novaLista.Dodaj(element);
            }

            foreach ( T element in l2)
            {
                novaLista.Dodaj(element);
            }

            return novaLista;
        }

        public static explicit operator List<T>(DvostrukaLista<T> dl)
        {
            List<T> lista = new List<T>();

            foreach( T element in dl.ObrnutiPoredak() )
            {
                lista.Add(element);
            }

            return lista;
        }

        public IEnumerable Where( WhereDelegat filter )
        {
            foreach (T element in this)
            {
                if (filter(element))
                    yield return element;
            }
        }
    }
}

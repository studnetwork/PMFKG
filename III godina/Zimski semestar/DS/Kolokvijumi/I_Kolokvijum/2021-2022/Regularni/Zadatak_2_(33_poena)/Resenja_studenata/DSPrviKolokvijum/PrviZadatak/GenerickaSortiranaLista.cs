using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PrviZadatak
{
    public delegate void ElementPostojiUListiDelegat<T>(T n);
    // 2.
    public class GenerickaSortiranaLista<T>:IEnumerable where T: class, IUporedivo<T> // 2.a
    {
        private ElementListe<T> glava;

        public GenerickaSortiranaLista()
        {
            glava = null;
        }

        // 2.b
        public T this[int indeks]
        {
            get
            {
                ElementListe<T> pom;
                int i;
                for (pom = glava, i = 0; pom != null && i < indeks; i++, pom = pom.sledeci) { }
                if (pom == null)
                    return null;
                    //throw new IndexOutOfRangeException();
                return pom.vrednost;
            }
            private set { }
        }

        // 2.c
        public T VrednostGlave
        {
            get
            {
                return glava?.vrednost;
            }
            private set { }
        }

        // 2.d
        public event ElementPostojiUListiDelegat<T> ElementPostojiUListi;

        // 2.e
        public void Dodaj(T vrednost)
        {
            ElementListe<T> novi = new ElementListe<T>(vrednost);
            ElementListe<T> pom=glava, prethodni=glava;
            if (glava == null)
            {
                glava = novi;
                return;
            }
            int uslov = glava.vrednost.Uporedi(vrednost);
            if (uslov <= 0)
            {
                if (uslov == 0)
                    ElementPostojiUListi?.Invoke(vrednost);
                novi.sledeci = glava;
                glava = novi;
                return;
            }
            for (; pom != null && (uslov=pom.vrednost.Uporedi(vrednost)) > 0; prethodni = pom,pom=pom.sledeci) { }
            if(uslov==0)
                ElementPostojiUListi?.Invoke(vrednost);
            novi.sledeci = prethodni.sledeci;
            prethodni.sledeci = novi;
        }

        private IEnumerable DajEnumerator()
        {
            ElementListe<T> pom;
            for(pom=glava;pom!=null;pom=pom.sledeci)
            {
                yield return pom.vrednost;
            }
        }
        // 2.f
        public IEnumerator GetEnumerator()
        {
            return this.DajEnumerator().GetEnumerator();
        }

        // 2.g
        public static List<T> operator +(GenerickaSortiranaLista<T> lista1,GenerickaSortiranaLista<T> lista2)
        {
            GenerickaSortiranaLista<T> novaLista=new GenerickaSortiranaLista<T>();
            foreach(T l in lista1)
            {
                novaLista.Dodaj(l);
            }
            foreach(T l in lista2)
            {
                novaLista.Dodaj(l);
            }
            return (List<T>)novaLista;
        }
        // 2.i
        public static GenerickaSortiranaLista<T> operator -(GenerickaSortiranaLista<T> lista, T elementZaBrisanje)
        {
            GenerickaSortiranaLista<T> novaLista = new GenerickaSortiranaLista<T>();
            foreach (T l in lista)
            {
                if(l.Uporedi(elementZaBrisanje)!=0)
                    novaLista.Dodaj(l);
            }
            return novaLista;
        }

        // 2.h
        public static explicit operator List<T>(GenerickaSortiranaLista<T> lista)
        {
            List<T> rezlutat = new List<T>();
            foreach(T l in lista)
            {
                rezlutat.Add(l);
            }
            return rezlutat;
        }
        public static explicit operator GenerickaSortiranaLista<T>(List<T> lista)
        {
            GenerickaSortiranaLista<T> rezlutat = new GenerickaSortiranaLista<T>();
            foreach (T l in lista)
            {
                rezlutat.Dodaj(l);
            }
            return rezlutat;
        }
    }
}

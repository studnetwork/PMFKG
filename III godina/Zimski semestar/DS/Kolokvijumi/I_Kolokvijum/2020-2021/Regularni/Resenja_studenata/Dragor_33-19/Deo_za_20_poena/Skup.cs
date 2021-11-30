using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zadatak
{
    delegate void DelegatVoidT<T>(T x);

    class Skup<T> : IEnumerable<T> where T: class, IJednakost<T>, new()
    {
        public event DelegatVoidT<T> ElementJeDuplikat;

        List<T> objekti;

        public int BrojElemenata { get => objekti.Count; }

        public Skup()
        {
            objekti = new List<T>();
        }

        public void Dodaj(T novi)
        {
            foreach (var item in objekti)
            {
                if (novi.DaLiSuJednaki(item))
                {
                    ElementJeDuplikat?.Invoke(novi);
                    return;
                }
            }

            objekti.Add(novi);
        }

        public void Izbaci(T element)
        {
            for (int i = 0; i < objekti.Count; i++)
            {
                if (element.DaLiSuJednaki(objekti[i]))
                {
                    objekti.RemoveAt(i);
                    return;
                }
            }

            throw new Exception("Element ne postoji!");
        }

        public bool Podskup(Skup<T> skup)
        {
            foreach (var aItem in skup)
            {
                bool postoji = false;

                foreach (var bItem in this)
                {
                    if (aItem.DaLiSuJednaki(bItem))
                    {
                        postoji = true;
                        break;
                    }
                }

                if (!postoji)
                {
                    return false;
                }
            }

            return true;
        }

        public static Skup<T> operator +(Skup<T> a, Skup<T> b)
        {
            Skup<T> c = new Skup<T>();

            foreach (var item in a)
            {
                c.Dodaj(item);
            }

            foreach (var item in b)
            {
                c.Dodaj(item);
            }

            return c;
        }

        public static Skup<T> operator -(Skup<T> a, Skup<T> b)
        {
            Skup<T> c = new Skup<T>();

            foreach (var item in a)
            {
                c.Dodaj(item);
            }

            foreach (var item in b)
            {
                try
                {
                    c.Izbaci(item);
                }
                catch(Exception) { }
            }

            return c;
        }

        public static bool operator ==(Skup<T> a, Skup<T> b)
        {
            // return b.Podskup(a) && a.Podskup(b);
            return a.BrojElemenata == b.BrojElemenata && a.Podskup(b);
        }

        public static bool operator !=(Skup<T> a, Skup<T> b)
        {
            return !(a == b);
        }

        public IEnumerator<T> GetEnumerator()
        {
            foreach (var item in objekti)
            {
                yield return item;
            }
        }

        public static explicit operator T[](Skup<T> skup)
        {
            T[] niz = new T[skup.BrojElemenata];

            int i = 0;
            foreach (var item in skup)
            {
                niz[i++] = item;
            }

            return niz;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            foreach (var item in objekti)
            {
                yield return item;
            }
        }
    }
}

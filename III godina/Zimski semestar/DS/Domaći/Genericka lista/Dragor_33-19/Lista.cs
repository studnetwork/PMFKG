using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GenerickaLista
{
    class Lista<T>
    {
        // > Attributes
        Element<T> glava;

        // > Properties
        public int BrojElemenata
        { 
            get
            {
                int n = 0;

                Element<T> p = glava;
                while (p != null)
                {
                    n++;
                    p = p.Sledeci;
                }

                return n;
            }
        }

        // > Indexers
        public Element<T> this[int index]
        {
            get
            {
                int i = 0;

                if (glava == null)
                    throw new Exception("Lista je prazna!");

                Element<T> p = glava;
                while (p.PostojiSledeci && i < index)
                {
                    i++;
                    p = p.Sledeci;
                }

                if (i == index)
                    return p;
                else
                    throw new Exception("Lista je prazna!");
            }
        }

        // Constructors
        public Lista(T glava)
        {
            this.glava = new Element<T>(glava);
        }

        // > Methods
        public void Add(T vrednost)
        {
            if (glava == null)
            {
                glava = new Element<T>(vrednost);
                return;
            }

            Element<T> p = glava;
            while (p.PostojiSledeci)
                p = p.Sledeci;

            p.Sledeci = new Element<T>(vrednost);
        }
        public IEnumerable<T> Prolaz()
        {
            Element<T> p = glava;
            while (p != null)
            {
                yield return p.Vrednost;
                p = p.Sledeci;
            }
        }

        public void BubbleSort()
        {
            for (int k = BrojElemenata; k >= 1; k--)
            {
                for (int i = 0; i < k - 1; i++)
                {
                    int j = i + 1;

                    if (this[i] > this[j])
                    {
                        Element<T> a = this[i];
                        Element<T> b = this[j];
                        Element<T> bNext = (j < BrojElemenata - 1) ? this[j + 1] : null;

                        a.Sledeci = bNext;

                        if (i == 0)
                            glava = b;
                        else
                            this[i - 1].Sledeci = b;  // aPrev.Sledeci = b

                        b.Sledeci = a;
                    }
                }
            }
        }

        public void SelectionSort()
        {
            for (int i = 0; i < BrojElemenata - 1; i++)
            {
                for (int j = i + 1; j < BrojElemenata; j++)
                {
                    if (this[i] > this[j])
                    {
                        Element<T> a = this[i];
                        Element<T> aNext = this[i + 1];
                        Element<T> b = this[j];
                        Element<T> bNext = (j < BrojElemenata - 1) ? this[j + 1] : null;
                        Element<T> bPrev = this[j - 1];


                        if (i == 0)
                            glava = b;
                        else {
                            Element<T> aPrev = this[i - 1];
                            aPrev.Sledeci = b;
                        }

                        a.Sledeci = bNext;

                        if (i + 1 == j)
                        {
                            b.Sledeci = a;
                        }
                        else
                        {
                            b.Sledeci = aNext;
                            bPrev.Sledeci = a;
                        }
                    }
                }
            }
        }
    }
}

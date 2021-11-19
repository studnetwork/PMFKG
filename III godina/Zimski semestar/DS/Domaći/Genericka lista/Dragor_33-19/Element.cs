using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GenerickaLista
{
    class Element<T>
    {
        // > Attributes
        T vrednost;
        Element<T> sledeci;

        // > Properties
        public T Vrednost { get => vrednost; }
        public Element<T> Sledeci { get => sledeci; set => sledeci = value; }
        public bool PostojiSledeci { get => sledeci != null; }

        // > Constructors
        public Element() : this(default(T)) { }

        public Element(T vrednost)
        {
            this.vrednost = vrednost;
            this.sledeci = null;
        }

        public static bool operator <(Element<T> a, Element<T> b)
        {
            if (!(a.vrednost is IUporediv<T> && b.vrednost is IUporediv<T>))
                throw new Exception("Neuporedivi tipovi!");

            return (a.vrednost as IUporediv<T>).Uporedi(b.vrednost) == -1;
        }

        public static bool operator >(Element<T> a, Element<T> b)
        {
            if (!(a.vrednost is IUporediv<T> && b.vrednost is IUporediv<T>))
                throw new Exception("Neuporedivi tipovi!");

            return (a.vrednost as IUporediv<T>).Uporedi(b.vrednost) == 1;
        }
    }
}

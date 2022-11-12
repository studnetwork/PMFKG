using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PrviZadatak
{
    internal class ElementListe<T>
    {
        public T vrednost
        {
            get;
            private set;
        }
        public ElementListe<T> sledeci;

        public ElementListe(T vrednost)
        {
            this.vrednost = vrednost;
            this.sledeci = null;
        }
    }
}

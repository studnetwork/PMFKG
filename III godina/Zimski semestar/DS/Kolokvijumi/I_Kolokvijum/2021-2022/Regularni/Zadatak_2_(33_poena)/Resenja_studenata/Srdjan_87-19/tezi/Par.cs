using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tezi
{
    class Par<Kljuc,Vrednost>
    where Kljuc : class, IEquatable<Kljuc>
    where Vrednost : class, IEquatable<Vrednost>
    {
        public Kljuc kljuc { get; set; }
        public Vrednost vrednost { get; set; }

        public Par(Kljuc kljuc, Vrednost vrednost)
        {
            this.kljuc = kljuc;
            this.vrednost = vrednost;
        }

        public override string ToString()
        {
            return kljuc.ToString() + vrednost.ToString();
        }
    }
}

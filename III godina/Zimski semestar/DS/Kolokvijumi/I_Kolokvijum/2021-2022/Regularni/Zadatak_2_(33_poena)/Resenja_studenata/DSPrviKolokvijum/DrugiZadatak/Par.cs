using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DrugiZadatak
{
    public class Par<Kljuc,Vrednost> where Kljuc: class,IEquatable<Kljuc> where Vrednost:class,IEquatable<Vrednost>
    {
        public Kljuc kljuc;
        public Vrednost vredost;

        public Par(Kljuc kljuc, Vrednost vredost)
        {
            this.kljuc = kljuc;
            this.vredost = vredost;
        }
        public override string ToString()
        {
            return "( " + kljuc.ToString() + " , " + vredost.ToString() + " )";
        }
    }
}

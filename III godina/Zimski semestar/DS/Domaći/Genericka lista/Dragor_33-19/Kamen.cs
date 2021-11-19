using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GenerickaLista
{
    class Kamen : IUporediv<Kamen>
    {
        float masa;
        public Kamen(float masa)
        {
            this.masa = masa;
        }

        public int Uporedi(Kamen kamen) => masa > kamen.masa ? 1 : (masa < kamen.masa ? -1 : 0);

        public override string ToString()
        {
            return "Kamen od " + masa + " grama";
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GenerickaLista
{
    interface IUporediv<T>
    {
        int Uporedi(T a);
    }
}

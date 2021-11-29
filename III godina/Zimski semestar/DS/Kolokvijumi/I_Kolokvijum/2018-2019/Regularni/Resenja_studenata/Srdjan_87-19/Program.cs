using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2018_2019_I_kol
{
    
    // Predmet: Dizajniranje softvera
    // Program: 2019
    // Autor : Srđan Todorović
    
    // O zadatku
    //
    // Predmet: Vizuelno programiranje
    // Kolokvijum: I
    // Školska godina: 2018-2019
    
    
    class Program
    {
        static void Main(string[] args)
        {
            DvostrukaLista<Teniser> muskaKonkurencija = new DvostrukaLista<Teniser>();
            DvostrukaLista<Teniser> zenskaKonkurencija = new DvostrukaLista<Teniser>();

            DvostrukaLista<Teniser>.FunkcijaDodavanja fd = delegate (Teniser t)
            {
                Console.WriteLine(t);
            };

            muskaKonkurencija.DodatJeNoviElement += fd;
            zenskaKonkurencija.DodatJeNoviElement += fd;

            muskaKonkurencija.Dodaj(new Teniser("Novak", "Djokovic", 15000));
            muskaKonkurencija.Dodaj(new Teniser("Petar", "Petrovic", 1001));
            muskaKonkurencija.Dodaj(new Teniser("Arsenije", "Arsenijevic", 8002));

            zenskaKonkurencija.Dodaj(new Teniser("Milica", "Milicevic", 7003));
            zenskaKonkurencija.Dodaj(new Teniser("Teodora", "Teodorovic", 5004));
            zenskaKonkurencija.Dodaj(new Teniser("Marijana", "Marijanovic", 6005));
            zenskaKonkurencija.Dodaj(new Teniser("Branka", "Brankovic", 10006));
            zenskaKonkurencija.Dodaj(new Teniser("Sladja", "Sladjanovic", 3007));
            zenskaKonkurencija.Dodaj(new Teniser("Aleksandra", "Aleksandric", 2007));

            muskaKonkurencija.Dodaj(new Teniser("Milos", "Milosevic", 6008));
            muskaKonkurencija.Dodaj(new Teniser("Marko", "Markovic", 9009));
            muskaKonkurencija.Dodaj(new Teniser("Aleksej", "Pavlov", 9009));

            Console.WriteLine("\nTeniseri muske konkurencije u neopadajucem redosledu: ");
            foreach( Teniser teniser in muskaKonkurencija )
            {
                Console.WriteLine(teniser);
            }

            Console.WriteLine("\nTeniseri zenske konkurencije u nerastucem redosledu: ");
            foreach (Teniser teniser in zenskaKonkurencija.ObrnutiPoredak())
            {
                Console.WriteLine(teniser);
            }

            DvostrukaLista<Teniser> sviTeniseri = muskaKonkurencija + zenskaKonkurencija;

            Console.WriteLine("\nSvi teniseri u neopadajucem redosledu: ");
            foreach (Teniser teniser in sviTeniseri)
            {
                Console.WriteLine(teniser);
            }


            IEnumerable pocinjeSaAiViseOd500 = sviTeniseri.Where((Teniser t) => t.Ime.StartsWith("A") && t.ATPpoeni > 5000);

            Console.WriteLine("\nSvi teniseri cije ime pocinje sa \"A\" i koji imaju vise od 5000 APT poena: ");
            foreach (Teniser teniser in pocinjeSaAiViseOd500)
            {
                Console.WriteLine(teniser);
            }

            IEnumerable paranATP = sviTeniseri.Where((Teniser t) => t.ATPpoeni % 2 == 0);

            Console.WriteLine("\nSvi teniseri koji imaju paran broj ATP poena: ");
            foreach (Teniser teniser in paranATP)
            {
                Console.WriteLine(teniser);
            }

            // dodatno, nije trazeno u zadatku; testiranje indeksera
            Console.WriteLine("\nDrugi teniser na listi tenisera sa najmanjim brojem ATP poena: ");
            Console.WriteLine(sviTeniseri[1]);

            // pauziranje pred kraj programa
            Console.ReadKey();
        }
    }

    class Teniser : IUporedivo<Teniser>
    {
        public string Ime { get; set; }
        public string Prezime { get; set; }
        public int ATPpoeni { get; set; }

        public Teniser()
        {
        }

        public Teniser(string ime, string prezime, int ATPpoeni)
        {
            Ime = ime;
            Prezime = prezime;
            this.ATPpoeni = ATPpoeni;
        }

        public override string ToString()
        {
            return String.Format("Teniser: {0} {1} {2}", Ime, Prezime, ATPpoeni);
        }

        public int Uporedi(Teniser val)
        {
            if (ATPpoeni == val.ATPpoeni)
                return 0;

            if (ATPpoeni > val.ATPpoeni)
                return 1;

            return -1;
        }
    }
}

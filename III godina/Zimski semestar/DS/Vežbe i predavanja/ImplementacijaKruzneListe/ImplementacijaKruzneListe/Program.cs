using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImplementacijaKruzneListe
{
    class Program
    {
        // Predmet: Dizajniranje softvera
        // Program: 2019
        // Autor : Srđan Todorović

        // O zadatku:
        // Modifikacija kolokvijuma; implementira se jednostruka kruzna lista umesto dvostruke (regularne) liste
        //
        // Predmet: Vizuelno programiranje
        // Kolokvijum: I
        // Školska godina: 2018-2019

        static void Main(string[] args)
        {
            KruznaJednostrukaLista<Teniser> muskaKonkurencija = new KruznaJednostrukaLista<Teniser>();
            KruznaJednostrukaLista<Teniser> zenskaKonkurencija = new KruznaJednostrukaLista<Teniser>();

            KruznaJednostrukaLista<Teniser>.Funkcija fd = delegate (Teniser t)
            {
                Console.WriteLine( "Dodat " + t);
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
            foreach (Teniser teniser in muskaKonkurencija)
            {
                Console.WriteLine(teniser);
            }

            Console.WriteLine("\nTeniseri zenske konkurencije u nerastucem redosledu: ");
            foreach (Teniser teniser in zenskaKonkurencija.ObrnutiPoredak())
            {
                Console.WriteLine(teniser);
            }

            KruznaJednostrukaLista<Teniser> sviTeniseri = muskaKonkurencija + zenskaKonkurencija;

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
            if (ATPpoeni < val.ATPpoeni)
                return -1;

            if (ATPpoeni > val.ATPpoeni)
                return 1;

            return 0;
        }
    }


    delegate bool WhereDelegat<Tip>(Tip x) where Tip : class, IUporedivo<Tip>, new();

    interface IUporedivo<T>
    {
        /// <summary>
        /// Uporedjuje dati element sa prosledjenim tako sto odredjuje ko ima manju poziciju u neopadajucem poretku
        /// </summary>
        /// <returns>
        ///     Vraca -1 ukoliko element dolazi pre u neopadajucem poretku,
        ///     0 ukoliko imaju iste vrednosti ili +1 ukoliko prosledjeni
        ///     element dolazi pre u neopadajucem poretku
        /// </returns>
        int Uporedi(T x);
    }

    class KruznaJednostrukaLista<T> : IEnumerable where T : class, IUporedivo<T>, new()
    {
        public delegate void Funkcija(T x);
        public event Funkcija DodatJeNoviElement;
        class Element<T>
        {
            public T Val { get; set; }
            public Element<T> Sledeci { get; set; }
        }


        Element<T> pristupniElement;
        Element<T> prethodnikPristupnog;

        public int BrojElemenata { get; private set; }

        void ProveriIspravnostIndeksa(int i)
        {
            if (i < 0 || i >= BrojElemenata)
                throw new IndexOutOfRangeException("Indeks je izvan opsega. Njegova vrednost je: " + i);
        }

        // odredjuje se relativno, u odnosu na pristupni
        public T this[int redniBroj]
        {
            get
            {
                ProveriIspravnostIndeksa(redniBroj);

                int i = 0;
                Element<T> trenutni = pristupniElement;
                while ( i++ < redniBroj ) // zbog provere ispravnosti indeksa nema potrebe za drugim uslovom
                    trenutni = trenutni.Sledeci;

                return trenutni.Val;
            }

            private set
            {
                ProveriIspravnostIndeksa(redniBroj);

                int i = 0;
                Element<T> trenutni = pristupniElement;
                while (i++ < redniBroj) // zbog provere ispravnosti indeksa nema potrebe za drugim uslovom
                    trenutni = trenutni.Sledeci;

                trenutni.Val = value;
            }
        }

        // dodaje element u sortiranu kruznu listu, bez narusavanja neopadajuceg poretka
        public void Dodaj( T vrednostNovogElementa )
        {
            // iako ne postoji parametarizovan konstruktor moguce je inicijalizovati objekat
            // pomocu compound inicijalizatora
            Element<T> noviElement = new Element<T>() { Val = vrednostNovogElementa };

            if (pristupniElement == null)
            {
                pristupniElement = noviElement;
                prethodnikPristupnog = noviElement;

                // povezivanje; vrsi se kako bi lista bila kruzna
                pristupniElement.Sledeci = pristupniElement;
            }
            // proveri da li novi treba da bude "poslednji"; uradjeno radi optimizacije koda
            else if (-1 != vrednostNovogElementa.Uporedi(prethodnikPristupnog.Val))
            {
                noviElement.Sledeci = pristupniElement;

                prethodnikPristupnog.Sledeci = noviElement;
                prethodnikPristupnog = noviElement;
            }
            else
            {
                Element<T> prethodni = pristupniElement;
                Element<T> trenutni = pristupniElement.Sledeci;

                // dodavanje pre prvog, u slucaju da je data vrednost manja od svih ostalih
                // u listi
                if ( -1 == vrednostNovogElementa.Uporedi(pristupniElement.Val))
                {
                    pristupniElement = noviElement;
                }
                else
                {

                    // prolazi kroz listu sve dok ne naidje na element koji ide nakon njega
                    while (trenutni != pristupniElement && -1 != vrednostNovogElementa.Uporedi(trenutni.Val))
                    {
                        prethodni = trenutni;
                        trenutni = trenutni.Sledeci;
                    }
                }
            
            

                noviElement.Sledeci = trenutni;
                prethodni.Sledeci = noviElement;

            }


            BrojElemenata++;

            if (DodatJeNoviElement != null)
                DodatJeNoviElement(vrednostNovogElementa);
        }

        public IEnumerator GetEnumerator()
        {
            yield return pristupniElement.Val;

            Element<T> trenutni = pristupniElement.Sledeci;
            
            while( trenutni != pristupniElement )
            {
                yield return trenutni.Val;
                trenutni = trenutni.Sledeci;
            }
        }

        public IEnumerable ObrnutiPoredak()
        {
            yield return prethodnikPristupnog.Val;

            Element<T> poslednjiElementIteracije = prethodnikPristupnog;

            Element<T> prethodni = prethodnikPristupnog;
            Element<T> trenutni = pristupniElement;

            while (poslednjiElementIteracije != pristupniElement)
            {
                // prolazi sve dok ne dodje do nekog koji je vec vracen
                while (trenutni != poslednjiElementIteracije)
                {
                    prethodni = trenutni;
                    trenutni = trenutni.Sledeci;
                }

                yield return prethodni.Val;
                // smanjenje krajnje granice za 1 element
                poslednjiElementIteracije = prethodni;
                
                // vracanje na pristupni radi zapocinjanja nove iteracije
                trenutni = pristupniElement;
                prethodni = prethodnikPristupnog;
            }
        }

        public static KruznaJednostrukaLista<T> operator +(KruznaJednostrukaLista<T> a, KruznaJednostrukaLista<T> b)
        {
            KruznaJednostrukaLista<T> objedinjenaLista = new KruznaJednostrukaLista<T>();

            foreach (T vrednost in a)
                objedinjenaLista.Dodaj(vrednost);
            
            foreach (T vrednost in b)
                objedinjenaLista.Dodaj(vrednost);

            return objedinjenaLista;
        }


        public static explicit operator List<T>( KruznaJednostrukaLista<T> kjl )
        {
            List<T> lista = new List<T>();

            foreach (T vrednost in kjl)
                lista.Insert(0, vrednost);

            /* druga varijantas
             foreach( T vrednost in kjl.ObrnutiPoredak() )
                lista.Add(vrednost);
            */

            return lista;
        }

        public KruznaJednostrukaLista<T> Where( WhereDelegat<T> filter )
        {
            KruznaJednostrukaLista<T> rezultat = new KruznaJednostrukaLista<T>();

            foreach( T vrednost in this )
            {
                if (filter(vrednost))
                    rezultat.Dodaj(vrednost);
            }

            return rezultat;
        }
    }
}

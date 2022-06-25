object Zadatak2 {
    def lokalniMaksimum(brojevi: List[Int]): List[Int] = {
        brojevi match {
            case x::y::z::ts => 
                if(x < y && z < y) {
                    y :: lokalniMaksimum(z::ts)
                }
                else {
                    lokalniMaksimum(y::z::ts)
                }
            case _ => List()
        }
    }

    def main(args: Array[String]): Unit = {
        println("Pronalazenje lokalnih maksimuma u datom nizu brojeva\n")

        println("Koliko brojeva cini dati niz? ")
        val n: Int = readInt() // deprecated; koristi se zbog jednostavnost

        var brojevi: List[Int] = List()

        println("\nUnesite brojeve")
        for(i <- 1 to n) {
            print(s"\t$i. broj: ")
            brojevi = brojevi ++ List(readInt())
            // moze i sa :+ da se doda
        }

        val lmax = lokalniMaksimum(brojevi)
        println(s"Lokalni maksimum za brojeve $brojevi je $lmax")
    }
}

/* Test primeri:
    lokalniMaksimum [2,9,5,6,1]
        [9,6]

    lokalniMaksimum [2,3,4,1,5]
        [4]

    lokalniMaksimum [1,2,3,4,5]
        []
*/
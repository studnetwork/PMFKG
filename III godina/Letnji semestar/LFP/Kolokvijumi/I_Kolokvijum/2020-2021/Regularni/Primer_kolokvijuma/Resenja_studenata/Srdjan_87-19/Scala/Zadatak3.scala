object Zadatak3 {
    def main(args: Array[String]): Unit = {
        val lista: List[Int] = List(0,1,2,7,8,5,7,8,1,2,9)
        nacrtajHistogram(lista)
    }

    def nacrtajHistogram(cifre: List[Int]) = {
        def vratiZvezdice(brojZvezdica: Int): String = {
            if(brojZvezdica < 0)
                throw new Error("Broj zvezdica ne moze biti negativan broj")
            
            var zvezdice: String = ""

            if(brojZvezdica != 0)
                for(i <- 1 to brojZvezdica)
                    zvezdice = zvezdice + "*"

            zvezdice
        }
    
        for(i <- 0 to 9) {

            val brojZvezdica: Int = cifre.count(x => x==i)
            println(s"$i:${vratiZvezdice(brojZvezdica)}")
        }
    }
}


/* Test primeri:
    nacrtajHistogram [0,1,2,7,8,5,7,8,1,2,9]
        0:*
        1:**
        2:**
        3:
        4:
        5:*
        6:
        7:**
        8:**
        9:*
*/
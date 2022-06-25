object Zadatak1 {
    def uListu(broj: Int): List[Int] = {
        if(broj < 1)
            throw new Error("Funkcija 'uListu' radi samo sa prirodnim brojevima")
        else if(broj < 10)
            List(broj)
        else uListu(broj/10) ++ List(broj%10)
    }

    def main(args: Array[String]): Unit = {
        println(s"Konvertovanje broja u list cifara koje se u njemu pojavljuju")

        println("\nUnesite broj:")
        val broj: Int = readLine().toInt // .toInt je deprecated, korisceno je samo radi jednostavnosti koda

        println(s"\nLista cifara za broj $broj je ${uListu(broj)}")
    }
}
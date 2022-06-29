object Zadatak1 {
    val samoglasnici: String = "aeiou"

    def main(args: Array[String]): Unit = {
        println("Prebrojavanje samoglasnika u datom stringu\n(za zauztavljanje programa uneti: KRAJ)\n")
        
        var unos: String = ""

        do {
            print("Unesite string: ")
            unos = readLine() // deprecated; koristi se: scala.io.StdIn
            println(s"String '$unos' ima ${brojSamoglasnika(unos)} samoglasnika\n")
        } while(unos != "KRAJ")

    }

    def brojSamoglasnika(unos: String): Int = {
        def _brojSamoglasnika(unos: String): Int = {
            unos match {
                case "" => 0
                case unos => 
                    val slovo: Char = unos.charAt(0)
                    val slova: String = unos.substring(1)
                    if(samoglasnici.contains(slovo)) {
                        _brojSamoglasnika(slova) + 1
                    }
                    else {
                        _brojSamoglasnika(slova)
                    }
            }
        }

        _brojSamoglasnika(unos.toLowerCase())
    }
}

/* Test primeri:
    brojSamoglasnika "haskell"
        2
*/

object Zadatak2 {
    def main(args: Array[String]): Unit = {
        var listaInt: List[Int] = List.range(0, 10)
        println(s"parniPreNeparnih($listaInt) == ${parniPreNeparnih(listaInt)}")

        val listaStr = "haskell".toList
        println(s"parniPreNeparnih($listaStr) == ${parniPreNeparnih(listaStr)}")
    }

    def parniPreNeparnih[A](lista: List[A]): List[A] = {
        var novaLista: List[A] = List()
        var neparni: List[A] = List()

        var jesteParan: Boolean = true
        for(element <- lista) {
            if(jesteParan)
                novaLista = novaLista ++ List(element)
            else
                neparni = neparni ++ List(element)

            jesteParan = !jesteParan
        }

        novaLista ++ neparni
    }
} 
 
 
 
 
 
 
/* Test primeri:
    parniPreNeparnih [0..10]
        [0,2,4,6,8,10,1,3,5,7,9]

    parniPreNeparnih "haskell"
        "hselakl"
*/

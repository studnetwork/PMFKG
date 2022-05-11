data TipPoruke =  Info | Upozorenje | Greska KodGreske
    deriving (Eq, Ord, Show, Read)

type KodGreske = Int

{-
Info :: Char
Info = 'I'

Upozorenje :: Char
Upozorenje = 'W'

Greska :: Char
Greska = 'E'
-}

data Log = LogPoruka TipPoruke TimeStamp Opis | Nepoznato Opis
    deriving (Eq, Ord, Show, Read)

type TimeStamp = Int
type Opis = String


prvaGreska :: [Log] -> Log
prvaGreska ( (LogPoruka (Greska kod) ts opis) : logs )
    = pomocna (LogPoruka (Greska (-1)) 2147483647 "") ( (LogPoruka (Greska kod) ts opis) : logs ) -- 2147483647 je gornja granica za int
        where
        pomocna (LogPoruka (Greska kod) ts opis) [] =  (LogPoruka (Greska kod) ts opis)
        pomocna (LogPoruka (Greska kod) ts opis) ( (LogPoruka (Greska kod2) ts2 opis2) : logs )
            | ts2<ts    = pomocna (LogPoruka (Greska kod2) ts2 opis2) logs
            | otherwise = pomocna (LogPoruka (Greska kod) ts opis) logs
        pomocna (LogPoruka (Greska kod) ts opis) ( _ : logs ) = pomocna (LogPoruka (Greska kod) ts opis) logs
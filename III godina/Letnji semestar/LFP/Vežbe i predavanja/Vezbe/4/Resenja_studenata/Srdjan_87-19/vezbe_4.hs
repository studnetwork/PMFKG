readUntilEmpty :: IO ()
readUntilEmpty = do putStrLn "Unesite neku poruku"
                    line <- getLine
                    if line == []
                        then return ()
                    else do putStrLn ("Uneli ste: " ++ line ++ "\n")
                            readUntilEmpty

-- -----------------------------------------------------------------------------  

{- test primer
brisiKontrolne 0 [2,11,4,17,3,5,8,3,1,4]
[2,11,4,3,5,3,1]
-}

-- deklaracija/potpis
brisiKontrolne :: Int -> [Int] -> [Int]

{-- prva verzija
brisiKontrolne _ []     = []
brisiKontrolne _ [x]    = [x]
brisiKontrolne sumaDoSada (x:y:zs)
    | (sumaDoSada+x)==y = x : brisiKontrolne 0 zs
    | otherwise         = x : brisiKontrolne (sumaDoSada+x) (y:zs)
--}

-- druga verzija
brisiKontrolne _ [] = []
brisiKontrolne sumaDoSada (x:xs)
    | sumaDoSada==x = brisiKontrolne 0 xs
    | otherwise     = x : brisiKontrolne (sumaDoSada+x) xs

-- -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    --        

{- test primer
dodajKontrolne 2 0 0 [2,11,4,3,5,3,1]
[2,11,13,4,3,7,5,3,8,1]
-}

dodajKontrolne :: Int -> Int -> Int -> [Int] -> [Int]
dodajKontrolne korak trenutno sumaDoSada []
    | korak/=trenutno = []
    | otherwise       = [sumaDoSada]
dodajKontrolne korak trenutno sumaDoSada (x:xs)
    | trenutno==korak = sumaDoSada : dodajKontrolne korak 0 0 (x:xs)
    | otherwise       = x : dodajKontrolne korak (trenutno+1) (sumaDoSada+x) xs

-- -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    --    

{- test primer 1
ispravi 2 [2,11,4,17,6,9]
[2,11,13,4,6,10,9]
-}

{- test primer 2
ispravi 3 [2,11,4,17,6,9,15,2,3]
[2,11,4,17,6,9,2,17,3]
-}

ispravi :: Int -> [Int] -> [Int]
ispravi _ []     = []
ispravi korak xs = dodajKontrolne korak 0 0 (brisiKontrolne 0 xs)

-- -----------------------------------------------------------------------------
-- Napomena: 
-- u resenju na prezentaciji koeficijent i eksponent imaju drugaciji redosled

{- test primer 1: 2*2^3 + 4*2^5 + 6*2^7 == 912
izracunajPolinom 2 [(2,3),(4,5),(6,7)]
912
-}

{- test primer 2 (primer sa prezentacije) 
izracunajPolinom 2 [(2,1),(1,3)]
912
-}

type Polinom = [(Int,Int)]

izracunajPolinom :: Int -> Polinom -> Int
izracunajPolinom _ [] = 0
izracunajPolinom x ((koef,eksponent) : ostali) = koef * x^eksponent + izracunajPolinom x ostali


-- -----------------------------------------------------------------------------

{- test primer 1
brojPojavljivanjaSvakog [1,2,1,3,3,1]
[(1,3),(2,1),(3,2)]
-}

{- test primer 2
brojPojavljivanjaSvakog "test\tes\tt\nt"
[('t',4),('e',2),('s',2),('\t',2),('\n',1)] 
-}

brojPojavljivanjaSvakog :: Eq a => [a] -> [(a,Int)]
brojPojavljivanjaSvakog [] = []
brojPojavljivanjaSvakog (x:xs) = (x, 1 + brojPojavljivanja x xs) : brojPojavljivanjaSvakog (izbaci x xs)
                                  where

                                  brojPojavljivanja _ []     = 0
                                  brojPojavljivanja y (z:zs)
                                    | y==z      = 1 + brojPojavljivanja y zs
                                    | otherwise = brojPojavljivanja y zs

                                  izbaci _ [] = []
                                  izbaci y (z:zs)
                                    | y==z      = izbaci y zs
                                    | otherwise = z : izbaci y zs

-- -----------------------------------------------------------------------------

ispeglajListu :: [[a]] -> [a]
ispeglajListu [] = []
ispeglajListu (vektor:vektori) = vektor ++ ispeglajListu vektori

-- -----------------------------------------------------------------------------

nzd :: Int -> Int -> Int
nzd a 0 = a
nzd a b
    | a > b = nzd b (a `mod` b)
    | otherwise = nzd a (b `mod` a)
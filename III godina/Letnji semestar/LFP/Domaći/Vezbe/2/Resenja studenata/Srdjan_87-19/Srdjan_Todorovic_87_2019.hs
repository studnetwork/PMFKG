-- 1. Izdvoj parne elemente liste 
--   a) generisanjem liste
parni :: [Int] -> [Int]
parni xs = [ x | x <- xs, x `mod` 2 == 0 ]

--   b) rekurzivno
parni2 :: [Int] -> [Int]
parni2 [] = []
parni2 (x:xs)
    | x `mod` 2 == 0 = x : parni2 xs
    | otherwise = parni2



-- 2. Broj pojavljivanja X u listi Y 
pojava :: Int -> [Int] -> Int
pojava a [] = 0
pojava a (x:xs)
    | a == x = 1 + pojava a xs
    | otherwise = pojava a xs



-- 3. Lista elemenata koji se pojavljuju jedanput u listi
jedinstveni :: [Int] -> [Int]
jedinstveni xs = [ x | x <- xs, pojava x xs == 1]

-- 4. Brisanje duplikata elemenata (Skup od liste)
obrisiDuplikate :: [Int] -> [Int]
obrisiDuplikate [] = []
obrisiDuplikate (x:xs)
    | pojava x xs == 0 = x : obrisiDuplikate xs
    | otherwise = obrisiDuplikate xs


-- 5. Prvih K elemenata liste
prvihk :: Int -> [Int] -> [Int]
prvihk n (x:xs)
    | n <= 0 = []
    | otherwise = x : prvihk (n-1) xs

-- 6. Obrnuti listu
obrt :: [Int] -> [Int]
obrt [] = []
obrt (x:xs) = (obrt xs) ++ [x]

-- 7. Definisati fukciju gde total f vraća funkciju koja za n računa f 0 + f 1 + ... + f n 
total :: (Int-> Int) -> (Int-> Int)
total f 
    = func 
    where
        func n 
            | n < 0 = 0
            | otherwise = func (n-1) + f n
        
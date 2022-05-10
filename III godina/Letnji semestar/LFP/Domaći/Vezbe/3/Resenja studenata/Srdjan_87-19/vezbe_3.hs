data Tree a = Nil | Node a (Tree a) (Tree a)
    deriving (Eq, Ord, Show, Read)

-- -------------------------------------------------------------------------------------

-- 1. Broj pojavljivanja cvora u stablu
{-
test primer:
brojPojavljivanja 3 (Node 2 (Node 3 Nil Nil) (Node 1 Nil (Node 3 Nil Nil)))
2
-}

brojPojavljivanja :: Eq a => a -> Tree a -> Int
brojPojavljivanja content Nil = 0
brojPojavljivanja value (Node content left right)
    | value == content = 1 + brojPojavljivanja value left + brojPojavljivanja value right
    | otherwise = brojPojavljivanja value left + brojPojavljivanja value right                           

-- -------------------------------------------------------------------------------------

-- 2. Prevodjenje binarnog stabla u listu brojeva

{-
test primer:
treeToList (Node 1 (Node 2 Nil Nil) (Node 3 Nil (Node 4 Nil Nil)))
[1,2,3,4]

in order varijanta: 
    treeToList left ++ [content] ++ treeToList right
-}

treeToList :: Tree a -> [a]
treeToList Nil = []
treeToList (Node content left right) = [content] ++ treeToList left ++ treeToList right

-- -------------------------------------------------------------------------------------

-- 3. Lista faktorijela prirodnih brojeva

{-
max pozitivna vrednost za Int u Haskell-u je 2147483647, pa zbog toga nakon 2004189184
vraca negativne vrednosti, a nakon toga i nule
-}

fakt :: [Int]
fakt = [ factorial(naturalNumber) | naturalNumber <- [1..] ]
       where
       factorial x
            | x == 1 = 1
            | otherwise = factorial(x-1) * x

-- -------------------------------------------------------------------------------------

-- 4. Lista Fibonacijevih brojeva

{-
Beskonacna lista
-}

fib :: [Int]
fib = [ fibonacci number | number <- [1..]]
      where
      fibonacci 1 = 1
      fibonacci 2 = 1
      fibonacci x = fibonacci(x-2) + fibonacci(x-1)

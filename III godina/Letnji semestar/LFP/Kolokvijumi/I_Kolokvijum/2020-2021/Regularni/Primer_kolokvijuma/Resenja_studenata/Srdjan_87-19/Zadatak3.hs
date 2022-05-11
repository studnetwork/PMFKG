
nacrtajHistogram :: [Int] -> IO ()
nacrtajHistogram [] = return ()
nacrtajHistogram (x:xs) = putStr (foldl (++) "" linije)
                          where
                          linije = map (ispisiPonavljanjaCifre') [0..9]
                          ispisiPonavljanjaCifre' cifra = ispisiPonavljanjaCifre cifra (brojPojavljivanja cifra (x:xs))

-- -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -- 

brojPojavljivanja :: Int -> [Int] -> Int              
brojPojavljivanja x [] = 0
brojPojavljivanja x (y:ys)
    | x==y = 1 + brojPojavljivanja x ys
    | otherwise = brojPojavljivanja x ys

-- -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -- 

zvezdice :: Int -> String
zvezdice 0 = ""
zvezdice brPojav = "*" ++ zvezdice (brPojav-1)

-- -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -- 

ispisiPonavljanjaCifre :: Int -> Int -> String
ispisiPonavljanjaCifre x brPojav = show x ++ ":" ++ (zvezdice brPojav) ++ "\n" 


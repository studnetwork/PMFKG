-- Prvi nacin
uListu :: Int -> [Int]
uListu 0 = [0]
uListu x = pomocna x
           where
           pomocna 0 = []
           pomocna x = pomocna (x `quot` 10) ++ [x `rem` 10]

{- Drugi nacin
uListu :: Int -> [Int]
uListu x = [ (read (c:"") :: Int) | c <- (show x)]
-}
lokalniMaksimum :: [Int] -> [Int]
lokalniMaksimum []  = []
lokalniMaksimum [x] = []
lokalniMaksimum [x,y] = []
lokalniMaksimum (x:y:z:ts)
    | y > x && y > z = y : lokalniMaksimum (z:ts)
    | otherwise      = lokalniMaksimum (y:z:ts)
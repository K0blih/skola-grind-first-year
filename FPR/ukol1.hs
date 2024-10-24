isPrime :: Int -> Bool
isPrime 1 = False
isPrime p = isPrimeSub p (p-1) 
    where
    isPrimeSub _ 1 = True
    isPrimeSub n x | n `mod` x == 0 = False
                   | otherwise = isPrimeSub n (x-1)

main = do
    print (isPrime 3)
    print (isPrime 8)
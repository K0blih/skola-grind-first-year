fact :: Int -> Int
fact 0 = 1
fact x = x * fact (x-1)

fib :: Int -> Int
fib 0 = 1
fib 1 = 1
fib x = fib (x-1) + fib (x-2)

leapYear :: Int -> Bool
leapYear x 
 | x `mod` 400 == 0 = True
 | x `mod` 100 == 0 = False
 | otherwise = x `mod` 4 == 0

isPrime :: Int -> Bool
isPrime 1 = False
isPrime n = primeHelper n (n-1) where
    primeHelper _ 1 = True
    primeHelper x y
     | x `mod` y == 0 = False
     | otherwise = primeHelper x (y-1)

threeDifferent :: Int -> Int -> Int -> Bool
threeDifferent a b c = a /= b && b /= c && a /= c

fourEqual :: Int -> Int -> Int -> Int -> Bool
fourEqual a b c d = a == b && b == c && c == d

averageThree :: Int -> Int -> Int -> Float
averageThree a b c = fromIntegral(sum [a,b,c]) / 3

howManyAboveAverage :: Int -> Int -> Int -> Int
howManyAboveAverage a b c = length [x | x <- [a,b,c], fromIntegral x > averageThree a b c]

power :: Int -> Int -> Int
power _ 0 = 1
power x y = x * power x (y-1)

mult :: Int -> Int -> Int
mult _ 0 = 0
mult x y = x + mult x (y-1)

nonZeros :: [Int] -> [Int]
nonZeros [] = []
nonZeros xs = filter (/= 0) xs

rotateLeft1 :: [a] -> [a]
rotateleft1 [] = []
rotateLeft1 xs = tail xs ++ [head xs]

rotateRight1 :: [a] -> [a]
rotateRight1 [] = []
rotateRight1 xs = [last xs] ++ init xs

oddMembers :: [Int] -> [Int]
oddMembers xs = [x | x <-xs, odd x]

countOddMembers :: [Int] -> Int
countOddMembers xs = length [x | x <-xs, odd x]

compareLists :: Eq a => [a] -> [a] -> Bool
compareLists xs ys = xs == ys

removeOne :: Eq a => a -> [a] -> [a]
removeOne _ [] = []
removeOne y (x:xs)
 | y == x = xs
 | otherwise = x : removeOne y xs

removeAll :: Eq a => a -> [a] -> [a]
removeAll el xs = filter (/=el) xs 

replicate' :: Int -> a -> [a]
replicate' x y = take x (repeat y)

-- rotateLeftN :: [a] -> Int -> [a]
-- rotateLeftN [] 0 = xs
-- rotateLeftN xs n = rotateLeftN (n-1) (rotateLeft1 xs)

-- rotateRightN :: [a] -> Int -> [a]
-- rotateRightN [] 0 = xs
-- rotateRightN xs n = rotateRightN (n-1) (rotateLeft1 xs)

alternate :: [a] -> [a] -> [a]
alternate [] ys = ys
alternate xs [] = xs
alternate (x:xs) (y:ys) = x : y : alternate xs ys

filterEvenGt7 :: [Int] -> [Int]
filterEvenGt7 xs = filter (even) (filter (>=7) xs)

makeTriples :: [a] -> [(a,a,a)]
makeTriples [] = []
makeTriples (x:y:z:xs) = (x, y, z) : makeTriples xs
makeTriples _ = []

insertOnIndex :: [a] -> a -> Int -> [a]
insertOnIndex xs el index = take index xs ++ [el] ++ drop index xs
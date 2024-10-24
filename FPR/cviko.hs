factorial :: Int -> Int
factorial f
 | f == 0 = 1
 | otherwise = f * factorial (f-1)

fact 0 = 1
fact f = f * factorial (f-1)

mult :: Int -> Int -> Int
mult _ 0 = 0
mult x y = x + mult x (y-1)

prime :: Int -> Bool
prime 1 = False
prime n = tmp (n-1) where
    tmp i | i == 1 = True
          | n `mod` i == 0 = False
          | otherwise = tmp (i-1)

gcd1 :: Int -> Int -> Int
gcd1 x y 
 | x == y = x
 | x > y = gcd1 y (x - y)
 | x < y = gcd1 (y - x) x

sumIt :: [Int] -> Int
sumIt [] = 0
sumIt (x:xs) = x + sumIt xs

getHead :: [Int] -> Int
getHead [x] = x
getHead (x:xs) = x

isElement :: Eq a => a -> [a] -> Bool
isElement a [] = False
isElement y (x:xs)
 | y == x = True
 | otherwise = isElement y xs

getTail :: [a] -> [a]
getTail (x:xs) = xs

getInit :: [a] -> [a]
getInit [_] = []
getInit (x:xs) = x : getInit xs

nonZeros :: [Int] -> [Int]
nonZeros [] = []
nonZeros (x:xs)
 | x == 0 = nonZeros xs
 | x /= 0 = x : nonZeros xs

max' :: [Int] -> Int
max' (x:xs) = tmp x xs where
    tmp am [] = am
    tmp am (x:xs)   | am < x = tmp x xs
                    | otherwise = tmp am xs

combine :: [a] -> [a] -> [a]
combine [] a = a
combine (x:xs) a = x : combine xs a

take' :: Int -> [a] -> [a]
take' 0 xs = []
take' n [] = []
take' n (x:xs) = x : take' (n-1) xs

drop' :: Int -> [a] -> [a]
drop' 0 x = x
drop' _ [] = []
drop' n (_:xs) = drop' (n-1) xs

divisors :: Int -> [Int]
divisors n = tmp n where
    tmp 0 = []
    tmp x | n `mod` x == 0 = [x] ++ tmp (x-1)
          | otherwise = tmp (x-1)

zipThem :: [a] -> [b] -> [(a,b)]
zipThem (x:xs) (y:ys) = (x,y) : zipThem xs ys
zipThem _ _ = []

dotProduct :: [a] -> [b] -> [(a,b)]
dotProduct xs ys = [(x,y)|x<-xs, y<-ys]

-- import Data.List (sort)

-- countries :: [(String, Int)] -> Int -> [String]
-- countries pair minC = [a | (a,b) <- pair, b > minC]

-- intersection3 :: Eq a => [a] -> [a] -> [a] -> [a]
-- intersection3 a b c = [x | x <- a, x `elem` b, x `elem` c]

-- merge :: Ord a => [a] -> [a] -> [a]
-- merge xs ys = sort (xs ++ ys)
-- merge' :: Ord a => [a] -> [a] -> [a]
-- merge' xs ys = quickSort (xs ++ ys) where
--     quickSort [] = []
--     quickSort (z:zs) = quickSort [x | x <- zs, x <= z] ++ [z] ++ quickSort [y | y <- zs, y > z]

-- select :: [(String, Float)] -> String
-- select chalka = head [a | (a,b) <- chalka, b == maximum [b | (a,b) <- chalka]]

-- factorials :: Int -> Int -> [(Int, Int)]
-- factorials a b = [(x, factorial x) | x <- [a..b]]
--   where
--     factorial 0 = 1
--     factorial n = n * factorial (n - 1)

-- -- splitWith :: Eq a => [a] -> [a] -> [[a]]

-- convert :: [(String, Int, Float)] -> [(String, Float)]
-- convert seznam = [(a, fromIntegral b * c) | (a,b,c) <- seznam]

-- replaceByRepeat :: String -> Char -> Int -> String
-- replaceByRepeat list char count = concat [if a == char then replicate count char else [a] | a <- list]

-- -- change :: [a] -> [(Int, Int)] -> [a]                 cooked
-- -- change seznam [(a,b)] = reverse (take b (drop a seznam)) ++ drop (a + b) seznam

-- accounts :: [(String, Int)] -> [String]
-- accounts accs = [a | (a,b) <- accs, b > 0]

-- -- mostFrequent :: [Int] -> Int
-- -- mostFrequent ns = snd (maximum [ (length ks, head ks) | ks <- group (sort ns) ])

-- -- getHashMap cooked

-- filter' :: [(String, Int)] -> Int -> [String]
-- filter' dvojice vek = [a | (a,b) <- dvojice, b < vek]

-- positions :: String -> Char -> [Int]
-- positions retezec char = [i | (c, i) <- zip retezec [0..], c == char]

-- unique :: Eq a => [a] -> [a] -> [a] -> [a]
-- unique a b c = [x | x <- a, not (x `elem` b), not (x `elem` c)] ++ [x | x <- b, not (x `elem` a), not (x `elem` c)] ++ [x | x <- c, not (x `elem` a), not (x `elem` b)]

-- average :: [(String, Int)] -> Double
-- average dvojice = fromIntegral (sum [b | (_, b) <- dvojice]) / fromIntegral (length dvojice)

-- -- changes :: Eq a => [(a,b)] -> a -> b -> [(a,b)] cooked

-- countries seznam x = [a | (a,b) <- seznam, b > x]

-- intersection3 :: Ord a => [a] -> [a] -> [a] -> [a]
-- intersection3 a b c = [x | x <- a, x `elem` b, x `elem` c]

-- merge :: Ord a => [a] -> [a] -> [a]
-- merge xs ys = quicksort (xs++ys) where
--   quicksort [] = []
--   quicksort [z] = [z]
--   quicksort (z:zs) = quicksort [x | x <- zs, x <= z] ++ [z] ++ quicksort [y | y <- zs, y > z]

-- select seznam = [a | (a,b) <- seznam, b ==  maximum [b | (a,b) <- seznam]]

-- factorials x y = [(a, factorial a) | a <- [x..y]] where
--   factorial 0 = 1
--   factorial n = n * factorial (n-1)

-- -- splitWith cooked

-- convert seznam = [(a,fromIntegral b * c) | (a,b,c) <- seznam]

-- replaceByRepeat seznam char x = concat [if a == char then replicate x char else [a] | a <- seznam]

-- average seznam = fromIntegral (sum [b | (a,b) <- seznam]) / fromIntegral (length [b | (a,b) <- seznam])

-- changes tuple x y = [(a,if a == x then [y] else [b]) | (a,b) <- tuple]

-- buildText seznam = concat (concat [replicate b a | (a,b) <- seznam])

-- positions seznam char = [b | (a,b) <- zip seznam [0..], a == char]

-- unique a b c = [x | x <- a, not (elem x b), not (elem x c)] ++ [x | x <- b, not (elem x a), not (elem x c)] ++ [x | x <- c, not (elem x b), not (elem x a)]

-- mostFrequent :: [Int] -> Int
-- mostFrequent seznam =

countries seznam c = [a | (a,b) <- seznam, b > c]

intersection3 a b c = [x | x <- a, elem x b, elem x c]

merge xs ys = quicksort (xs ++ ys) where
  quicksort [] = []
  quicksort [z] = [z]
  quicksort (z:zs) = quicksort [x | x <- zs, x <= z ] ++ [z] ++ quicksort [y | y <- zs, y > z]

select seznam = [a | (a,b) <- seznam, b == maximum [b | (a,b) <- seznam]]

factorials x y = [(a, factorial a) | a <- [x..y]] where
  factorial 0 = 1
  factorial n = n * factorial (n-1)

convert seznam = [(a, fromIntegral b * c) | (a,b,c) <- seznam]

replaceByRepeat seznam char count = concat [if a == char then replicate count char else [a] | a <- seznam]

positions seznam char = [b | (a,b) <- zip seznam [0..], char == a]

unique a b c = [x | x <- a, not (elem x b), not (elem x c)] ++ [x | x <- b, not (elem x a), not (elem x c)] ++ [x | x <- c, not (elem x b), not (elem x a)]

average seznam = fromIntegral (sum [b | (a,b) <- seznam]) / fromIntegral (length [b | (a,b) <- seznam])

changes seznam a b = [(x,if a == x then [b] else [y]) | (x,y) <- seznam]

buildText seznam = concat (concat [replicate b a | (a,b) <- seznam])
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

-----------------------------------------------------------------------------------

data Tree a = Leaf a 
            | Branch a (Tree a) (Tree a) deriving (Show)

testTree1 :: Tree Int            
testTree1 = Branch 12 (Branch 23 (Leaf 34) (Leaf 45)) (Leaf 55)

testTree2 :: Tree Char            
testTree2 = Branch 'a' (Branch 'b' (Leaf 'c') (Leaf 'd')) (Leaf 'e')

getGreaterElements :: Ord a => Tree a -> a -> [a]
getGreaterElements (Leaf x) m | x > m = [x]
                              | otherwise = []
getGreaterElements (Branch x l r) m = [list | list <- (getGreaterElements l m ++ [x] ++ getGreaterElements r m), list > m]

toString :: Show a => Tree a -> String
toString (Leaf x) = show x
toString (Branch x l r) = show x ++ "(" ++ (toString l) ++ "," ++ (toString r) ++ ")"

fromString :: Read a => String -> Tree a
fromString inp = fst (fromString' inp) where
  fromString' :: Read a => String -> (Tree a,String)
  fromString' inp = 
    let
      before = takeWhile (\x ->  x /='(' &&  x /=',' &&  x/=')') inp 
      after = dropWhile (\x ->  x /='(' &&  x /=',' && x/=')') inp
      value = read before
    in if null after || head after /= '(' then (Leaf value, after) else 
        let
          (l,after') = fromString' (tail after)
          (r,after'') = fromString' (tail after') 
        in (Branch value l r, tail after'')

leafCount :: Tree a -> Int
leafCount (Leaf x) = 1
leafCount (Branch x l r) = leafCount l + leafCount r

branchCount :: Tree a -> Int
branchCount (Leaf x) = 0
branchCount (Branch x l r) = branchCount l + branchCount r + 1

contains :: Eq a => Tree a -> a -> Bool
contains (Leaf x) value | x == value = True
                        | otherwise = False
contains (Branch x l r) value | x == value = True
                              | contains l value = True
                              | contains r value = True
                              | otherwise = False

greaterThan :: Ord a => Tree a -> a -> Int
greaterThan (Leaf x) m | x > m = 1
                       | otherwise = 0
greaterThan (Branch x l r) m = length [list | list <- (getGreaterElements l m ++ [x] ++ getGreaterElements r m), list > m]

--------------------------------------

-- data Entity = Point {x :: Double, y :: Double}
--             | Circle {centerX :: Double, centerY :: Double, radius :: Int}
--             | Container {children :: [Entity]}
--             deriving (Show)

-- entityExample :: Entity
-- entityExample = Container [
--                    Point 1.0 2.0,
--                    Circle 3.0 4.0 5,
--                    Container [Point 6.0 7.0, Circle 8.0 9.0 10]
--                ]

data Component = 
    TextBox {name :: String, text :: String} 
    | Button {name :: String, value :: String} 
    | Container {name :: String, children :: [Component]}

gui :: Component
gui = Container "My App" 
    [ Container "Menu" 
        [ Button "btn_new" "New",
          Button "btn_open" "Open",
          Button "btn_close" "Close"
        ],
      Container "Body" 
        [ TextBox "textbox_1" "Some text goes here" ],
      Container "Footer" []
    ]

countButtons :: Component -> Int
countButtons (TextBox _ _) = 0
countButtons (Button _ _) = 1
countButtons (Container _ children) = sum (map countButtons children)

addElement :: Component -> Component -> String -> Component
addElement (TextBox name text) _ _ = TextBox name text
addElement (Button name value) _ _ = Button name value
addElement (Container name children) newComponent targetName
    | name == targetName = Container name (children ++ [newComponent])
    | otherwise = Container name (map (\child -> addElement child newComponent targetName) children)



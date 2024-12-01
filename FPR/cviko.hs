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

quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort [x] = [x]
quicksort (x:xs) = quicksort [y | y<-xs,y<x] ++ [x] ++ quicksort (filter (x<=) xs)

oddList :: Int -> Int -> [Int]
oddList x y = filter odd [x..y]

removeDuplicates :: Eq a => [a] -> [a]
removeDuplicates [] = []
removeDuplicates (x:xs) = x : removeDuplicates (filter (/= x) xs)

union :: Eq a => [a] -> [a] -> [a]
union xs ys = [x | x <- removeDuplicates xs] ++ [y | y<-ys, not (elem y xs)]

intersection :: Eq a => [a] -> [a] -> [a]
intersection xs ys = [y | y<-ys, elem y xs]

countThem :: String -> [(Char, Int)]
countThem [] = []
countThem xs = [(x, length (filter (==x) xs)) | x <- removeDuplicates xs]

goldbach :: Int-> [(Int, Int)]
goldbach n = [(x, n-x) | x<- [1..(n-1)], prime x, prime (n-x)]

data Expr = Num Int
          | Add Expr Expr
          | Sub Expr Expr
          | Mul Expr Expr
          | Div Expr Expr
          | Var Char deriving (Eq)

ex1 = Add (Num 1) (Mul (Num 2) (Num 3))
ex2 = Mul (Add (Num 1) (Num 2)) (Num 3)

eval :: Expr -> Int
eval (Num x) = x
eval (Add l r) =  (eval l) + (eval r)
eval (Sub l r) =  (eval l) - (eval r)
eval (Mul l r) =  (eval l) * (eval r)
eval (Div l r) =  (eval l) `div` (eval r)

showExpr :: Expr -> String
showExpr (Num x) = show x
showExpr (Var ch) = [ch]
showExpr (Add l r) = "(" ++ showExpr l ++ "+" ++ showExpr r ++ ")"
showExpr (Sub l r) = "(" ++ showExpr l ++ "-" ++ showExpr r ++ ")"
showExpr (Mul l r) = "(" ++ showExpr l ++ "*" ++ showExpr r ++ ")"
showExpr (Div l r) = "(" ++ showExpr l ++ "/" ++ showExpr r ++ ")"

instance Show Expr where
    show = showExpr

deriv :: Expr -> Char -> Expr
deriv (Num num) x = Num 0
deriv (Var myVar) x | myVar == x = Num 1
                    | otherwise = Num 0
deriv (Add u v) x = Add (deriv u x) (deriv v x)
deriv (Sub u v) x = Sub (deriv u x) (deriv v x)
deriv (Mul u v) x = Add (Mul (deriv u x) v) (Mul (deriv v x) u)
deriv (Div u v) x = Div (Sub (Mul (deriv u x) v) (Mul (deriv v x) u)) (Mul v v)

data Tree a = Leaf a 
            | Branch a (Tree a) (Tree a) deriving (Show)

testTree1 :: Tree Int            
testTree1 = Branch 12 (Branch 23 (Leaf 34) (Leaf 45)) (Leaf 55)

sum' :: Tree Int -> Int
sum' (Leaf x) = x
sum' (Branch x l r) = sum' l + x + sum' r

toList :: Tree a -> [a]
toList (Leaf x) = [x]
toList (Branch x l r) = toList l ++ [x] ++ toList r

maxTree :: Ord a => Tree a -> a
maxTree (Leaf x) = x
maxTree (Branch x l r) = maximum [x, maxTree l, maxTree r]

depthTree :: Tree a -> Int
depthTree (Leaf x) = 1
depthTree (Branch x l r) = max (depthTree l) (depthTree r) + 1

data Point = Point {column::Int,row::Int}

data Position = Position {leftTopCorner :: Point, width :: Int, height :: Int}

data Component
  = TextBox {name :: String, position :: Position, text :: String}
  | Button {name :: String, position :: Position, text :: String}
  | Container {name :: String, children :: [Component]}

gui :: Component
gui =
  Container "My App"
    [ Container "Menu"
        [ Button "btn_new" (Position (Point 0 0) 100 20) "New",
          Button "btn_open" (Position (Point 100 0) 100 20) "Open",
          Button "btn_close" (Position (Point 200 0) 100 20) "Close"
        ],
      Container "Body" [TextBox "textbox_1" (Position (Point 0 20) 300 500) "Some text goes here"],
      Container "Footer" []
    ]

instance Show Point where
    show (Point {column = x, row = y}) = "(" ++ show x ++ "," ++ show y ++ ")"

instance Show Position where
    show (Position {leftTopCorner = x, width = y, height = z}) = show x ++ "[" ++ show y ++ "," ++ show z ++ "]"

instance Show Component where
    show c = showTmp "" c where
        showTmp indent (TextBox {name = x, position = p, text = t}) = indent ++ show p ++ " TextBox[" ++ x ++ "]: " ++ t
        showTmp indent (Button {name = x, position = p, text = t}) = indent ++ show p ++ " Button[" ++ x ++ "]: " ++ t
        showTmp indent (Container {name = x, children = childs}) = let
            processed = concat ["\n" ++ showTmp (indent ++ "  ") c | c <- childs]
            in indent ++ "Container - " ++ x ++ processed

insertInto :: Component -> String -> Component -> Component
insertInto (TextBox x y z) _ _ = (TextBox x y z)
insertInto (Button x y z)  _ _ = (Button x y z)
insertInto (Container x child) name what | x == name = Container x (what : child)
                                         | otherwise = Container x [insertInto c name what | c <- child]
-- insertInto c _ _ = c                                         

deleteFrom :: Component -> String -> Component
deleteFrom (Container x child) target = Container x [deleteFrom c target |c<-child, name c /= target ]
deleteFrom c _ = c
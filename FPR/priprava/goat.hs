data Company = Name {name :: String}
             | Employees {count :: Int}
             | OwnerOf {children :: [Company]}
             deriving (Show)

example :: Company
example =
    OwnerOf [
        Name "Penis",
        Employees 20,
        OwnerOf [
            Name "Curak",
            Employees 10
        ]
    ]

data FileType = Image | Executable | SourceCode | TextFile deriving (Show)

data Entry 
    = File { name :: String, size :: Int, fileType :: FileType }
    | Directory { name :: String, entries :: [Entry] }
    deriving (Show)
-- Example root directory structure
root :: Entry
root = Directory "root" 
    [ File "logo.jpg" 5000 Image
    , Directory "classes" 
        [ File "notes-fpr.txt" 200 TextFile
        , File "presentation.jpg" 150 Image
        , File "first_test.hs" 20 SourceCode 
        ]
    ]

countLargerFiles :: Int -> Entry -> Int
countLargerFiles x (File _ size _) = if size > x then 1 else 0
countLargerFiles x (Directory _ children) = sum (map (countLargerFiles x) children)

removeFile :: String -> Entry -> Entry
removeFile delName (Directory x children) = Directory x [removeFile delName c | c <- children, name c /= delName]
removeFile _ x = x

data Entity = Point {x :: Double, y :: Double}
            | Circle {cX :: Double, cY :: Double, r :: Int}
            | Box {children :: [Entity]}
            deriving (Show)

example :: Entity
example =
    Box [
        Point 10 5.5,
        Circle 10 5.5 3,
        Box [
            Point 10 5.5,
            Circle 10 5.5 3
        ]
    ]

data FileType = Image | Executable | SourceCode | TextFile deriving (Show)

data Entry 
    = File { name :: String, size :: Int, fileType :: FileType }
    | Directory { name :: String, entries :: [Entry] }
    deriving (Show)
-- Example root directory structure
root :: Entry
root = Directory "root" 
    [ File "logo.jpg" 5000 Image
    , Directory "classes" 
        [ File "notes-fpr.txt" 200 TextFile
        , File "presentation.jpg" 150 Image
        , File "first_test.hs" 20 SourceCode 
        ]
    ]

countSize :: Entry -> Int
countSize (File _ size _) = size
countSize (Directory _ children) = sum (map countSize children)

directorySizes :: Entry -> [(String, Int)]
directorySizes (File _ _ _) = []
directorySizes (Directory name children) = (name, countSize (Directory name children)) : concatMap directorySizes children

data TernaryTree a = Leaf a
                   | Branch a (TernaryTree a) (TernaryTree a) (TernaryTree a)
                   deriving (Show)

example :: TernaryTree Int
example = Branch 1 (Branch 1 (Leaf 1) (Leaf 2) (Leaf 3)) (Branch 2 (Leaf 1) (Leaf 2) (Leaf 3)) (Branch 3 (Leaf 1) (Leaf 2) (Leaf 3))

data FileType = Image | Executable | SourceCode | TextFile deriving (Show)

data Entry 
    = File { name :: String, size :: Int, fileType :: FileType }
    | Directory { name :: String, entries :: [Entry] }
    deriving (Show)
-- Example root directory structure
root :: Entry
root = Directory "root" 
    [ File "logo.jpg" 5000 Image
    , Directory "classes" 
        [ File "notes-fpr.txt" 200 TextFile
        , File "presentation.jpg" 150 Image
        , File "first_test.hs" 20 SourceCode,
        Directory "empty1" []
        ],
        Directory "empty2" []
    ]

countEmptyDirectories :: Entry -> Int
countEmptyDirectories (File _ _ _) = 0
countEmptyDirectories (Directory name children) = if null children then 1 + sum (map countEmptyDirectories children) else sum (map countEmptyDirectories children)

getFiles :: Entry -> String -> [String]
getFiles (File name _ _) suffix = if suffix == drop (length name - length suffix) name then [name] else []
getFiles (Directory _ children) suffix = concatMap (`getFiles` suffix) children

data Article = Text { text :: String }
             | Chapter { name :: String, children :: [Article]}
             deriving (Show)

example :: Article
example =
    Chapter "1" [
        Text "cau",
        Chapter "2" [
            Text "ahoj"
        ]
    ]

data FileType = Image | Executable | SourceCode | TextFile deriving (Show)

data Entry 
    = File { name :: String, size :: Int, fileType :: FileType }
    | Directory { name :: String, entries :: [Entry] }
    deriving (Show)
-- Example root directory structure
root :: Entry
root = Directory "root" 
    [ File "logo.jpg" 5000 Image
    , Directory "classes" 
        [ File "notes-fpr.txt" 200 TextFile
        , File "presentation.jpg" 150 Image
        , File "first_test.hs" 20 SourceCode,
        Directory "empty1" []
        ],
        Directory "empty2" []
    ]

countDirectories :: Entry -> Int
countDirectories (File _ _ _) = 0
countDirectories (Directory _ children) = 1 + sum (map countDirectories children)

filterImages :: Entry -> Entry
filterImages (Directory name children) = Directory name [filterImages c | c <- children, helper c]
filterImages x = x

helper :: Entry -> Bool
helper (File _ _ Image) = False
helper x = True

data Element = Button { name :: String, text :: String}
             | Text { text :: String }
             | Panel { children :: [Element] }
             deriving (Show)

example :: Element
example =
    Panel [
        Button "cau" "ahoj",
        Text "penis",
        Panel [
            Button "cau" "ahoj",
            Text "penis"
        ]
    ]

data FileType = Image | Executable | SourceCode | TextFile deriving (Show)

data Entry 
    = File { name :: String, size :: Int, fileType :: FileType }
    | Directory { name :: String, entries :: [Entry] }
    deriving (Show)
-- Example root directory structure
root :: Entry
root = Directory "root" 
    [ File "logo.jpg" 5000 Image
    , Directory "classes" 
        [ File "notes-fpr.txt" 200 TextFile
        , File "presentation.jpg" 150 Image
        , File "first_test.hs" 20 SourceCode,
        Directory "empty1" []
        ],
        Directory "empty2" []
    ]

countImages :: Entry -> Int
countImages (File _ _ Image) = 1
countImages (File _ _ _) = 0
countImages (Directory _ children) = sum (map countImages children)

fullNames :: Entry -> [String]
fullNames dir = fullNamesHelper dir ""

fullNamesHelper :: Entry -> String -> [String]
fullNamesHelper (File name _ _) path = [path ++ "/" ++ name]
fullNamesHelper (Directory name children) path = concatMap (`fullNamesHelper` (path ++ "/" ++ name)) children

data Item = Item {name :: String, price :: Int} deriving (Show)
data Section = Section {name' :: String, items :: [Item], section :: [Section]} deriving (Show)

item1 = Item "penis" 10
section1 = Section "penisy" [item1] []

example =
    Section "obchod" [item1] [section1]

data FileType = Image | Executable | SourceCode | TextFile deriving (Show)

data Entry 
    = File { name :: String, size :: Int, fileType :: FileType }
    | Directory { name :: String, entries :: [Entry] }
    deriving (Show)
-- Example root directory structure
root :: Entry
root = Directory "root" 
    [ File "logo.jpg" 5000 Image
    , Directory "classes" 
        [ File "notes-fpr.txt" 200 TextFile
        , File "presentation.jpg" 150 Image
        , File "first_test.hs" 20 SourceCode,
        Directory "empty1" []
        ],
        Directory "empty2" []
    ]

countFiles :: Entry -> Int
countFiles (File _ _ _) = 1
countFiles (Directory _ children) = sum (map countFiles children)

removeFiles :: String -> Entry -> Entry
removeFiles suffix (Directory x children) = Directory x [removeFiles suffix c | c <- children, suffix /= drop (length (name c) - length suffix) (name c)]
removeFiles _ x = x

zipAll :: Entry -> (Int -> Int) -> Entry
zipAll (File name size fileType) f = (File (name ++ ".zip") (f size) fileType)
zipAll (Directory x children) f = Directory x [zipAll c f | c <- children]

adjustSize :: Int -> Int
adjustSize size = size * 2
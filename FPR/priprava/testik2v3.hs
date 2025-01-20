data TernaryTree a = Leaf a 
                   | Branch a (TernaryTree a) (TernaryTree a) (TernaryTree a)
                   deriving (Show)

example :: TernaryTree Int
example = Branch 1 (Branch 2 (Leaf 1) (Leaf 2) (Leaf 3)) (Branch 2 (Leaf 1) (Leaf 2) (Leaf 3)) (Branch 3 (Leaf 1) (Leaf 2) (Leaf 3))

-- Úkol 2
-- Definice datových typů FileType a Entry
data FileType = Image | Executable | SourceCode | TextFile deriving (Show)

data Entry
  = File {name :: String, size :: Int, ftype :: FileType}
  | Directory {name :: String, entries :: [Entry]} deriving (Show)

-- Příklad datové struktury
root :: Entry
root =
  Directory
    "root"
    [ File "notes-fp.txt" 200 TextFile,
      File "presentation.jpg" 150 Image,
      Directory
        "classes"
        [ File "first_test.hs" 300 SourceCode
        ],
      Directory
        "prazdny"
        []
    ]

countEmptyDirectories :: Entry -> Int
countEmptyDirectories (File _ _ _) = 0
countEmptyDirectories (Directory _ entries)
    | null entries = 1
    | otherwise = sum (map countEmptyDirectories entries)

getFiles :: Entry -> String -> [String]
getFiles (File name _ _) suffix = if reverse (take 3 (reverse name)) == suffix then [name] else []
getFiles (Directory _ entries) suffix = concat (map (`getFiles` suffix) entries)
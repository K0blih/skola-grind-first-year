data DynamicTree a 
    = Leaf a 
    | Branch a [DynamicTree a]
    deriving (Show)

tree :: DynamicTree Int
tree = Branch 1 [Branch 2 [Branch 3 [Branch 4 [Leaf 1]], Branch 5[]], Branch 3 [], Leaf 2]

data FileType = Image | Executable | SourceCode | TextFile deriving (Show, Eq)

data Entry
  = File {name :: String, size :: Int, ftype :: FileType}
  | Directory {name :: String, entries :: [Entry]} deriving (Show, Eq)

--příklad datové struktury
root :: Entry
root =
  Directory
    "root"
    [ File "notes-fp.txt" 200 TextFile,
      File "presentation.jpg" 150 Image,
      Directory
        "classes"
        [ File "first_test.hs" 300 SourceCode
        ]
    ]

countFiles :: Entry -> Int
countFiles (File _ _ _) = 1
countFiles (Directory _ entries) = sum (map countFiles entries)

fullNames :: Entry -> [String]
fullNames entry = fullNamesHelper entry ""

fullNamesHelper :: Entry -> String -> [String]
fullNamesHelper (File name _ _) path = [path ++ "/" ++ name]
fullNamesHelper (Directory name entries) path = 
  concatMap (\entry -> fullNamesHelper entry (path ++ "/" ++ name)) entries
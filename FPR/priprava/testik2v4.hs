data Article
    = Text { jmeno :: String }
    | Chapter { jmeno :: String, value :: [Article] } 
    deriving (Show)

example :: Article
example = Chapter "Kapitola 1"
    [ Text "za sedmi haskelly",
      Chapter "Podkapitola"
        [ Text "a sedmi semestry" ]
    ]

-- Úkol 2
-- Definice datových typů FileType a Entry
data FileType = Image | Executable | SourceCode | TextFile deriving (Show, Eq)

data Entry
  = File {name :: String, size :: Int, ftype :: FileType}
  | Directory {name :: String, entries :: [Entry]} deriving (Show, Eq)

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

countDirectories :: Entry -> Int
countDirectories (File _ _ _) = 0
countDirectories (Directory _ entries) = 1 + sum (map countDirectories entries)

isImage :: Entry -> Bool
isImage (File _ _ ftype) = if ftype == Image then True else False
isImage _ = False

filterImages :: Entry -> Entry
filterImages (Directory name childs) = Directory name [filterImages c | c<-childs,not(isImage c)]
filterImages file  = file

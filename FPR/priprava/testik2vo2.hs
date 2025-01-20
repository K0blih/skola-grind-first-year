data Color
    = Black
    | White
    | RGB Int Int Int  -- Červená, Zelená, Modrá složka
    | Mix [Color]      -- Mix více barev
    deriving (Show)

exampleColor :: Color
exampleColor = Mix[RGB 255 0 0, Black, Mix[White, RGB 1 2 3]]

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

countImages :: Entry -> Int
countImages (File _ _ ftype)
    | ftype == Image = 1
    | otherwise = 0
countImages (Directory _ entries) = sum (map countImages entries)

isImage :: Entry -> Bool
isImage (File _ _ ftype) = if ftype == Image then True else False
isImage _ = False

filterImages :: Entry -> Entry
filterImages (Directory name childs) = Directory name [filterImages c | c<-childs,not(isImage c)]
filterImages file  = file


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

-- Implementace funkce zipAll
zipAll :: Entry -> (Int -> Int) -> Entry
zipAll (File name size ftype) f = File (name ++ ".zip") (f size) ftype
zipAll (Directory name entries) f = Directory name (map (`zipAll` f) entries)

-- Testovací funkce pro změnu velikosti
adjustSize :: Int -> Int
adjustSize size = size `div` 2

-- Příklad použití
zippedRoot :: Entry
zippedRoot = zipAll root adjustSize
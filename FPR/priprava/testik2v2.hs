-- Úkol 1
-- Rekurzivní datový typ Entity
data Entity
  = Point Double Double -- Bod s dvojicí souřadnic (x, y)
  | Circle Double Double Int -- Kruh s centrem (x, y) a poloměrem
  | Group [Entity] -- Složený objekt (skupina entit)
  deriving (Show)


-- Příklad struktury Entity
exampleEntity :: Entity
exampleEntity =
  Group
    [ Point 1.0 2.0,
      Circle 3.0 4.0 10,
      Group
        [ Point 5.0 6.0,
          Circle 7.0 8.0 5
        ]
    ]

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
        ]
    ]

-- Příklad: countSize root  -> Výstup: 650
-- Funkce pro výpočet celkové velikosti souborů
countSize :: Entry -> Int
countSize (File _ size _) = size -- Pokud je to soubor, vrátíme jeho velikost
countSize (Directory _ entries) = sum (map countSize entries) -- Rekurzivně spočítáme všechny podadresáře

-- Úkol 3
-- Funkce pro vrácení seznamu adresářů a jejich velikostí
directorySizes :: Entry -> [(String, Int)]
directorySizes (File _ _ _) = [] -- Pokud je to soubor, nic nevrátí
directorySizes (Directory name entries) = (name, countSize (Directory name entries)) : concatMap directorySizes entries

-- Použití
-- directorySizes root  -> Výstup: [("root",650),("classes",300)]
-- Úkol 1
-- Definice datové struktury Company
data Company = Company
  {name :: String, employees :: Int, ownedCompanies :: [Company]} deriving (Show)

-- Příklad struktury
exampleCompany :: Company
exampleCompany =
  Company
    { name = "Hlavní Firma",employees = 50,ownedCompanies =
        [ Company {name = "Dceřiná Firma 1", employees = 30, ownedCompanies = []},
          Company {name = "Dceřiná Firma 2", employees = 20, ownedCompanies = []}
        ]
    }

-- Úkol 2
-- Definice typů FileType a Entry
data FileType = Image | Executable | SourceCode | TextFile deriving (Show)

data Entry
  = File {name' :: String, size :: Int, ftype :: FileType}
  | Directory {name' :: String, entries :: [Entry]} deriving (Show)

-- Příklad dat
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

-- Použití (např. kolik souborů je větších než 190 bajtů)
-- countLargeFiles 190 root  -> Výstup: 2
countLargerFiles :: Int -> Entry -> Int
countLargerFiles threshold (File _ size _) = if size > threshold then 1 else 0
countLargerFiles threshold (Directory _ entries) = sum (map (countLargerFiles threshold) entries)

-- Úkol 3
-- Funkce pro odstranění souborů s daným názvem
removeFile :: String -> Entry -> Entry
removeFile target (Directory name entries) = Directory name (map (removeFile target) (filter notTarget entries)) where
    notTarget (File n _ _) = n /= target
    notTarget _ = True
removeFile _ file = file -- Neměnit jiné typy souborů nebo složek

-- Použití (např. odstranit všechny soubory jménem "notes-fp.txt")
-- removeFile "notes-fp.txt" root
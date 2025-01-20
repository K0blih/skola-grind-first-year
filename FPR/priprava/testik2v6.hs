-- data Items
--     = Item {name' :: String, price :: Int}
--     | Section {name' :: String, item_list :: [Items], under :: [Items]}

--nebo (ignoruj červené, funguje to když je to samotné)

data Item = Item {name' :: String, price :: Int} deriving (Show)
data Section = Section {name'' :: String, item_list :: [Item], under :: [Section]} deriving (Show)

-- Example items
item1 = Item {name' = "Apple", price = 1}
item2 = Item {name' = "Banana", price = 2}
item3 = Item {name' = "Milk", price = 3}
item4 = Item {name' = "Bread", price = 2}
item5 = Item {name' = "Cheese", price = 5}
item6 = Item {name' = "Soap", price = 4}
item7 = Item {name' = "Shampoo", price = 6}

-- Example sections
produceSection = Section {name'' = "Produce", item_list = [item1, item2], under = []}
dairySection = Section {name'' = "Dairy", item_list = [item3, item5], under = []}
bakerySection = Section {name'' = "Bakery", item_list = [item4, item3], under = []}
cleaningSection = Section {name'' = "Cleaning Supplies", item_list = [item6, item7], under = []}

-- Main store section
-- store :: Section
store = Section {
    name'' = "Main Store",
    item_list = [item4],
    under = [bakerySection]
}

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

removeFile :: String -> Entry -> Entry
removeFile target (Directory name entries) =
  Directory name (map (removeFile target) (filter notTarget entries))
  where
    notTarget (File n _ _) = n /= target
    notTarget _ = True
removeFile _ file = file -- Neměnit jiné typy souborů nebo složek

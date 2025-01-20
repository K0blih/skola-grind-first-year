-- data Company = Name { name :: String }
--              | Employees { count :: Int }
--              | OwnerOf { children :: [Company] }
--              deriving (Show)

-- example1 :: Company
-- example1 = 
--     OwnerOf [
--         Name "Penis",
--         Employees 20,
--         OwnerOf [
--             Name "Kokot",
--             Employees 5
--         ]
--     ]

-- ---------------------------------------------------------

-- data FileType = Image 
--               | Executable 
--               | SourceCode 
--               | TextFile
--               deriving (Show)

-- data Entry = File { name :: String, size :: Int, ftype :: FileType }
--            | Directory { name :: String, entries :: [Entry] }
--            deriving (Show)

-- root :: Entry
-- root = Directory "root"
--     [ File "logo.jpg" 5000 Image,
--       Directory "classes"
--         [ File "notes-fpr.txt" 200 TextFile,
--           File "presentation.jpg" 150 Image,
--           File "first_test.hs" 20 SourceCode
--         ]
--     ]

-- countLargerFiles :: Int -> Entry -> Int
-- countLargerFiles x (File _ size _)
--  | size > x = 1
--  | otherwise = 0
-- countLargerFiles x (Directory _ entries) = sum (map (countLargerFiles x) entries)

-- -----------------------------------------------------------

-- removeFile :: String -> Entry -> Entry
-- removeFile delName (Directory x entries) = Directory x [removeFile delName a | a <- entries, name a /= delName]
-- removeFile _ e = e

-- -------------------------------------------------------------------------------------------------------------------------------------------------

-- data Entity = Point { x :: Double, y :: Double }
--             | Circle { sX :: Double, sY :: Double, r :: Int}
--             | Box { entities :: [Entity] }
--             deriving (Show)

-- example2 :: Entity
-- example2 =
--   Box [
--     Point 10 7.5,
--     Circle 10 7.5 5,
--     Box [
--       Point 10 7.5,
--       Circle 10 7.5 5
--     ]
--   ]

-- ----------------------------------------------------------------

-- data FileType = Image 
--               | Executable 
--               | SourceCode 
--               | TextFile
--               deriving (Show)

-- data Entry = File { name :: String, size :: Int, ftype :: FileType }
--            | Directory { name :: String, entries :: [Entry] }
--            deriving (Show)

-- root :: Entry
-- root = Directory "root"
--     [ File "logo.jpg" 5000 Image,
--       Directory "classes"
--         [ File "notes-fpr.txt" 200 TextFile,
--           File "presentation.jpg" 150 Image,
--           File "first_test.hs" 20 SourceCode
--         ]
--     ]

-- countSize :: Entry -> Int
-- countSize (File _ size _) = size
-- countSize (Directory _ entries) = sum (map countSize entries)

-- directorySizes :: Entry -> [(String, Int)]
-- directorySizes (File _ _ _) = []
-- directorySizes (Directory name entries) = (name, sum (map countSize entries)) : concatMap directorySizes entries

--------------------------------------------------------------------

-- data FileType = Image 
--               | Executable 
--               | SourceCode 
--               | TextFile
--               deriving (Show)

-- data Entry = File { name :: String, size :: Int, ftype :: FileType }
--            | Directory { name :: String, entries :: [Entry] }
--            deriving (Show)

-- root :: Entry
-- root = Directory "root"
--     [ File "logo.jpg" 5000 Image,
--       Directory "classes"
--         [ File "notes-fpr.txt" 200 TextFile,
--           File "presentation.jpg" 150 Image,
--           File "first_test.hs" 20 SourceCode
--         ]
--     ]

-- countLargerFiles :: Int -> Entry -> Int
-- countLargerFiles x (File _ size _) = if size > x then 1 else 0
-- countLargerFiles x (Directory _ entries) = sum (map (countLargerFiles x) entries)

-- removeFile :: String -> Entry -> Entry
-- removeFile fileName (Directory x entries) = Directory x [removeFile fileName a | a <- entries, name a /= fileName]
-- removeFile _ x = x

-- countSize :: Entry -> Int
-- countSize (File _ size _) = size
-- countSize (Directory _ entries) = sum (map countSize entries)

-- directorySizes :: Entry -> [(String, Int)]
-- directorySizes (File _ _ _) = []
-- directorySizes (Directory name entries) = (name, countSize (Directory name entries)) : concatMap directorySizes entries

-- data FileType = Image 
--               | Executable 
--               | SourceCode 
--               | TextFile
--               deriving (Show)

-- data Entry = File { name :: String, size :: Int, ftype :: FileType }
--            | Directory { name :: String, entries :: [Entry] }
--            deriving (Show)

-- root :: Entry
-- root = Directory "root"
--     [ File "logo.jpg" 5000 Image,
--       Directory "classes"
--         [ File "notes-fpr.txt" 200 TextFile,
--           File "presentation.jpg" 150 Image,
--           File "first_test.hs" 20 SourceCode,
--           Directory "empty1" []
--         ]
--     ]

-- countEmptyDirectories :: Entry -> Int
-- countEmptyDirectories (File _ _ _) = 0
-- countEmptyDirectories (Directory _ entries)
--  | null entries = 1 + sum (map countEmptyDirectories entries)
--  | otherwise = sum (map countEmptyDirectories entries)

-- getFiles :: Entry -> String -> [String]
-- getFiles (File name _ _) suffix = if drop (length name - length suffix) name == suffix then [name] else []
-- getFiles (Directory _ entries) suffix = concatMap (`getFiles` suffix) entries

data FileType = Image 
              | Executable 
              | SourceCode 
              | TextFile
              deriving (Show)

data Entry = File { name :: String, size :: Int, ftype :: FileType }
           | Directory { name :: String, entries :: [Entry] }
           deriving (Show)

root :: Entry
root = Directory "root"
    [ File "logo.jpg" 5000 Image,
      Directory "classes"
        [ File "notes-fpr.txt" 200 Image,
          File "presentation.jpg" 150 Image,
          File "first_test.hs" 20 SourceCode
        ]
    ]

countDirectories :: Entry -> Int
countDirectories (File _ _ _) = 0
countDirectories (Directory _ entries) = 1 + sum (map countDirectories entries)

filterImagesHelper :: Entry -> Bool
filterImagesHelper (File _ _ Image) = False
filterImagesHelper _ = True


filterImages :: Entry -> Entry
filterImages (Directory x entries) = Directory x [filterImages a | a <- entries, filterImagesHelper a]
filterImages x = x

countImages :: Entry -> Int
countImages (File _ _ Image) = 1
countImages (File _ _ _) = 0
countImages (Directory _ entries) = sum (map countImages entries)

fullNames :: Entry -> [String]
fullNames entry = fullNamesHelper entry ""

fullNamesHelper :: Entry -> String -> [String]
fullNamesHelper (File name _ _) path = [path ++ "/" ++ name]
fullNamesHelper (Directory name entries) path = concatMap (`fullNamesHelper`(path ++ "/" ++ name)) entries

countFiles :: Entry -> Int
countFiles (File _ _ _) = 1
countFiles (Directory _ entries) = sum (map countFiles entries)

removeFiles :: String -> Entry -> Entry
removeFiles suffix (Directory x entries) = Directory x [removeFiles suffix a | a <- entries, suffix /= drop (length (name a) - length suffix) (name a)]
removeFiles _ file = file

zipAll :: Entry -> (Int -> Int) -> Entry
zipAll (File name size ftype) f = File (name ++ ".zip") (f size) ftype
zipAll (Directory name entries) f = Directory name [ zipAll a f | a <- entries]

-- Testovací funkce pro změnu velikosti
adjustSize :: Int -> Int
adjustSize size = size `div` 2

-- Příklad použití
zippedRoot :: Entry
zippedRoot = zipAll root adjustSize
-- data Element
--     = Button {name' :: String, text :: String}
--     | Text {text :: String}
--     | Panel {children :: [Element]} deriving(Show)

-- data FileType = Image | Executable | SourceCode | TextFile deriving (Show, Eq)

-- data Entry
--   = File {name :: String, size :: Int, ftype :: FileType}
--   | Directory {name :: String, entries :: [Entry]} deriving (Show, Eq)

-- --příklad datové struktury
-- -- root :: Entry
-- root =
--   Directory
--     "root"
--     [ File "notes-fp.txt" 200 TextFile,
--       File "presentation.jpg" 150 Image,
--       Directory
--         "classes"
--         [ File "first_test.hs" 300 SourceCode
--         ]
--     ]

-- countImages :: Entry -> Int
-- countImages (File _ _ ftype) = if ftype == Image then 1 else 0
-- countImages (Directory _ entries) = sum (map countImages entries)

-- fullNames :: Entry -> [String]
-- fullNames entry = fullNamesHelper entry ""

-- fullNamesHelper :: Entry -> String -> [String]
-- fullNamesHelper (File name _ _) path = [path ++ "/" ++ name]
-- fullNamesHelper (Directory name entries) path = concatMap (\entry -> fullNamesHelper entry (path ++ "/" ++ name)) entries

data Point = Point {column::Int,row::Int} deriving (Show)

data Position = Position {leftTopCorner :: Point, width :: Int, height :: Int} deriving (Show)

data Component
  = TextBox {name :: String, position :: Position, text :: String}
  | Button {name :: String, position :: Position, text :: String}
  | Container {name :: String, children :: [Component]}
  deriving (Show)
-- As an example, we can use following data structure.

gui :: Component
gui =
  Container "My App"
    [ Container "Menu"
        [ Button "btn_new" (Position (Point 0 0) 100 20) "New"
        ],
      Container "Footer" []
    ]

insertInto :: Component -> String -> Component -> Component
insertInto (Container cName children ) toName element = if cName == toName then Container cName (children++[element]) else Container cName [insertInto c toName element  |c<-children]
    -- | cName == toName = Container cName (children++[element]) 
    -- | otherwise = Container cName [insertInto c toName element  |c<-children]
insertInto x toName element = x
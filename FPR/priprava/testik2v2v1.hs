data DynamicTree a 
    = Leaf a 
    | Branch a [DynamicTree a]
    deriving (Show)

tree :: DynamicTree Int
tree = Branch 1 [Branch 2 [Branch 3 [Branch 4 [Leaf 1]], Branch 5[]], Branch 3 [], Leaf 2]

data Component = TextBox {name :: String, text :: String}
    | Button {name :: String, value :: String}
    | Container {name :: String, children :: [Component]} deriving(Show)

gui :: Component
gui = Container "My App" [
        Container "Menu" [
            Button "btn_new" "New",
            Button "btn_open" "Open",
            Button "btn_close" "Close"],
        Container "Body" [TextBox "textbox_1" "Some text goes here"],
        Container "Footer" []]

guiDepth :: Component -> Int
guiDepth (TextBox _ _) = 1
guiDepth (Button _ _) = 1
guiDepth (Container _ children) = 1 + (if null children then 0 else maximum (map guiDepth children))

justContainer :: Component -> Component
justContainer (TextBox _ _) = Container "Empty" []
justContainer (Button _ _) = Container "Empty" []
justContainer (Container name children) = Container name (filter hasChildren (map justContainer children)) where
    hasChildren (Container _ []) = False
    hasChildren _ = True


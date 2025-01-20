data Company = Company
  { name :: String, -- Název firmy
    employees :: Int, -- Počet zaměstnanců
    ownedCompanies :: [Company] -- Seznam dceřiných firem
  }
  deriving (Show)

data Article = Text String
    | Section String [Article] deriving (Show)

myArticle :: Article
myArticle = Section "Document" [
        Section "Introduction" [
            Text "My Introuction",
            Section "Notation" [Text "alpha beta gamma"]],
        Section "Methods" [
            Section "Functional Programming" [Text "FPR"],
            Section "Logical Programming" [Text "LPR"]],
        Section "Results" [Text "All is great"]]

allSectionNames :: Article -> [String]
allSectionNames (Text _) = []
allSectionNames (Section name children) = name : concatMap allSectionNames children

articleDepth :: Article -> Int
articleDepth (Text _) = 0
articleDepth (Section _ children) = 1 + maximum (map articleDepth children)


type Maze = [String]

sample1 :: Maze
sample1 = ["*********",
           "* *   * *",
           "* * * * *",
           "* * * * *",
           "*   *   *",
           "******* *",
           "        *",
           "*********"]

printMaze :: Maze -> IO ()
printMaze x = putStr (concat (map (++"\n") x))
-- printMaze sample1 

getFromMaze :: Maze -> (Int, Int) -> Char
getFromMaze maze (r, c) = (maze !! r) !! c
-- getFromMaze  sample1  (1,1)

putIntoMaze :: Maze -> [(Int,Int,Char)] -> Maze
putIntoMaze maze updates = foldl splitMaze maze updates
-- printMaze(putIntoMaze sample2 [(0,0,'1'),(6,6,'2'),(0,6,'3')]) 

splitMaze :: Maze -> (Int, Int, Char) -> Maze
splitMaze maze (r,c,char) = take r maze ++ [placeChar (maze !! r) (r,c,char)] ++ drop (r+1) maze

placeChar :: String -> (Int, Int, Char) -> String
placeChar maze (r,c,char) = take c maze ++ [char] ++ drop (c+1) maze

getPart :: Maze -> (Int, Int) -> (Int, Int) -> Maze
getPart maze (startRow, startCol) (height, width) = [take width (drop startCol row) | row <- take height (drop startRow maze)]
-----

getPath :: (Int, Int) -> String -> [(Int, Int, Char)]
getPath (startRow, startCol) path = scanl move (startRow, startCol, '+') path where
    move (row, col, _) 'd' = (row + 1, col, '|')
    move (row, col, _) 'u' = (row - 1, col, '|')
    move (row, col, _) 'l' = (row, col - 1, '-')
    move (row, col, _) 'r' = (row, col + 1, '-')

markPath :: Maze -> (Int, Int) -> [Char] -> Maze
markPath maze (startRow, startCol) path = putIntoMaze maze (getPath (startRow, startCol) path)
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

putIntoMaze :: Maze -> [(Int,Int,Char)] -> Maze
putIntoMaze maze updates = foldl splitMaze maze updates
-- printMaze(putIntoMaze sample2 [(0,0,'1'),(6,6,'2'),(0,6,'3')]) 

splitMaze :: Maze -> (Int, Int, Char) -> Maze
splitMaze maze (r,c,char) = take r maze ++ [placeChar (maze !! r) (r,c,char)] ++ drop (r+1) maze

placeChar :: String -> (Int, Int, Char) -> String
placeChar maze (r,c,char) = take c maze ++ [char] ++ drop (c+1) maze

getPath :: Maze -> (Int, Int) -> (Int, Int) -> [(Int,Int,Char)]
getPath maze (startRow, startCol) (endRow, endCol) = bfs [(startRow, startCol, '+')] where
    bfs ((r, c, char):queue)
      | (r, c) == (endRow, endCol) = queue
      | otherwise = bfs (queue ++ [(nr, nc, char) | (nr, nc, '+') <- [(r-1, c, '+'), (r+1, c, '+'), (r, c-1, '+'), (r, c+1, '+')], nr >= 0, nr < length maze, nc >= 0, nc < length (head maze), maze !! nr !! nc /= '*', notElem (nr, nc, '+') (map (\(x, y, _) -> (x, y, '+')) queue)])
    
makePath :: Maze -> (Int, Int) -> (Int, Int) -> Maze
makePath maze (startRow, startCol) (endRow, endCol) = putIntoMaze maze (getPath maze (startRow, startCol) (endRow, endCol))

type Maze = [String]

sample1 :: Maze
sample1 = ["*********",
           "* *   * *",
           "* * * * *",
           "* * * * *",
           "* . *   *",
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

getPart :: Maze -> (Int, Int) -> (Int, Int) -> Maze
getPart maze (startRow, startCol) (height, width) = [take width (drop startCol row) | row <- take height (drop startRow maze)]
-- printMaze(getPart sample1 (1,1) (7,7))

findPositions :: Maze -> Char -> [(Int, Int)]
findPositions maze char = [(r, c) | r <- [0..length maze - 1], c <- [0..length (maze !! 0) - 1], maze !! r !! c == char ]
-- findPositions sample4 'e'

getPath :: (Int, Int) -> [(Char,Int)] -> [(Int, Int, Char)]
getPath (startRow, startCol) dirschars = scanl move (startRow, startCol, '.') dirschars where
    move (row, col, _) ('d', len) = (row + len, col, '.')
    move (row, col, _) ('u', len) = (row - len, col, '.')
    move (row, col, _) ('l', len) = (row, col - len, '.')
    move (row, col, _) ('r', len) = (row, col + len, '.')

fillMaze :: Maze -> (Int, Int) -> [(Char,Int)] -> Maze
fillMaze maze (startRow, startCol) dirschars = putIntoMaze maze (getPath (startRow, startCol) dirschars)

getMap :: Maze -> (Int, Int) -> Maze
getMap maze (row, col) = getPart maze (row-1, col-1) (3, 3)

miniMaps :: Maze -> (Int, Int) -> [(Char,Int)] -> Maze
miniMaps maze start dirs = let
    filledMaze = fillMaze maze start dirs -- Fill the maze with the path
    positions = findPositions filledMaze '.' -- Find all positions of '.'
    subgrids = map (getMap filledMaze) positions -- Get 3x3 subgrids around each position
    in concat subgrids 

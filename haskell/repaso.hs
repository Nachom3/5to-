--4. Escriba las siguientes funciones combinando map, filter y foldl/foldr, segun sea necesario:
--a. Una funcion suma cubos que dada una lista de numeros list, devuelva la suma de los cubos de los numeros positivos de list.
--b. Una funcion long lists que toma una lista de listas y devuelve true si y solo si las longitudes de todas las sublistas son mayores a 4.
--c. Una funcion prod positivo que dada una lista list compuesta por listas de n´umeros devuelva otra lista que contenga ´unicamente las sublistas de list las cuales al multiplicar todos sus elementos obtengamos un resultado positivo.


dovelverreal :: [Float] -> [Float]
dovelverreal xs = filter (\x-> x > 0) xs


devolverstring :: [String] -> [String]
devolverstring xs = filter (\x -> length x < 4) xs

longlist :: [[a]] -> Bool
longlist xs = if length (filter (\x -> length x > 4) xs) == length xs then True  else False

longlist2 :: [[a]] -> Bool
longlist2 xs = foldr (\x acc-> (length x > 4) && acc) True xs

prodpositiv :: [[Int]] -> [[Int]]
prodpositiv xs = filter (\x-> foldr (*) 1 x > 0) xs
data Meses = Enero | Febero | Marzo | Abril | Mayo | Junio | Julio | Agosto | Sepetiembre | Octubre | Noviembre | Diciembre

data Geometria = Circulo Float | Rectangulo Float Float 
   deriving (Show)
vacaciones :: Meses -> Bool
vacaciones Enero = True
vacaciones Febero = True
vacaciones Diciembre = True
vacaciones _ = False

perimetro :: Geometria -> Float
perimetro (Circulo r) = (2 * 3.14) * r
perimetro (Rectangulo x y) = 2 * x + 2 * y

escalar :: Float -> Geometria -> Geometria  
escalar x (Circulo r) = Circulo (r * x)

data Dinero = Pesos Float | Dolar Float | Cheque String
    deriving (Show)



cambio :: Dinero -> Dinero
cambio (Dolar x) = Pesos (x * 1200)
cambio (Pesos y) = Dolar (y / 1200) 
cambio (Cheque z)= (Cheque z)


data Nat = Zero | Succ Nat
    deriving (Show)

nat2int :: Nat -> Int
nat2int Zero = 0
nat2int (Succ x) = 1 + nat2int x

data List a = Nil | Cons a (List a)
  deriving (Show)

sumar :: List Int -> Int
sumar Nil = 0
sumar (Cons x xs) = x + sumar xs

data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr
  deriving (Show)

expresionEjemplo :: Expr
expresionEjemplo = Resta (Suma (Literal 1) (Literal 2)) (Suma (Literal 3) (Literal 4))

mostrar :: Expr -> String
mostrar (Literal x)   = show x
mostrar (Suma e1 e2)  = "(" ++ mostrar e1 ++ " + " ++ mostrar e2 ++ ")"
mostrar (Resta e1 e2) = "(" ++ mostrar e1 ++ " - " ++ mostrar e2 ++ ")"

evaluar :: Expr -> Int
evaluar (Literal x)   = x
evaluar (Suma e1 e2)  = evaluar e1 + evaluar e2
evaluar (Resta e1 e2) = evaluar e1 - evaluar e2

buscar :: Expr -> Int -> Bool
buscar (Literal x) y = x == y 
buscar (Suma e1 e2) y = buscar e1 y || buscar e2 y
buscar (Resta e1 e2) y = buscar e1 y || buscar e2 y 

list2alg :: [a] -> List a
list2alg [] = Nil
list2alg (x:xs) = Cons x (list2alg xs)

divisionSegura :: Float -> Float -> Maybe Float
divisionSegura _ 0 = Nothing
divisionSegura x y = Just (x / y)

type Resultado a = Either a String

llamarDivisión :: Float -> Float -> Resultado Float
llamarDivisión x y = case divisionSegura x y of
    Just r  -> Left r
    Nothing -> Right "Division por cero"


--data Nat = Zero | Succ Nat
--FOLD COOKED

foldnat :: (r ->r) -> r -> Nat -> r
foldnat f b Zero = b
foldnat f b (Succ n) = f (foldnat f b n)

sumar2 :: Nat -> Int
sumar2 (Succ x) = foldnat (+ 1) 0 (Succ x)

-- data List a = Nil | Cons a (List a)

foldlist :: (a->b -> b) -> b -> List a -> b
foldlist f b Nil = b
foldlist f b (Cons x xs) = f x (foldlist f b xs)

sumar22 :: List Int -> Int
sumar22 xs = foldlist (+) 0 xs

--data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr\

foldExpr :: (Int -> r) -> (r -> r -> r) -> (r -> r -> r) -> Expr -> r
foldExpr f _ _ (Literal x)   = f x
foldExpr f g h (Suma e1 e2)  = g (foldExpr f g h e1) (foldExpr f g h e2)
foldExpr f g h (Resta e1 e2) = h (foldExpr f g h e1) (foldExpr f g h e2)

evaluarFoldExpr :: Expr -> Int
evaluarFoldExpr = foldExpr id (+) (-)

-- data Nat = Zero | Succ Nat
-- data List a = Nil | Cons a (List a)

natSize :: List a -> Nat
natSize Nil = Zero
natSize (Cons _ xs) = Succ (natSize xs)

dup :: List a -> List a
dup (Cons x xs) = foldlist (\a b -> Cons a (Cons a b)) (Cons x (Cons x Nil)) xs

zipdup :: List a -> List (a, a)
zipdup = foldlist (\x l -> Cons (x, x) l) Nil



--data Nat = Zero | Succ Nat
--data List a = Nil | Cons a (List a)
--data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr\
concatList :: List a -> List a -> List a
concatList l r = foldlist Cons r l

flattenExpr :: Expr -> List Int
flattenExpr = foldExpr (\x -> Cons x Nil) concatList concatList

maxNumber :: Expr -> Int
maxNumber = foldExpr (\x-> id x) max max


--data Nat = Zero | Succ Nat
--data List a = Nil | Cons a (List a)
--data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr\

--foldnat :: (r ->r) -> r -> Nat -> r
--foldnat f b Zero = b
--foldnat f b (Succ n) = f (foldnat f b n)

repeat' :: a -> Nat -> List a
repeat' x = foldnat (\xs -> Cons x xs) Nil





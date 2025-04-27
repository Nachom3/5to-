data OpEd = Escribir Char | Borrar | Reemplazar Char

aplicar :: OpEd -> String -> String
aplicar (Escribir x) xs = xs ++ [x]
aplicar (Reemplazar x) xs = init xs ++ [x]
aplicar Borrar  xs = init xs


---foldList :: r -> (a -> r -> r) -> List a -> r
---foldList z f Nil = z
---foldList z f (Cons x xs) = f x (foldList z f xs)

snoc :: List a -> a -> List a
snoc xs x = foldList (Cons x Nil) Cons xs

reverseList :: List a -> List a
reverseList xs = foldList Nil (\x xs' -> xs' `snoc` x) xs

aplicarTodas :: List OpEd -> String -> String
aplicarTodas ops s = foldList s (\xs s' -> aplicar xs s') (reverseList ops)

--data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr\
--foldExpr :: (Int -> r) -> (r -> r -> r) -> (r -> r -> r) -> Expr -> r
--foldExpr f _ _ (Literal x)   = f x
--foldExpr f g h (Suma e1 e2)  = g (foldExpr f g h e1) (foldExpr f g h e2)
--foldExpr f g h (Resta e1 e2) = h (foldExpr f g h e1) (foldExpr f g h e2)

data Raro a = Nada | Algo a | Par (Raro a) (Raro a)

foldraro :: r -> (a-> r) -> (r->r->r) -> Raro a -> r
foldraro r f g Nada = r
foldraro r f g (Algo x) = f x
foldraro r f g (Par x y) = g (foldraro r f g x) (foldraro r f g y)


sumarRaro :: Raro Int -> Int
sumarRaro xs = foldraro 0 (\x'-> x') (+) xs


foldList :: r -> (a -> r -> r) -> List a -> r
foldList z f Nil = z
foldList z f (Cons x xs) = f x (foldList z f xs)

data List a = Nil | Cons a (List a)

class Bolsa b where
    agregar :: a -> b a -> b a
    buscar :: Eq a => a -> b a -> Bool
    quitar :: Eq a => a -> b a -> b a
    cantidad :: b a -> Int

instance Bolsa List where
    agregar :: a -> List a -> List a
    agregar x xs = Cons x xs

    buscar :: Eq a => a -> List a -> Bool
    buscar x l = foldList False (\y b->if x == y then True else b) l

    quitar :: Eq a => a -> List a -> List a
    quitar x l = foldList Nil (\y acc -> if x == y then acc else Cons y acc) l

    cantidad :: List a -> Int 
    cantidad l = foldList 0 (\_ n -> n + 1) l



fun :: Ord b => (a -> b) -> a -> b -> b -> b
fun g a s d = if g a == s then s else if g a < s then g a 
                                                 else d


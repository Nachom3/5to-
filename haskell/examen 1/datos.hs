data Nat = Zero | Succ Nat
data List a = Nil | Cons a (List a)
data Expr = Literal Int |
            Suma Expr Expr |
            Resta Expr Expr


valor :: Nat -> Int
valor Zero = 0
valor (Succ n) = 1 + valor n

foldNat :: (r -> r) -> r -> Nat -> r
foldNat f b Zero = b
foldNat f b (Succ n) = f (foldNat f b n)

valorConFold :: Nat -> Int
valorConFold n = foldNat (1 +) 0 n


suma :: List Int -> Int
suma Nil = 0
suma (Cons n y) = n + suma y

foldList :: (a ->  r ->  r) ->  r ->  List a ->  r
foldList f b Nil = b
foldList f b (Cons a l) = f a (foldList f b l)

sumaConFold xs = foldList (\a r -> a + r) 0 xs

evaluar (Literal n) = n
evaluar (Suma e1 e2) = (evaluar e1) + (evaluar e2)
evaluar (Resta e1 e2) = (evaluar e1) - (evaluar e2)

foldExpr :: (r -> r -> r) -> (r -> r -> r) -> (Int -> r) -> Expr -> r
foldExpr s r l (Literal n) = l n
foldExpr s r l (Suma e1 e2) = s (foldExpr s r l e1) (foldExpr s r l e2)
foldExpr s r l (Resta e1 e2) = r (foldExpr s r l e1) (foldExpr s r l e2)

foldexpr2 x = foldExpr (+) (-) id x
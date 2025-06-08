data OpEd =  Escribir Char | Borrar | Reemplazar Char



aplicar :: OpEd -> String ->String
aplicar (Escribir x) ys = ys ++ [x]
aplicar Borrar xs = init xs 
aplicar (Reemplazar x) ys = init ys ++ [x]

snoc :: List a -> a -> List a
snoc xs x = foldList (Cons x Nil) Cons xs

reverseList :: List a -> List a
reverseList xs = foldList Nil (\x xs' -> xs' `snoc` x) xs


data List a = Nil | Cons a (List a)

foldList :: r -> (a -> r -> r) -> List a -> r
foldList z f Nil = z
foldList z f (Cons x xs) = f x (foldList z f xs)

aplicarTodas :: List OpEd -> String -> String
aplicarTodas l ys = foldList ys (\a acc-> aplicar a acc) (reverseList l)
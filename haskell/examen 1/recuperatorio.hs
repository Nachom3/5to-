data CType = IntT Int | Ptr CType


foldPtr :: (Int -> r) -> (r -> r) -> CType -> r
foldPtr r _ (IntT x) = r x
foldPtr r f (Ptr t) = f (foldPtr r f t)

accesosRAM :: CType -> Int 
accesosRAM x = foldPtr (+ 1) (\x'-> x' + 1) x

data Nat = Zero | Succ Nat
    deriving Show

class MyEnum a where
    succ2 :: a -> a
    toEnum2 :: Int -> a
    fromEnum2 :: a -> Int

instance MyEnum Nat where 
    succ2 :: Nat -> Nat
    succ2 x = foldnat Succ (Succ Zero) x

    toEnum2 :: Int -> Nat 
    toEnum2 0 = Zero
    toEnum2 x = Succ (toEnum2(x-1))
    
    fromEnum2 :: Nat -> Int
    fromEnum2 Zero = 0
    fromEnum2 xy = foldnat (1+) 0 xy


foldnat :: (r ->r) -> r -> Nat -> r
foldnat f b Zero = b
foldnat f b (Succ n) = f (foldnat f b n)

enumFrom2 :: MyEnum a => a -> [a]
enumFrom2 x = x : enumFrom2 (succ2 x)

fun t s b c = t == s || b == c
fun :: (Eq a, Eq b) => a -> a -> b -> b -> Bool
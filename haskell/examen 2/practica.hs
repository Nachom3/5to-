-- Para hacer los ejercicios, primero definimos todo
-- Ejercicio 1
-- Dar la instancia: Stack Pila
class Stack s where
  empty :: s a
  push :: a -> s a -> s a
  top :: s a -> a    
  pop :: s a -> s a
  isEmpty :: s a -> Bool

data Pila a = PTop a (Pila a) | PEmpty deriving (Show, Eq)

instance Stack Pila where
  empty :: Pila a
  empty = PEmpty

  push :: a -> Pila a -> Pila a
  push = PTop

  top :: Pila a -> a
  top (PTop x _) = x

  pop :: Pila a -> Pila a
  pop (PTop _ p) = p

  isEmpty :: Pila a -> Bool
  isEmpty PEmpty = True
  isEmpty _ = False

-- Dar la instancia: Queue FastQueue
-- se queja si usamos los mismos nombres que la clase anterior
class Queue q where
  qempty :: q a
  enqueue :: a -> q a -> q a
  front :: q a -> a
  dequeue :: q a -> q a
  qisEmpty :: q a -> Bool

data FastQueue a = FQ ([a], [a]) deriving (Show, Eq)

instance Queue FastQueue where
  qempty :: FastQueue a
  qempty = FQ ([], [])

  enqueue :: a -> FastQueue a -> FastQueue a
  enqueue x (FQ (ins, outs)) = FQ (x:ins, outs)

  front :: FastQueue a -> a
  front (FQ (ins, [])) = front (FQ ([], reverse ins)) -- es lenta por cosas de lenguaje funcional :^)
  front (FQ (ins, outs)) = head outs

  dequeue :: FastQueue a -> FastQueue a
  dequeue (FQ (ins, [])) = dequeue (FQ ([], reverse ins))
  dequeue (FQ (ins, outs)) = FQ (ins, tail outs)

  qisEmpty :: FastQueue a -> Bool
  qisEmpty (FQ ([], [])) = True
  qisEmpty _ = False

-- Dar la instancia: PriorityQueue []
-- se queja si usamos los mismos nombres que la clase anterior
class PriorityQueue pq where
  pqempty :: Ord a => pq a
  pqenqueue :: Ord a => a -> pq a -> pq a
  pqfront :: Ord a => pq a -> a
  pqdequeue :: Ord a => pq a -> pq a
  pqisEmpty :: Ord a => pq a -> Bool

instance PriorityQueue [] where
  pqempty :: Ord a => [a]
  pqempty = []

  pqenqueue :: Ord a => a -> [a] -> [a]
  pqenqueue x [] = [x]
  pqenqueue x (y:ys)
    | x <= y = x:y:ys
    | otherwise = y : (pqenqueue x ys)

  pqfront :: Ord a => [a] -> a
  pqfront = head

  pqdequeue :: Ord a => [a] -> [a]
  pqdequeue = tail

  pqisEmpty :: Ord a => [a] -> Bool
  pqisEmpty [] = True
  pqisEmpty _ = False

-- isEmpty empty para cualquier stack
-- Haskell no lo logra deducir, simplificamos
-- determinando de qué stack estamos hablando
verificarStack :: (Eq a) => Pila a -> a -> Bool
verificarStack stk x =
  top (push x stk) == x &&
  pop (push x stk) == stk &&
  isEmpty (empty :: Pila a) &&
  not (isEmpty (push x stk))

-- Ídem
verificarQueue :: (Eq a) => FastQueue a -> a -> a -> Bool
verificarQueue q x y =
  front (enqueue x q) == x &&
  front (enqueue x (enqueue y q)) == front (enqueue y q) &&

  dequeue (enqueue x q) == qempty &&
  dequeue (enqueue x (enqueue y q)) == enqueue x (dequeue (enqueue y q)) &&

  qisEmpty (qempty :: FastQueue a) &&
  not (qisEmpty (enqueue x q))


toString :: Pila Char -> String
toString PEmpty = []
toString (PTop x xs) =  toString xs ++ [x]

toStack :: String -> Pila Char
toStack [] = PEmpty
toStack (x:xs) = (push x (toStack xs))

fromStack :: Pila Char -> String
fromStack PEmpty = []
fromStack stk = top stk : fromStack (pop stk)

esPalindromo :: String -> Bool
esPalindromo str = fromStack (toStack str) == str

intercalaColas :: Pila a -> Pila a -> Pila a
intercalaColas stk1 PEmpty = stk1
intercalaColas PEmpty stk2 = stk2
intercalaColas stk1 stk2 = push (top stk1) (push (top stk2) (intercalaColas (pop stk1) (pop stk2)))
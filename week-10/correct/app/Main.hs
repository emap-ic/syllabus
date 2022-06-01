module Main where

import Lib

import Test.QuickCheck

data Expr
  = Val Int
  | Add Expr Expr
  deriving (Show)


instance Arbitrary Expr where
  arbitrary =
    oneof
      [ do (Val <$> arbitrary)
      , do x <- arbitrary
           y <- arbitrary
           return (Add x y)
      ]
         
data Op
  = PUSH Int
  | ADD
  deriving (Show)


eval :: Expr -> Int
eval (Val n) = n
eval (Add x y) = eval x + eval y

comp :: Expr -> [Op]
comp (Val n) = [PUSH n]
comp (Add x y) = comp x ++ comp y ++ [ADD]

exec :: [Op] -> [Int] -> [Int]
exec ((PUSH n):c) s = exec c (n : s)
exec (ADD:c) (m:n:s) = exec c (n + m : s) 
exec _ s = s


correct e = exec (comp e) [] == [eval e]

preverse :: [Int] -> Bool
preverse xs = reverse (reverse xs) == xs


primes = filterPrime [2 ..]
  where
    filterPrime (p:xs) = p : filterPrime [x | x <- xs, x `mod` p /= 0]


main :: IO ()
main = someFunc

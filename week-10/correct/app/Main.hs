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
      [ do
          x <- arbitrary
          return (Val x)
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

prop_reverse :: [Int] -> Bool
prop_reverse xs = reverse (reverse xs) == xs


main :: IO ()
main = someFunc



inductive Palindrome : List  α → Prop where
 | nil :  Palindrome []
 | single : (a : α) → Palindrome [a]
 | sandwich : (a : α) → Palindrome as → Palindrome ([a] ++ as ++ [a])


theorem palindrome_reverse (h : Palindrome as) : Palindrome as.reverse := by 
 induction h with 
   | nil => exact Palindrome.nil
   | single a => exact Palindrome.single a
   | sandwich a h ih => simp; exact Palindrome.sandwich _ ih


theorem reverse_eq_of_palindrome (h : Palindrome as) : as.reverse = as := by 
 induction h with 
  | nil => rfl
  | single a => rfl
  | sandwich a h ih => simp [ih]


example (h : Palindrome as) : Palindrome as.reverse := by
 simp [reverse_eq_of_palindrome h, h]


def List.last : (as : List α) → as ≠ [] → α 
 | [a]           , _ => a
 | a₁ :: a₂ :: as, _ => (a₂ :: as).last (by simp)



/-
def map (f: a → b) : List a → List b
 | [] => []
 | (x :: xs) => f x :: map f xs

def foldr (f : α → β → β) (init : β) : List α → β
  | []     => init
  | a :: l => f a (foldr f init l)
-/

open List

#reduce List.map (λ x : Nat => x + 10) [1,2,3]
#reduce List.foldr (λ x y => x + y) 0 [1,2,3]

example (a b c : Type) (f : b → c) (g : a → b) (xs : List a) :
 (map f ∘ map g) xs = map (f ∘ g) xs := by
  unfold Function.comp
  induction xs with
   | nil => simp [map]
   | 
  
  
   
  

import tactic
import data.list
import data.real.basic 
import init.function
 
open function

def map {a b : Type} : (a → b) → list a → list b
| f [] := []
| f (x :: xs) := f x :: map f xs

#reduce map (λ x : ℕ, x + 10) [1,2,3,4]

def foldr {a b: Type} : (a → b → b) → b → list a → b 
| f e [] := e
| f e (x :: xs) := f x (foldr f e xs)

def foldl {a b : Type} : (b → a → b) → b → list a → b
| f e [] := e
| f e (x :: xs) := foldl f (f e x) xs

#reduce foldr (λ x y, x + y) 0 [1,2,3]
#reduce foldl (λ x y, x + y) 0 [1,2,3]

example : foldr (λ x y : ℕ, x + y) (0 : ℕ) [1,2,3] = 6 :=
begin
 rw foldr,
 rw foldr,
 rw foldr,
 rw foldr,
end

example (a b c : Type) (f : b → c) (g : a → b) (xs : list a) : 
 (map f ∘ map g) xs = map (f ∘ g) xs :=
begin
 unfold comp,
 induction xs with xa xha xhi,
 repeat { rw map },

 simp, 
 rw ← xhi,
end

example (a b c : Type) (f : b → c) (g : a → b) :
 (map f ∘ map g) = map (f ∘ g) :=
begin
 unfold comp,
 funext,
 induction x with xa xha xhi,
 repeat { rw map },
 { simp,
   rw ← xhi, },
end

#reduce list.append [1,2] [3,4]

example {a : Type} {xs ys zs : list a} : (xs ++ ys) ++ zs = xs ++ (ys ++ zs) :=
begin
 induction xs with b hb,
 apply list.append.equations._eqn_1,
 simp [xs_ih],
end

def reverse { a : Type } : list a -> list a
| []      := []
| (x::xs) := (reverse xs) ++ [x]


lemma rev_aux {a : Type } (x : a) (ys : list a) : reverse (ys ++ [x]) = x :: reverse ys :=
begin
 induction ys with b bs hi,
 simp [reverse, append],

 rw list.cons_append,
 rw reverse,
 rw hi,
 rw reverse.equations._eqn_2,
 rw list.cons_append,
end

theorem rev_rev_eq {a : Type} : ∀ xs : list a, reverse (reverse xs) = xs :=
begin
 intro xs,
 induction xs with b bs hi,
 simp [reverse,append],

 rw reverse,
 rw rev_aux,
 rw hi,
end

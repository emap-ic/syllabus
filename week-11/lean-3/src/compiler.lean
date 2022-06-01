import tactic

namespace compiler

/- expressions are values and add-expressions -/
inductive Expr
| Val : ℕ -> Expr
| Add : Expr -> Expr -> Expr
open Expr

#check Add (Val 34) (Val 12)

/-- evaluate an expression directly -/
@[simp] def eval : Expr -> ℕ
| (Val n) := n
| (Add a b) := eval a + eval b

#reduce eval $ Add (Val 34) (Val 12) 

/-
  we'll compile our expressions to instructions of a stack machine
  which supports push and add operations
-/
inductive Instr
| PUSH : ℕ -> Instr
| ADD : Instr
open Instr

/-- compile an expression to an instruction list -/
@[simp] def compile : Expr -> list Instr
| (Val n) := [PUSH n]
| (Add a b) := compile a ++ compile b ++ [ADD]

#reduce compile $ Add (Val 34) (Val 12)

/-- execute a list of instructions on a stack -/
@[simp] def exec : list Instr -> list ℕ -> list ℕ
| ((PUSH n) :: rest) s := exec rest (n :: s)
| (ADD :: rest) (a :: b :: s) := exec rest ((a + b) :: s)
| _ s := s

#reduce (exec ∘ compile) (Add (Val 34) (Val 12)) []
#reduce exec (compile $ (Add (Val 34) (Val 12))) []

/-- compiled expressions only add to the stack when `exec`d -/
@[simp] lemma exec_compile_concat (e : Expr) : 
  ∀ instrs stack,
   exec (compile e ++ instrs) stack = exec instrs (eval e :: stack) :=
begin
  induction e with n a b iha ihb,
  case Val {
    intros,
    simp,
  },
  case Add {
    intros,
    simp [iha, ihb, add_comm],
  }
end

#print exec_compile_concat

/-- exec (compile e) = eval e -/
theorem exec_compile_eq_eval (e : Expr) : exec (compile e) [] = [eval e] :=
by simpa using exec_compile_concat e [] []

end compiler

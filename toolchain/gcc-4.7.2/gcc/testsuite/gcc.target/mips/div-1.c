/* { dg-options "-O -mgp64 (-mips16)" } */
/* { dg-final { scan-assembler "\tddiv\t" } } */
/* { dg-final { scan-assembler "\tmflo\t" } } */
/* { dg-final { scan-assembler-not "\tmfhi\t" } } */

typedef int DI __attribute__((mode(DI)));

MIPS16 DI
f (DI x, DI y)
{
  return x / y;
}

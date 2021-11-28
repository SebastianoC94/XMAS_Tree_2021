#include "random.h"

static uint32_t Seed; 

 /* Linear Congruential Generator 
  * Constants from  
  * "Numerical Recipes in C" 
  * by way of 
   * <http://en.wikipedia.org/wiki/Linear_congruential_generator#LCGs_in_common_use>
   * Note: Secure implementations may want to get uncommon/new LCG values
  */
uint32_t NextVal()
{
  Seed=Seed*1664525L+1013904223L;  
  return Seed;
} 

/* Call before first use of NextVal */
void InitSeed()
{
   //Your code for random seed here

   // Correct distribution errors in seed
   NextVal();
   NextVal();
   NextVal();
   NextVal();
}

uint8_t random_bit_mask(void)
{
  uint32_t rnd = NextVal() >> 8;
  
  uint8_t msk = rnd >> 8;
  
  return msk;
}

uint8_t random_number(uint8_t min, uint8_t max)
{
  uint8_t rnd = random_bit_mask();
  return (rnd %(max - min + 1) + min);
}



/** Description: Iterate over all masks and 
 * their submasks/supermasks in O(3^n).
*/
//iterate submask
for (int submask = mask; submask;
  submask = (submask - 1) & mask)
//iterate supermask
for (int supermask = mask; supermask < (1 << n);
  supermask = (supermask + 1) | mask)

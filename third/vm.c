#include "vm.h"

int main()
{
  srand(time(NULL));
  int len = (int)pow(2, PPN);
  int page_table[len], tlb[len];
  init_pt(page_table, len);
  init_tlb(tlb, (int)pow(2, TLB_SIZE), page_table, len);
  // print_pt(page_table, len);
  // print_tlb(tlb, len);
  int count;
  printf("$");
  scanf("%d", &count);
  int temp_count = count;
  while(count-- > 0) {
    float access_time = 0;
    float tlb_hit = 0;
    int simulation = SIM_NUM;
    while (simulation-- > 0) {
      int addr = gen_virtual_addr(len);
      int ppn, ppo;
      // printf("virtual address: %d\n", addr);
      int vpn = (addr & 0xff000) >> P;
      int vpo = addr & 0x00fff;
      if (USE_TLB) {
        access_time += ATT;
        if (tlb[vpn] != 100) {
          ppn = tlb[vpn];
          ppo = vpo;
          access_time += AMT;
          tlb_hit += 1;
        } else {
          ppn = page_table[vpn];
          ppo = vpo;
          access_time += 2 * AMT;
        }
      } else {
        ppn = page_table[vpn];
        ppo = vpo;
        access_time += 2 * AMT;
      }
      // printf("physical address: %d\n", (ppn << P) +ppo);
    }
    printf("average access time: %.1f\n\n", access_time / SIM_NUM);
    printf("tlb hit: %.1f%%\n", (tlb_hit / SIM_NUM)*100);
  }
}

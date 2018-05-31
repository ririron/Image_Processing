#include <stdio.h>
int main(void)
{
    int foo[2][3] = {0}; //(int[3])*型
    int (*ptr)[3];       //(int[3])*型
    ptr = &foo;          //foo が &(foo[0]) を指すのに対して, &foo は &(配列としてのfoo) をさす.

    printf ("foo[1][2] = %d\n", ptr[1][2]);
    //foo[1][2] = 0 と正しく表示される.

    return 0;
}

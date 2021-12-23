// Compact solution:

// long foo(long x, long y){
//     long r = 188*y-43*x;
//     return r;
// }

//Detailed solution:
long foo(long x, long y){
    long t0 = 3*x;      //lea    (%rdi,%rdi,2),%rax
    t0 = x+4*t0;        //lea    (%rdi,%rax,4),%rax
    t0 = t0<<2;         //shl    $0x2,%rax
    long t1 = 3*y;      //lea    (%rsi,%rsi,2),%rcx
    long t2 = t1;       //mov    %rcx,%rdx
    t2 = t2<<5;         //shl    $0x5,%rdx
    t2 -= t1;           //sub    %rcx,%rdx
    t0 += t2;           //add    %rdx,%rax
    y = y-x;            //sub    %rdi,%rsi
    t2 = 3*y;           //lea    (%rsi,%rsi,2),%rdx
    t2 = t2<<5;         //shl    $0x5,%rdx
    t2-=y;              //sub    %rsi,%rdx
    t0+=t2;             //add    %rdx,%rax
    return t0;


}
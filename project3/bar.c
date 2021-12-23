long bar(long x, long y){
    long t0 = x;        //mov    %rdi,%rdx
    int t1 = 0;         //mov    $0x0,%eax
    long t2 = 5*x;      //lea    (%rdi,%rdi,4),%rcx
    t2 = 2*t2+x;        //lea    (%rdi,%rcx,2),%rcx
    x = 16*y;           //mov    %rsi,%rdi      shl    $0x4,%rdi
    t2 = 2*y +t2;       //lea    (%rcx,%rsi,2),%rcx
    t2 = t2-x;          //sub    %rdi,%rcx
    t2+=1;              //add    $0x1,%rcx
    while (t0<=y){      //cmp    %rsi,%rdx      jle    24 <bar+0x24>
        t0+=1;          //add    $0x1,%rdx
        t1=t1+t2;       //add    %rcx,%rax
    }
    return t1;
}
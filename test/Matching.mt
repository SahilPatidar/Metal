extern fn printf;
extern fn strlen;


fn KTM(str *const i8, patt *const i8)  {
    let mut e = strlen(patt) as i32;
    let mut LTB [256]i32;
    let mut si = e + 1;
    for i in 0..si { 
        LTB[i] = 0;
    }

    let size = strlen(str) as i32;
    let mut pi = 1;
    for let mut i = 0; i < size; i+=1 { 
        if patt[LTB[pi - 1]] == str[i] {
            LTB[pi] = LTB[pi - 1] + 1;
            pi+=1;
            printf("%d ", i);
        }
    }   
    printf("\n");
}


fn main() -> i32{
    // KTM("olderisnotcaller", "isnot");
    KTM("olderisnotcaller", "iser");
    // KTM("olderisnotcaller", "deri");
    return 0;
}
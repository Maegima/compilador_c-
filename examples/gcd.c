int gcd(int u, int v){
if(v==0) 
    return u;
 else 
    return gcd(v, u-u/v*v);
}

void main(void)
{
    int x; int y[10];
    x = input(); 
    y[1 + x] = input();
    output(gcd(x,y));   
}
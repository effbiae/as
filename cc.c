typedef unsigned char C,*S;typedef char G;typedef short H;typedef int I;typedef long J;
#define R return
#define C(x,y) case x:{y;break;}
enum{ax,cx, dx, bx, sp, bp, si, di,
     r8,r9,r10,r11,r12,r13,r14,r15};
enum{o,u,z,g,s,b,y,x,       //o(accum) s(stack) i,j(scratch) x,y,z,u,v,w(parms) b,c,d,e,f,g(save state).   s,b,c,d no RM mode
     v,w,i,j,c,d,e,f};    
enum{ret,mov,add,sub,imul,cqo,idiv,nop};
J swap(J*x,J*y){J t=*x;*x=*y;*y=t;R t;}    // store load  immediate
J as(G*b,J o,J x,J y,J m) //m is 1:RR, 2:MR, 4:RM, 8:RI.  return inst length
{G*a=b;
 G rex(G w){R 0x48|w*8|(x>7)*4|y>7;}
 G modrm(){R (0||m&1)*0xC0|(x&7)*8|y&7;}
 G*dir(G p){if(m&2)swap(&x,&y),p+=2;*a++=rex(0),*a++=p,*a++=modrm();}
 switch(o){
 C(ret,*a++=0xC3)
 C(add,dir(0x01))
 C(sub,dir(0x29))
 C(mov,(m&8?*a++=0x48+(x>7),*a++=0xb8+x%8,*(J*)a=y,a+=8  //immediate, 
           :dir(0x89)))
 C(cqo, (*a++=0x48,*a++=0x99))
 C(idiv,(y=7,*a++=rex(1),*a++=0xF7,*a++=modrm()))
 C(imul,(y=5,*a++=rex(1),*a++=0xF7,*a++=modrm()))
 default:*(I*)0;
 }
 R a-b;
}
#include<stdio.h>
#define O printf
int main()
{C b[128]={0};
 FILE*f=fopen("o","w");
 I i=0;
 i+=as(b+i,mov,ax,cx,1);
 i+=as(b+i,mov,ax,cx,2);
 i+=as(b+i,mov,ax,cx,4);
 i+=as(b+i,mov,ax,0xdeadbeef,8);
 i+=as(b+i,ret,0,0,0);
 fwrite(b,i,1,f);
 fclose(f);
}

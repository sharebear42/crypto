// Basic RSA encryption algorithm.

#include<stdio.h>
#include<conio.h> 
#include<stdlib.h> 
#include<math.h> 
#include<string.h> 

int p,q,ptest,qtest,x,y,m[100],e[100],d[100],temp[100],c[100],flag,i;
long int len,j,s;
char Msg[100];

int prime(long int);
void calcE();
long int calcD(long int);
void encrypt();
void decrypt();

int main()
{
	system("cls");
	do
	{
	printf("Enter a prime number: ");			
	scanf("%d",&ptest);
	flag=prime(ptest);
	}while(flag==0);
	if(flag==1)
	p=ptest;
	do
	{
	printf("\nEnter a second prime number: ");
	scanf("%d",&qtest);
	flag=prime(qtest);
	}while(flag==0);
	if(flag==1)
	q=qtest;
	printf("\nEnter message: ");
	fflush(stdin);
	scanf("%[^\n]%*c",Msg);
	len=strlen(Msg);
	for(i=0;i!=len;i++)
	m[i]=Msg[i];
	x=p*q;
	y=(p-1)*(q-1);
	calcE();
	printf("\nPossible values of e and d: ");
	for(i=0;i<j-1;i++)
	printf("\n%ld\t%ld",e[i],d[i]);
	encrypt();
	decrypt();
	getch();
	return(0);
}

int prime(long int pr) { 
	int i; 
	j=sqrt(pr); 
	for(i=2;i<=j;i++) { 
    		if(pr%i==0) 
    		return 0; 
		} 
		return 1; 
} 

void calcE() {
	int k;
	k=0;
	for(i=2;i<y;i++) {
		if(y%i==0)
		continue;
		flag=prime(i);
		if(flag==1&&i!=p&&i!=q) {
			e[k]=i;
			flag=calcD(e[k]);
			if(flag>0) {
				d[k]=flag;
				k++;
			}
			if(k==99)
			break;
		}
	}
}

long int calcD(long int z) {
	long int k=1;
	do 
	{
	s=(k*z)%y;
	k++;
	}while(s!=1);
	k=k-1;
	return(k);
}

void encrypt() {
	long int ptxt,ctxt,key=e[0],k;
	i=0;
	while(i<=len) {
		ptxt=m[i];
		ptxt=ptxt-42;
		k=1;
		for(j=0;j<key;j++) {
			k=k*ptxt;
			k=k%x;
		}
		temp[i]=k;
		ctxt=k+42;
		c[i]=ctxt;
		i++;
	}
	c[i]=-1;
	printf("\nThe encrypted message: ");
	for(i=0;c[i]!=-1;i++)
	printf("%c",c[i]);
}

void decrypt() {
	long int ptxt,ctxt,key=d[0],k;
	i=0;
	while(c[i]!=-1) {
		ctxt=temp[i];
		k=1;
		for(j=0;j<key;j++) {
			k=k*ctxt;
			k=k%x;
		}
		ptxt=k+42;
		m[i]=ptxt;
		i++;
	}
	m[i]=-1;
	printf("\nThe decrypted message: ");
	for(i=0;m[i]!=-1;i++)
	printf("%c",m[i]);
}
		
	


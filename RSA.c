/* Basic RSA crypto.
	By Isaac Schumann
	Only for learning, do not use!	
*/

#include<stdio.h>
#include<conio.h> 
#include<stdlib.h> 
#include<math.h> 
#include<string.h> 

int p,q,ptest,qtest,n,phi,m[100],e[100],d[100],temp[100],c[100],flag,i;
long int len,j;
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
		// requests prime number from the user.
	printf("Enter a prime number: ");			
	scanf("%d",&ptest);
		// checks if it is prime before assigning it to the 'p' variable.
	flag=prime(ptest);
	}while(flag==0);
	if(flag==1)
	p=ptest;
	do
	{
		// requests another prime number from the user.
	printf("\nEnter a second prime number: ");
	scanf("%d",&qtest);
		// checks if it is prime before assigning it to the 'q' variable.
	flag=prime(qtest);
	}while(flag==0);
	if(flag==1)
	q=qtest;
		// gets the message from the user.
	printf("\nEnter message: ");
	fflush(stdin);
	scanf("%[^\n]%*c",Msg);
	len=strlen(Msg);
	for(i=0;i!=len;i++)
	m[i]=Msg[i];
		// calculates the modulus and phi.
	n=p*q;
	phi=(p-1)*(q-1);
		// then e and d.
	calcE();
	printf("\nPossible values of e and d: ");
	for(i=0;i<j-1;i++)
	printf("\n%ld\t%ld",e[i],d[i]);
	encrypt();
	decrypt();
	getch();
	return(0);
}
// The prime check.
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
		// cycles through all integers less than phi..
	for(i=2;i<phi;i++) {
		if(phi%i==0)
		continue;
			// if phi is not divisible by 'i', checks if prime.
		flag=prime(i);
		if(flag==1&&i!=p&&i!=q) {
				// if prime, assigns to a value of 'e'.
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
	long int k=1,s;
	do 
	{
	s=(k*z)%phi;
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
			// the answer to everything is then subtracted from 'ptext'..
		ptxt=ptxt-42;
		k=1;
		for(j=0;j<key;j++) {
			k=k*ptxt;
			k=k%n;
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
			k=k%n;
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
		
	


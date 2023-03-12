#include<stdio.h>

//Function for generating array of random binary numbers
int random(int a[],int n)
{
	int i;
//	srand(time(0));
	for(i=0;i<n;i++)
	{
		a[i] = (rand()%2);
	}
}

//Function for dividing a[n] array into two equal parts b[n/2],c[n/2]
void divide(int a[],int b[],int c[], int n)
{
	int i,j;
	int h = n/2;
	for(i=0;i<h;i++)
	{
		b[i] = a[i];
	}
	for(j=0;j<h;j++)
	{
		c[j] = a[i];
		i++;
	}
}

//Function for finding XOR
void xor(int a[],int b[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		a[i] = a[i]^b[i];
	}
}

int main()
{
	int i,r,s,c=0;
	srand(time(0));
	long int rand_sim,key_sim;
	//Array declarations for A3 Algorithm
	int randm[128],key[128],r1[64],r2[64],k1[64],k2[64],sub_op1[32],sub_op2[32];
	
	//Array declarations for SIM
	int randms[128],keys[128],r1s[64],r2s[64],k1s[64],k2s[64],sub_op1s[32],sub_op2s[32];
	
	
	/* SRES* generation by A3 Algorithm*/
	
	//Generating RAND(128 bits) & Key(128 bits)
	random(randm,128);
	random(key,128);
	
	printf("RAND of 128 bits = ");
	for(i=0;i<128;i++)
	{
		printf("%d",randm[i]);
	}
	
	printf("\n\nKey of 128 bits = ");
	for(i=0;i<128;i++)
	{
		printf("%d",key[i]);
	}
	
	//Divide RAND(128 bits) into two equal parts of 64 bits each(r1,r2)
	divide(randm, r1, r2,128);
	//Divide Key(128 bits) into two equal parts of 64 bits each(k1,k2)
	divide(key, k1, k2, 128);
	
	//XOR of r1 with k2 saved in r1
	xor(r1,k2,64);
	//XOR of r2 with k1 saved in r2
	xor(r2,k1,64);
	
	//XOR of r1 with r2 saved in r1
	xor(r1,r2,64);
	
	//Divide r1(64 bits) into two equal parts of 32 bits each(sub_op1,sub_op2)
	divide(r1,sub_op1,sub_op2,64);
	
	//XOR of sub_op1 with sub_op2 saved in sub_op1
	xor(sub_op1,sub_op2,32);
	
	printf("\n\nSRES* = ");
	
	for(i=0;i<32;i++)
	{
		printf("%d",sub_op1[i]);
	}
	
	/*SRES generation by SIM using A3 Algorithm*/
	
	//Accept RAND for SIM
	printf("\n\nEnter RAND of SIM of 128 bits = ");
	for(i=0;i<128;i++)
	{
		randms[i] = randm[i];
	}
	for(i=0;i<128;i++)
	{
		printf("%d",randms[i]);
	}
	
	/*
	scanf("%d",&rand_sim);
	for(i=127;i>=0;i--)
	{
		r = rand_sim%10;
		randms[i]=r;
		rand_sim = rand_sim/10;
	}*/
	
	//Accept Key for SIM
	printf("\n\nEnter Key of SIM of 128 bits = ");
	for(i=0;i<128;i++)
	{
		keys[i] = key[i];
	}
	for(i=0;i<128;i++)
	{
		printf("%d",keys[i]);
	}
	
	/*
	scanf("%d",&key_sim);
	for(i=127;i>=0;i--)
	{
		s = key_sim%10;
		keys[i]=s;
		key_sim = key_sim/10;
	}	*/
	
	//Divide 
	divide(randms, r1s, r2s,128);
	divide(keys, k1s, k2s, 128);

	//XOR
	xor(r1s,k2s,64);
	xor(r2s,k1s,64);
	
	xor(r1s,r2s,64);
	
	divide(r1s,sub_op1s,sub_op2s,64);
	
	xor(sub_op1s,sub_op2s,32);
	
	printf("\n\nSRES = ");
	
	for(i=0;i<32;i++)
	{
		printf("%d",sub_op1s[i]);
	}
	
	printf("\n\nUser is ");
	for(i=0;i<32;i++)
	{
		if(sub_op1[i]!=sub_op1s[i])
		{
			c++;
		}
		
	}
	if(c>0)
	{
		printf("not ");
	}
	printf("Authenticated!");
}


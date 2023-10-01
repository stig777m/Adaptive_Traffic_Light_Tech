#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

struct sll
{ 
	char lit[10];
	float time;
	struct sll *next;
};
typedef struct sll node;
node *head=NULL,*temp,*temp2,*new;

void create()
{
	if(head==NULL)
	{ 	new=(node*)malloc(sizeof(node));
		new->next=new;
		head=new;
	}
	else
		printf("Exists");
}

void ins_end()
{
	new=(node*)malloc(sizeof(node));
	temp=head;
	while(temp->next!=head)
	{
		temp=temp->next;
	}
	temp->next=new;
	new->next=head;
}

void ped_crossing(int nor,int pedtime)
{
	int i;
	temp=head;
	do
	{	
		strcpy(temp->lit,"RED");
		temp=temp->next;
	}while(temp!=head);
	printf("/////////  RED FOR %d secs FOR PEDESTRIAN CROSSING  //////////\n",pedtime);
	printf("Road no:-\t");
	for(i=1;i<=nor;i++)
			printf(" Road %d\t",i);
	printf("\t|\tTime\nLight:-  \t");
	temp=head;
	do
	{
		printf(" %s\t",temp->lit);
		temp=temp->next;
	}while(temp!=head);
	printf("\t|\t%d secs\n//////////////////////////////////////////////////////////////\n\n",pedtime);	
}

void assignTime(int density[])
{
	int i=0;
	temp=head;
	do
	{
		temp->time=(float)density[i]/100*60.0;
		temp=temp->next;
		i++; 	
	}while(temp!=head);
}

void display(int nor)
{
	int j;
	float cur_time;
	printf("\nRoad no:-\t");
	for(j=1;j<=nor;j++)
		printf(" Road %d\t",j);
	printf("\t|\tTime\n");
	temp=head;
	printf("Light:-  \t");
	do
	{
		printf(" %s\t",temp->lit);
		if(!strcmpi(temp->lit,"GREEN")) 
			cur_time=temp->time;	
		if(!strcmpi(temp->lit,"AMBER")) 
			cur_time=4;
		temp=temp->next;
	}while(temp!=head);
	printf("\t|\t%.2f secs",cur_time);
}

void displayambr(int nor,int busyele,int flag)
{
		temp2=head;
		int i=0;
		while(i!=flag)
		{	
			temp2=temp2->next;
			i++;
		}
		strcpy(temp2->lit,"AMBER");
		temp2=temp2->next;
		if(busyele!=flag)
			strcpy(temp2->lit,"AMBER");
		display(nor);
	
}

int main()
{
	int densa[20],nor,i,flag,loop;
	int pedtime,busy,busyele;
	char ped,ambr,editped='Y',editden='Y',editambr='y',ext;
	float mean;
	
	//textcolor(25);
	//cprintf(" hihihi");
	printf("\t\t\t\tADAPTIVE TRAFFIC LIGHTS SYSTEM \n\n");
	printf("This program will calculate and give you the sqeuence of the traffic lights at a intersection with the time \n");
	printf("\nEnter the number of roads joining at the intersection: ");
	scanf("%d",&nor);
		
	//creating the node linked list
	create();
	
	for(i=0;i<nor-1;i++)
	{
		ins_end();
	}
	
	label:                    //label from the goto function which enables to alter the parameters if needed
	
	if(tolower(editambr)=='y')
	{
		printf("\nDo you want Amber light between light changes?[Y/N] :");
		scanf(" %c",&ambr);
	}
	
	if(tolower(editped)=='y')
	{
		printf("\nDo you all traffic to be stopped for pedestrain crossing [Y/N]: ");
		scanf(" %c",&ped);
		if(tolower(ped)=='y')
		{	printf("\nEnter the time required for pedestrain crossing(in secs): ");
			scanf("%d",&pedtime);
		}
	}
	
	if(tolower(editden)=='y')
	{
		busy=0;
		for(i=0;i<nor;i++)
		{
			printf("\nDensity at road %d in terms of traffic capacity (out of 100%): ",i+1);
			scanf("%d",&densa[i]);
			if(densa[i]>busy)
			{
				busy=densa[i];
				busyele=i;
			}
		}		
	}
	
	assignTime(densa);
		
	printf("\n\nThe sqeuence of traffic lights on each road and time the lights will stay on is as follows for the most efficient flow of traffic\n\n");
	if(tolower(ped)=='y')
		printf("The lights at all roads will turn red for %d secs for pedestrain crossing\n\n",pedtime);
	//displaying;
	flag=0;
	loop=0;
	while(loop<nor)
	{
		temp2=head;
		i=0;
		do
		{	
			if(i<flag)
				strcpy(temp2->lit,"RED");
			else if (i==flag)
				strcpy(temp2->lit,"GREEN");
			else if (i>flag)
				strcpy(temp2->lit,"RED");	
			temp2=temp2->next;
			i++;
		}while(temp2!=head);
		
		//displaying
		display(nor);
		if(tolower(ambr)=='y')
		{
			displayambr(nor,busyele,flag);
		}
		
		printf("\n------------------------------------------------------------\n\n");
		if(busyele==flag && (tolower(ped)=='y'))
		{
			ped_crossing(nor,pedtime);
			if(tolower(ambr)=='y')
			{
				displayambr(nor,busyele+1,flag+1);
				printf("\n------------------------------------------------------------\n\n");
			}
		}
		flag++;
		loop++;
	}
	printf("\nThis cycle will continue untill the traffic density changes\n");
	printf("\nPress Y to exit and N to edit the parameters :");
	scanf(" %c",&ext);
	if(tolower(ext)=='y')
		exit(0);
	
	printf("\nDo you want to enable/disable pedestrain crossing?[Y/N] :");
	scanf(" %c",&editped);
		
	printf("\nDo you want to change the traffic densities?[Y/N] :");
	scanf(" %c",&editden);
	
	printf("\nDo you want to add/remove amber light?[Y/N] :");
	scanf(" %c",&editambr);
	goto label;
		
	getch();
	return 0;
}

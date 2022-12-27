/**
    Name: Mubtasim Ahmed Rakheen
**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#define MAX 50
typedef struct
{
    char label[6];
    int distance;
    int previous;
    int visited;
}
Vertex;

void DijkstraAlgo(Vertex VertexArray[],int AdjMatrix[MAX][MAX],int StartVertex,int VertexCount)
{
    int CurrentVertex = StartVertex;
    VertexArray[StartVertex].distance = 0;
    VertexArray[StartVertex].previous = -1;
    VertexArray[StartVertex].visited = 1;
    int x=0,i=0;
    for (x = 0; x < VertexCount-1; x++)
    {
        i=0;
        for(i=0;i<VertexCount;i++)
        {
            if(AdjMatrix[CurrentVertex][i] != -1 && !VertexArray[i].visited)
            {
                if(VertexArray[CurrentVertex].distance + AdjMatrix[CurrentVertex][i] < VertexArray[i].distance)
                {
                    VertexArray[i].distance = VertexArray[CurrentVertex].distance + AdjMatrix[CurrentVertex][i];
                    VertexArray[i].previous = CurrentVertex;
                }
            }
        }
        int SmallestVertexIndex = -1;
        int SmallestVertex = INT_MAX;
        i=0;
        for(i = 0; i < VertexCount; i++)
        {
            // Check all vertices for distance from CurrentVertex and update
            if (!VertexArray[i].visited)
            {
                if (VertexArray[i].distance < SmallestVertex)
                {
                    SmallestVertex = VertexArray[i].distance;
                    SmallestVertexIndex = i;
                }
            }
        }
        CurrentVertex = SmallestVertexIndex;
        VertexArray[CurrentVertex].visited = 1;
    }
}

int main()
{
    char filename[500]="";
    printf("Please Enter graph text file name, including file extension[**The graph file location must be in the same directory as the program file**]: ");
    scanf("%s",filename);
    char print[10]="";
    int x=1;
    while(x==1){
        printf("Do you want to print the ADJACENCY MATRIX and VERTEX ARRAY of the graph(yes/no): ");
        scanf("%s",print);
        if(strcmp(print,"yes")!=0 && strcmp(print,"no")!=0){
            printf("Invalid input! please try again.");
        }
        else{
            break;
        }
    }

    if(access(filename, F_OK) == 0)
    {
        Vertex VertexArray[MAX] = {};
        int AdjMatrix[MAX][MAX]= {};
        int a=0,b=0;
        for(a=0;a<MAX;a++)
        {
            for(b=0;b<MAX;b++)
            {
                AdjMatrix[a][b] = -1;
            }
        }
        char FileLine[30]={};
        char *token;
        int vi=0,w=0;
        int count=0;
        FILE* FH=fopen(filename,"r");
        while (fgets(FileLine, sizeof(FileLine)-1, FH) != NULL)
        {
            if (FileLine[strlen(FileLine)-1] == '\n')
            {
                FileLine[strlen(FileLine)-1] = '\0';
            }
            token = strtok(FileLine, ",");
            strcpy(VertexArray[count].label,token);
            VertexArray[count].distance = INT_MAX;
            VertexArray[count].visited = 0;
            VertexArray[count].previous = -1;
            token = strtok(NULL, ",");
            while( token != NULL )
            {
                vi = atoi(token);
                token = strtok(NULL, ",");
                w = atoi(token);
                AdjMatrix[count][vi] = w;
                token = strtok(NULL, ",");
            }
            count++;
        }
        fclose(FH);
        int VertexCount = count;
        int StartVertex = 0;
        int DestinationVertex = 0;
        int i=0,j=0;

        if(strcmp(print,"yes")==0){
            printf("\n");
            for(i=0;i<VertexCount;i++)
            {
                for(j=0;j<VertexCount;j++)
                {
                    printf("%5d\t",AdjMatrix[i][j]);
                }
                printf("\n");
            }
        }

        char ans[6]={};
        printf("What is the starting vertex? ");
        scanf("%s",ans);
        int l=0;
        for(l=0;l<VertexCount;l++)
        {
            int comp = strcmp(VertexArray[l].label,ans);
            if(comp==0)
            {
                StartVertex = l;
            }
        }
        DijkstraAlgo(VertexArray,AdjMatrix,StartVertex,VertexCount);

        if(strcmp(print,"yes")==0){
            printf("\n\nI\tL\tD\tP\tV\n");
            for(i=0;i<VertexCount;i++)
            {
               printf("%d\t%s\t%d\t%d\t%d\n",i,VertexArray[i].label,VertexArray[i].distance,VertexArray[i].previous,VertexArray[i].visited);
            }
            printf("\n");
        }

        char ans2[6]={};
        printf("What is the destination vertex? ");
        scanf("%s",ans2);
        l=0;
        for(l=0;l<VertexCount;l++)
        {
            int comp = strcmp(VertexArray[l].label,ans2);
            if(comp==0)
            {
                DestinationVertex = l;
            }
        }
        int path[MAX] = {};
        path[0] = DestinationVertex;
        path[1] = VertexArray[DestinationVertex].previous;
        int p=2,cp=1;
        while(VertexArray[path[cp]].previous != -1)
        {
            path[p] = VertexArray[path[cp]].previous;
            p++;
            cp++;
        }
        printf("The path from %s to %s is ",VertexArray[StartVertex].label,VertexArray[DestinationVertex].label);
        int s=0;
        for(s=p-1;s>=0;s--)
        {
            if(s>0)
            {
                printf("%s->",VertexArray[path[s]].label);
            }
            else
            {
                printf("%s",VertexArray[path[s]].label);
            }
        }
        printf(" and has length of %d\n",VertexArray[DestinationVertex].distance);
    }

    else
    {
        printf("\nIncorrect filename or file not in same directory as program ...exiting\n");
    }

    return 0;
    exit(0);
}













#include<stdio.h>
#include<math.h>

typedef struct node node;

struct node
{
    int id; //�s��
    double x; //x�y��
    double y; //y�y��
    int num_of_con; //�s���쪺�I��
    int connects[100];
    double value;
    double next_value; //�p���Ȧs

};

int max(int a, int b)//�^�Ǥj��
{
    if (a>b)
        return a;
    else
        return b;
}

int distance(node nodes[],int current_node,int next_node)//return 1 �N��Z��>=1 return 0�N��Z��<1
{
    if((nodes[current_node].x-nodes[next_node].x)*(nodes[current_node].x-nodes[next_node].x)+(nodes[current_node].y-nodes[next_node].y)*(nodes[current_node].y-nodes[next_node].y)>=1)
    {
        return 1;
    }
    else
        return 0;
}

void make_connect(node nodes[],int num_of_nodes) //���I�I�̳s��
{
    for(int i=0; i<num_of_nodes; i++) //�{�b��node
    {
        for(int j=i+1; j<num_of_nodes; j++) //�n�ˬd���S���s����node
        {
            if(distance(nodes,i,j)==1)
                continue;
            else
            {
                nodes[i].connects[nodes[i].num_of_con]=j;
                nodes[j].connects[nodes[j].num_of_con]=i;
                nodes[i].num_of_con++;
                nodes[j].num_of_con++;

            }

        }
    }

}

void average(node nodes[],int num_of_nodes,int round)
{

    printf("%d %d\n",num_of_nodes,round);
    for(int r=0; r<round; r++)
    {

        for(int i=0; i<num_of_nodes; i++)//��X
        {
            printf("%.2lf",nodes[i].value);
            if(i!=num_of_nodes-1)
                printf(" ");
        }
        printf("\n");

        for(int i=0; i<num_of_nodes; i++) //i�N���b�p�⪺�I
        {
            double self_percent=1;//�ۤv�v��
            nodes[i].next_value=0;
            for(int j=0; j<nodes[i].num_of_con; j++) //��s���I���v�� j�N���s���쪺�I
            {
                nodes[i].next_value+=((double)1/(double)((max(nodes[i].num_of_con,nodes[nodes[i].connects[j]].num_of_con)*2)))*nodes[nodes[i].connects[j]].value;
                self_percent-=((double)1/(double)((max(nodes[i].num_of_con,nodes[nodes[i].connects[j]].num_of_con)*2)));
            }
            nodes[i].next_value+=self_percent*nodes[i].value;

        }

        for(int i=0; i<num_of_nodes; i++) //��s��
        {
            nodes[i].value=nodes[i].next_value;
        }


    }

}


int main()
{
    int num_of_nodes,round;
    scanf("%d%d",&num_of_nodes,&round);
    node nodes[num_of_nodes];
    for(int i=0; i<num_of_nodes; i++) //��J�I
    {
        int tmp_id;
        double tmp_x;
        double tmp_y;
        double tmp_value;
        scanf("%d%lf%lf%lf",&tmp_id,&tmp_x,&tmp_y,&tmp_value);
        nodes[tmp_id].id=tmp_id;
        nodes[tmp_id].x=tmp_x;
        nodes[tmp_id].y=tmp_y;
        nodes[tmp_id].value=tmp_value;
        nodes[tmp_id].next_value=tmp_value;
        nodes[tmp_id].num_of_con=0;
    }
    make_connect(nodes,num_of_nodes);
    average(nodes,num_of_nodes,round);


    return 0;
}

/*
���C�@�I

�H�o�@���}�l�ɪ��ƾ�
�אּ
1/2n*�Ii���� i���Ҧ��L�s�쪺�I (n����s���쪺�I�ҳs�����I���ƩάO�ۤv�ҳs�����I�Ƥ������j��)+~�Ҧ��s���I�@��
�A�[�W(1-�Ҧ��v��)*�ۤv����

�]���Ҧ��I����@����s���
�C�@���}�l�e����X��ثe�Ҧ��I����
*/


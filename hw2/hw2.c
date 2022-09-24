#include<stdio.h>
#include<stdlib.h>
#define null NULL
int maxlv;
//#define a 2+5
// ans = a * 3= 2+5 * 3
typedef struct node* nodeptr;
//typedef struct listnode* listnodeptr;
typedef struct node
{
    int id;
    nodeptr parent;
    int lv;
    int before;//�쥻parent�s��
    int after;//�sparent�s��
    nodeptr next_id;
    nodeptr child;//�schild��data ���V�Ĥ@�Ӥp��(�V�U��)
    nodeptr brothers;//�s�U�@��child if���h��child(�V�k��)

}node;

/*typedef struct listnode
{
    nodeptr data;//�schild��data ���V�Ĥ@�Ӥp��(�V�U��)
    nodeptr next;//�s�U�@��child if���h��child(�V�k��)
}listnode;
*/
nodeptr searchid(int id,nodeptr idhead)//�^��id=id����m
{
    nodeptr idcurrent=idhead;
    while(1)
    {
        if(idcurrent->id==id) break;
        idcurrent=idcurrent->next_id;
    }
    return idcurrent;
}
void dfs(nodeptr ending_cur,int level)
{
    ending_cur->lv=level;
    if(level>maxlv) maxlv=level;
    if(ending_cur->child!=null)//�V�U��
    {
        dfs(ending_cur->child,level+1);//�V�k��
    }
    if(ending_cur->brothers!=null)
    {
        dfs(ending_cur->brothers,level);
    }
}
/*
nodeptr searchid(int id,nodeptr cur_node)//�^��id=id����m ���Ӫ���
{
    if(cur_node->id == id) return cur_node;
    search(id, cur_node->next_id);
}
*/
int main()
{
    int num_of_node;

    scanf("%d",&num_of_node);
    int origin[num_of_node];//�s�@�}�l��
    for(int i=0;i<num_of_node;i++) scanf("%d",&origin[i]);
    nodeptr idhead=malloc(sizeof(node));
    nodeptr idcurrent=idhead;
    idhead->id=0;
    idhead->brothers=null;
    idhead->child=null;
    idhead->parent=null;
    idhead->before=origin[0];
    for(int i=1;i<num_of_node;i++)//�Цn�Ҧ������I
    {
        idcurrent->next_id=malloc(sizeof(node));
        idcurrent=idcurrent->next_id;
        idcurrent->id=i;
        idcurrent->brothers=null;
        idcurrent->child=null;
        idcurrent->parent=null;
        idcurrent->before=origin[i];
    }
    idcurrent->next_id=null;

    int ending[num_of_node];//�s���G�ϧ�
    int ending_head_id;
    nodeptr ending_head;//���G�Ϫ�head
    nodeptr ending_cur;//���G�ϫإ߹ϮɨϥΪ�����

    for(int i=0;i<num_of_node;i++)
    {
        scanf("%d",&ending[i]);
        if(ending[i]==-1) ending_head_id=i;
    }
    ending_head=searchid(ending_head_id,idhead);

    ending_cur=ending_head;
    idcurrent=idhead;
    for(int i=0;i<num_of_node;i++)//�q�s���ȱ��ع�
    {
       // printf("for %d \n",i);
       idcurrent->after=ending[i];
        if(ending[i]==-1)//���ۤv��parent
        {
            idcurrent->parent=null;
            idcurrent=idcurrent->next_id;
            continue;
        }
        else
        {
            idcurrent->parent=searchid(ending[i],idhead);
        }
        if(idcurrent->parent->child==null)//�ۤv��parent��ۤv��@��l �p�G�w�g����l�h�[�J��l���S��
        {
            idcurrent->parent->child=idcurrent;

        }
        else if(idcurrent->parent->child->brothers==null)
        {
            idcurrent->parent->child->brothers=idcurrent;
            idcurrent->parent->child->brothers->brothers=null;

        }
        else
        {
            nodeptr tmp=idcurrent->parent->child->brothers;
            idcurrent->parent->child->brothers=idcurrent;
            idcurrent->parent->child->brothers->brothers=tmp;

        }
            idcurrent=idcurrent->next_id;

    }
    maxlv=0;
    dfs(ending_cur,0);
    /*
    idcurrent=idhead;
    for(int i=0;i<num_of_node;i++)�L�X lv
    {
        printf("%d ", idcurrent->lv);
        idcurrent = idcurrent->next_id;
    }
    printf("\n");
    */
    /*
    idcurrent=idhead;
    for(int i=0;i<num_of_node;i++)�L�Xparent
    {
        if(idcurrent->parent==null) printf("null ");
        else printf("%d ",idcurrent->parent->id);
        idcurrent=idcurrent->next_id;
    }
    */
    printf("%d\n",maxlv+1);
    idcurrent=idhead;


    for(int i=0;i<=maxlv;i++)//�̾ڦU�I��lv��X�Q���ܹL�ΨS�Q���ܹL
    {
        idcurrent=idhead;
        //printf("for %d\n",i);
        for(int j=0;j<num_of_node;j++)
        {

            if(idcurrent->lv>i)
            {
                printf("%d ",idcurrent->before);
            }
            else
            {
                printf("%d ",idcurrent->after);
            }
            if(j!=num_of_node-1) idcurrent=idcurrent->next_id;
        }
        printf("\n");
        idcurrent=idhead;

    }

}


/*
dfs(head,0);
DFS(node *cur_node, int level) ��g�p��
{
    record, level;��llv�s�b�ۤv���W
    for all child of cur_node s
        DFS(s, level + 1)
}
dfs��N�p��
DFS(node *cur_node, int level)
{
    record, level;��llv�s�b�ۤv���W
    DFS(right, level);
    DFS(down, level + 1);
}

*/
/*
    for(int i=0;i<num_of_node;i++)
    {
        for(int j=0;j<num_of_node;j++)
        {
            if(ending[j]==ending_cur->id)
            {
                if(ending_cur->child==null)
                {
                    ending_cur->child=searchid(j,idhead);
                }
                else if(ending_cur->brothers==null)
                {
                    ending_cur->brothers=searchid(j,idhead);
                }
                else
                {
                    nodeptr tmp=ending_cur->brothers;
                    ending_cur->brothers=searchid(j,idhead);
                    ending_cur->brothers->brothers=tmp;

                }
            }
        }
        ending_cur=ending_cur->child;
    }

*/

/*
nodeptr head=malloc(sizeof(node));//head[0] �s����0, head[1]: 1, head[2]: 2
    nodeptr current=head;
    head->id=0;
    head->parent=NULL;
    head->child=malloc(sizeof(listnode));
    head->child->next=NULL;
    head->num_of_child=0;
    for(int i=1;i<num_of_node;i++)
    {
        current->child->data=malloc(sizeof(node));//�гy�U�@�I
        current->child->data->parent=current;//�O���U�@�Iparent
        current=current->child->data;//���ʨ�U�@�I
        current->id=i;
        current->num_of_child=0;
        current->child=malloc(sizeof(listnode));
        current->child->next=NULL;

    }
    current->child->data=NULL;
    int origin[num_of_node];//�s�@�}�l���p
    int start_parent;//�s�̶}�l���Y���H�O��
    nodeptr start_parent_ptr=NULL;
    for(int i=0;i<num_of_node;i++)
    {
        scanf("%d",&origin[i]);
        if(origin[i]==-1) start_parent=i;
    }

*/

/*
5
1 3 3 4 -1
3 3 4 2 -1
*/

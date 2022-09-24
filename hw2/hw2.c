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
    int before;//原本parent編號
    int after;//新parent編號
    nodeptr next_id;
    nodeptr child;//存child的data 指向第一個小孩(向下指)
    nodeptr brothers;//存下一個child if有多個child(向右指)

}node;

/*typedef struct listnode
{
    nodeptr data;//存child的data 指向第一個小孩(向下指)
    nodeptr next;//存下一個child if有多個child(向右指)
}listnode;
*/
nodeptr searchid(int id,nodeptr idhead)//回傳id=id的位置
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
    if(ending_cur->child!=null)//向下走
    {
        dfs(ending_cur->child,level+1);//向右走
    }
    if(ending_cur->brothers!=null)
    {
        dfs(ending_cur->brothers,level);
    }
}
/*
nodeptr searchid(int id,nodeptr cur_node)//回傳id=id的位置 明皇爸爸
{
    if(cur_node->id == id) return cur_node;
    search(id, cur_node->next_id);
}
*/
int main()
{
    int num_of_node;

    scanf("%d",&num_of_node);
    int origin[num_of_node];//存一開始圖
    for(int i=0;i<num_of_node;i++) scanf("%d",&origin[i]);
    nodeptr idhead=malloc(sizeof(node));
    nodeptr idcurrent=idhead;
    idhead->id=0;
    idhead->brothers=null;
    idhead->child=null;
    idhead->parent=null;
    idhead->before=origin[0];
    for(int i=1;i<num_of_node;i++)//創好所有的結點
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

    int ending[num_of_node];//存結果圖形
    int ending_head_id;
    nodeptr ending_head;//結果圖的head
    nodeptr ending_cur;//結果圖建立圖時使用的指標

    for(int i=0;i<num_of_node;i++)
    {
        scanf("%d",&ending[i]);
        if(ending[i]==-1) ending_head_id=i;
    }
    ending_head=searchid(ending_head_id,idhead);

    ending_cur=ending_head;
    idcurrent=idhead;
    for(int i=0;i<num_of_node;i++)//從編號值接建圖
    {
       // printf("for %d \n",i);
       idcurrent->after=ending[i];
        if(ending[i]==-1)//找到自己的parent
        {
            idcurrent->parent=null;
            idcurrent=idcurrent->next_id;
            continue;
        }
        else
        {
            idcurrent->parent=searchid(ending[i],idhead);
        }
        if(idcurrent->parent->child==null)//自己的parent把自己當作兒子 如果已經有兒子則加入兒子的兄弟
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
    for(int i=0;i<num_of_node;i++)印出 lv
    {
        printf("%d ", idcurrent->lv);
        idcurrent = idcurrent->next_id;
    }
    printf("\n");
    */
    /*
    idcurrent=idhead;
    for(int i=0;i<num_of_node;i++)印出parent
    {
        if(idcurrent->parent==null) printf("null ");
        else printf("%d ",idcurrent->parent->id);
        idcurrent=idcurrent->next_id;
    }
    */
    printf("%d\n",maxlv+1);
    idcurrent=idhead;


    for(int i=0;i<=maxlv;i++)//依據各點的lv輸出被改變過或沒被改變過
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
DFS(node *cur_node, int level) 放射小孩
{
    record, level;把llv存在自己身上
    for all child of cur_node s
        DFS(s, level + 1)
}
dfs串燒小孩
DFS(node *cur_node, int level)
{
    record, level;把llv存在自己身上
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
nodeptr head=malloc(sizeof(node));//head[0] 編號為0, head[1]: 1, head[2]: 2
    nodeptr current=head;
    head->id=0;
    head->parent=NULL;
    head->child=malloc(sizeof(listnode));
    head->child->next=NULL;
    head->num_of_child=0;
    for(int i=1;i<num_of_node;i++)
    {
        current->child->data=malloc(sizeof(node));//創造下一點
        current->child->data->parent=current;//記錄下一點parent
        current=current->child->data;//移動到下一點
        current->id=i;
        current->num_of_child=0;
        current->child=malloc(sizeof(listnode));
        current->child->next=NULL;

    }
    current->child->data=NULL;
    int origin[num_of_node];//存一開始狀況
    int start_parent;//存最開始的頭的人是誰
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

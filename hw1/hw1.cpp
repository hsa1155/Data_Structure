#include<bits/stdc++.h>
using namespace std;

struct node
{
    int id; //編號
    double x; //x座標
    double y; //y座標
    int num_of_con=0; //連接到的點數
    vector<int> connects; //連接的點們
    double value;
    double next_value; //計算後暫存

};

int distance(node nodes[],int current_node,int next_node)//return 1 代表距離>=1 return 0代表距離<1
{
    if((nodes[current_node].x-nodes[next_node].x)*(nodes[current_node].x-nodes[next_node].x)+(nodes[current_node].y-nodes[next_node].y)*(nodes[current_node].y-nodes[next_node].y)>=1)
    {
        return 1;
    }
    else
        return 0;
}

void make_connect(node nodes[],int num_of_nodes) //使點點們連接
{
    for(int i=0; i<num_of_nodes; i++) //現在的node
    {
        for(int j=i+1; j<num_of_nodes; j++) //要檢查有沒有連接的node
        {
            if(distance(nodes,i,j)==1)
                continue;
            else
            {
                nodes[i].num_of_con++;
                nodes[j].num_of_con++;
                nodes[i].connects.push_back(j);
                nodes[j].connects.push_back(i);
            }

        }
    }

}

void average(node nodes[],int num_of_nodes,int round)
{

    cout<<num_of_nodes<<" "<<round<<endl;
    for(int r=0; r<round; r++)
    {
       // cout<<r<<" ";

        for(int i=0; i<num_of_nodes; i++)
        {
            /*
            int num=nodes[i].value*100;
            double out=num/100.0;
            printf("%.2lf",out);
            */
            printf("%.2lf",nodes[i].value);
            if(i!=num_of_nodes-1) cout<<" ";
        }
        cout<<endl;

        for(int i=0; i<num_of_nodes; i++) //i代表正在計算的點
        {
            double self_percent=1;//自己權重
            nodes[i].next_value=0;
            for(int j=0; j<nodes[i].num_of_con; j++) //算連接點的權重 j代表它連接到的點
            {
                nodes[i].next_value+=((double)1/(double)((max(nodes[i].num_of_con,nodes[nodes[i].connects[j]].num_of_con)*2)))*nodes[nodes[i].connects[j]].value;
                self_percent-=((double)1/(double)((max(nodes[i].num_of_con,nodes[nodes[i].connects[j]].num_of_con)*2)));
            }
            nodes[i].next_value+=self_percent*nodes[i].value;

        }

        for(int i=0; i<num_of_nodes; i++) //更新值
        {
            nodes[i].value=nodes[i].next_value;
        }


    }

}


int main()
{
    int num_of_nodes,round;
    cin>>num_of_nodes>>round;
    node nodes[num_of_nodes];
    for(int i=0; i<num_of_nodes; i++) //輸入點
    {
        int tmp_id;
        double tmp_x;
        double tmp_y;
        double tmp_value;
        cin>>tmp_id>>tmp_x>>tmp_y>>tmp_value;
        nodes[tmp_id].id=tmp_id;
        nodes[tmp_id].x=tmp_x;
        nodes[tmp_id].y=tmp_y;
        nodes[tmp_id].value=tmp_value;
        nodes[tmp_id].next_value=tmp_value;
    }
    make_connect(nodes,num_of_nodes);
    average(nodes,num_of_nodes,round);
    /*
    for(int r=0;r<round;r++)
    {
        for(int i=0;i<num_of_nodes;i++)
        {
            cout<<nodes[i].value<<" ";
        }
        cout<<endl;
    }
    */
    /*
    for(int i=0;i<num_of_nodes;i++)
    {
        cout<<nodes[i].num_of_con<<" "<<nodes[i].connects[0]<<endl;
    }
    */


}
